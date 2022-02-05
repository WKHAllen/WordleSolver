#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "dict.h"
#include "letters.h"
#include "solver.h"

#define DICT_PATH "assets/american-english-dict"
#define LETTERS_PATH "assets/letters"

#define GUESS_RESULT_INPUT_MAX 64

BOOL is_five_lowercase_letters(const char *word) {
  if (strlen(word) != 5) {
    return FALSE;
  }

  for (size_t i = 0; i < 5; i++) {
    if (!(word[i] >= 97 && word[i] <= 122)) {
      return FALSE;
    }
  }

  return TRUE;
}

void print_usage(void) {
  printf("W O R D L E    S O L V E R\n\n");
  printf("Usage: Word guesses will be determined and shown on screen. After making a\n");
  printf("guess in Wordle, enter the results of the guess in the prompt here. Type the\n");
  printf("word, with a character before each letter indicating whether the letter is\n");
  printf("correct (%c), correct but in the wrong place (%c), or not used (%c).\n\n", CORRECT_PLACE_CHAR, INCORRECT_PLACE_CHAR, NOT_USED_CHAR);
}

int main(int argc, char **argv) {
  // Read the dictionary
  Dict *full_dict = new_dict();
  if (read_dict(full_dict, DICT_PATH) != DICT_SUCCESS) {
    printf("Error: failed to read dictionary file\n\n");
    free_dict(full_dict);
    pause("Press ENTER to exit\n");
    return 1;
  }

  // Filter out all words that are not five letters
  Dict *dict = filter_dict(full_dict, is_five_lowercase_letters);
  free_dict(full_dict);

  // Read letters from file
  int *letters = new_letters();
  if (read_letter_commonality(letters, LETTERS_PATH) != LETTERS_SUCCESS) {
    printf("Error: failed to read letters file\n\n");
    free_dict(dict);
    free_letters(letters);
    pause("Press ENTER to exit\n");
    return 1;
  }

  // Print the usage
  print_usage();
  printf("Number of possible words: %zd\n", dict->size);
  BOOL done = FALSE;

  // Make first guess
  char *guess = guess_word(dict, letters);
  char *upcase_guess = to_upper(guess);
  printf("Try: '%s'\n\n", upcase_guess);
  free(guess);
  free(upcase_guess);

  // Get first guess results
  char guess_results_line[GUESS_RESULT_INPUT_MAX];
  input("Enter guess results:\n> ", guess_results_line, GUESS_RESULT_INPUT_MAX);

  // Make guesses until empty input received
  while (strcmp(guess_results_line, "") != 0 && !done) {
    // Parse the guess results
    GuessResults *guess_results = new_guess_results();
    GuessResultsParseError *parse_error = parse_guess_results(guess_results, guess_results_line);

    // Check for parse errors
    if (parse_error->error_type != SOLVER_SUCCESS) {
      switch (parse_error->error_type) {
        case SOLVER_ERROR_EXPECTED_LETTER_PLACEMENT_CHAR:
          printf("ERROR: expected a letter placement indicator (%c, %c, or %c), instead found '%c'\n\n",
                CORRECT_PLACE_CHAR,
                INCORRECT_PLACE_CHAR,
                NOT_USED_CHAR,
                parse_error->bad_char);
          break;

        case SOLVER_ERROR_EXPECTED_LETTER:
          printf("ERROR: expected a letter, instead found '%c'\n\n", parse_error->bad_char);
          break;

        case SOLVER_ERROR_EXPECTED_FIVE_LETTERS:
          printf("ERROR: expected a five letter word\n\n");
          break;
      }

      free_dict(dict);
      free_letters(letters);
      free_guess_results(guess_results);
      free_guess_results_parse_error(parse_error);
      pause("Press ENTER to exit\n");
      return 1;
    }

    // Refine the dictionary based on the guess results
    Dict *refined_dict = refine_dict(dict, guess_results);
    free_dict(dict);
    dict = refined_dict;
    free_guess_results(guess_results);
    free_guess_results_parse_error(parse_error);
    printf("\nNumber of possible words: %zd\n", dict->size);

    // Check for completion
    if (dict->size == 0) {
      printf("ERROR: could not find a word matching the provided parameters\n\n");
      free_dict(dict);
      free_letters(letters);
      pause("Press ENTER to exit\n");
      return 1;
    } else if (dict->size == 1) {
      char *upcase_word = to_upper(dict->next->word);
      printf("WORD FOUND: '%s'\n", upcase_word);
      free(upcase_word);
      done = TRUE;
    } else {
      // Make next guess
      guess = guess_word(dict, letters);
      upcase_guess = to_upper(guess);
      printf("Try: '%s'\n\n", upcase_guess);
      free(guess);
      free(upcase_guess);

      // Get next guess results
      guess_results_line[GUESS_RESULT_INPUT_MAX];
      input("Enter guess results:\n> ", guess_results_line, GUESS_RESULT_INPUT_MAX);
    }
  }

  // Exit
  free_dict(dict);
  free_letters(letters);
  pause("\nPress ENTER to exit\n");
  printf("Exiting successfully...\n");
  return 0;
}
