#include <stdlib.h>
#include <string.h>
#include "solver.h"
#include "globals.h"
#include "dict.h"

GuessResults *new_guess_results(void) {
  GuessResults *guess_results = malloc(sizeof(GuessResults));
  guess_results->word = strdup("     ");
  guess_results->guess_states = malloc(5 * sizeof(LetterGuessState));
  return guess_results;
}

GuessResultsParseError *parse_guess_results(GuessResults *guess_results, const char *guess) {
  GuessResultsParseError *error = malloc(sizeof(GuessResultsParseError));
  error->error_type = SOLVER_SUCCESS;
  error->bad_char = '\0';

  int letter_num = 0;

  for (int i = 0; guess[i] != '\0'; i++) {
    if (guess[i] == CORRECT_PLACE_CHAR
        || guess[i] == INCORRECT_PLACE_CHAR
        || guess[i] == NOT_USED_CHAR) {
      if (letter_num >= 5) {
        error->error_type = SOLVER_ERROR_EXPECTED_FIVE_LETTERS;
        error->bad_char = guess[i];
        return error;
      }

      if (!is_letter(guess[i + 1])) {
        error->error_type = SOLVER_ERROR_EXPECTED_LETTER;
        error->bad_char = guess[i + 1];
        return error;
      }

      guess_results->word[letter_num] = to_lower_char(guess[i + 1]);
    }

    switch (guess[i]) {
      case CORRECT_PLACE_CHAR:
        guess_results->guess_states[letter_num++] = CorrectPlace;
        i++;
        break;

      case INCORRECT_PLACE_CHAR:
        guess_results->guess_states[letter_num++] = IncorrectPlace;
        i++;
        break;

      case NOT_USED_CHAR:
        guess_results->guess_states[letter_num++] = NotUsed;
        i++;
        break;

      case ' ':
      case '\t':
        continue;

      default:
        error->error_type = SOLVER_ERROR_EXPECTED_LETTER_PLACEMENT_CHAR;
        error->bad_char = guess[i];
        return error;
    }
  }

  if (letter_num != 5) {
    error->error_type = SOLVER_ERROR_EXPECTED_FIVE_LETTERS;
    return error;
  }

  return error;
}

int get_letter_count_up_to(const char *word, const int index) {
  int count = 0;

  for (int i = 0; i < index; i++) {
    if (word[i] == word[index]) {
      count++;
    }
  }

  return count;
}

int calculate_word_score(const char *word, const int *letters) {
  int score = 0;

  for (int i = 0; i < 5; i++) {
    score += get_commonality(letters, word[i]) / (1 + get_letter_count_up_to(word, i));
  }

  return score;
}

char *guess_word(const Dict *dict, const int *letters) {
  if (dict->size == 0) {
    return NULL;
  }

  char *best_guess = malloc(6 * sizeof(char));
  int best_score = 0;
  Dict *current = dict->next;

  while (current != NULL) {
    int current_score = calculate_word_score(current->word, letters);

    if (current_score > best_score) {
      strcpy_s(best_guess, 6, current->word);
      best_score = current_score;
    }

    current = current->next;
  }

  return best_guess;
}

BOOL word_contains(const char *word, const char chr) {
  for (int i = 0; i < 5; i++) {
    if (word[i] == chr) return TRUE;
  }

  return FALSE;
}

BOOL word_match(const char *word, const GuessResults *guess_results) {
  for (int i = 0; i < 5; i++) {
    switch (guess_results->guess_states[i]) {
      case CorrectPlace:
        if (word[i] != guess_results->word[i]) return FALSE;
        break;

      case IncorrectPlace:
        if (word[i] == guess_results->word[i] || !word_contains(word, guess_results->word[i])) return FALSE;
        break;

      case NotUsed:
        for (int j = 0; j < 5; j++) {
          if (word[j] == guess_results->word[i]) return FALSE;
        }
        break;
    }
  }

  return TRUE;
}

Dict *refine_dict(const Dict *dict, const GuessResults *guess_results) {
  Dict *refined_dict = new_dict();
  Dict *current = dict->next;
  Dict *current_refined = refined_dict;

  while (current != NULL) {
    if (word_match(current->word, guess_results)) {
      dict_set_next_word(current_refined, current->word);
      current_refined = current_refined->next;
      refined_dict->size++;
    }

    current = current->next;
  }

  return refined_dict;
}

void free_guess_results(GuessResults *guess_results) {
  if (strcmp(guess_results->word, "") != 0) {
    free(guess_results->word);
  }

  free(guess_results->guess_states);
  free(guess_results);
}

void free_guess_results_parse_error(GuessResultsParseError *error) {
  free(error);
}
