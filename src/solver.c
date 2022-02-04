#include <stdlib.h>
#include <string.h>
#include "solver.h"
#include "globals.h"
#include "dict.h"

GuessResults *new_guess_results(void) {
  GuessResults *guess_results = malloc(sizeof(GuessResults));
  guess_results->word = "";
  guess_results->guess_states = malloc(5 * sizeof(LetterGuessState));
  return guess_results;
}

int parse_guess_results(GuessResults *guess_results, const char *guess) {
  return 0;
}

char *guess_word(const Dict *dict, const int *letters) {
  return "";
}

BOOL word_match(const char *word, const GuessResults *guess_results) {
  for (int i = 0; i < 5; i++) {
    switch (guess_results->guess_states[i]) {
      case CorrectPlace:
        if (word[i] != guess_results->word[i]) return FALSE;
        break;

      case IncorrectPlace:
        if (word[i] == guess_results->word[i]) return FALSE;
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

Dict *narrow_dict(const Dict *dict, const GuessResults *guess_results) {
  Dict *narrowed_dict = new_dict();
  Dict *current = dict->next;
  Dict *current_narrowed = narrowed_dict;

  while (current != NULL) {
    if (word_match(current->word, guess_results)) {
      dict_set_next_word(current_narrowed, current->word);
      current_narrowed = current_narrowed->next;
    }

    current = current->next;
  }

  return narrowed_dict;
}

void free_guess_results(GuessResults *guess_results) {
  if (strcmp(guess_results->word, "") != 0) {
    free(guess_results->word);
  }

  free(guess_results->guess_states);
  free(guess_results);
}
