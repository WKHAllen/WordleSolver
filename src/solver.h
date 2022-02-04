/*
 * Solve wordle puzzles.
 */

#pragma once
#ifndef SOLVER_H
#define SOLVER_H

#include "globals.h"
#include "dict.h"
#include "letters.h"

#define SOLVER_SUCCESS                              0
#define SOLVER_ERROR_EXPECTED_LETTER_PLACEMENT_CHAR 1
#define SOLVER_ERROR_EXPECTED_LETTER                2
#define SOLVER_ERROR_EXPECTED_FIVE_LETTERS          3

#define CORRECT_PLACE_CHAR   '*'
#define INCORRECT_PLACE_CHAR '?'
#define NOT_USED_CHAR        '!'

/*
 * The state of a guessed letter.
 */
typedef enum _LetterGuessState {
  CorrectPlace,
  IncorrectPlace,
  NotUsed
} LetterGuessState;

/*
 * The results of a word guess.
 */
typedef struct _GuessResults {
  char *word;
  LetterGuessState *guess_states;
} GuessResults;

/*
 * A guess results parsing error.
 */
typedef struct _GuessResultsParseError {
  int error_type;
  char bad_char;
} GuessResultsParseError;

/*
 * Create a new guess results object.
 */
GuessResults *new_guess_results(void);

/*
 * Parse a word guess results.
 */
GuessResultsParseError *parse_guess_results(GuessResults *guess_results, const char *guess);

/*
 * Calculate the letter commonality score of a word.
 */
int calculate_word_score(const char *word, const int *letters);

/*
 * Guess a word.
 */
char *guess_word(const Dict *dict, const int *letters);

/*
 * Filter out words in the dictionary based on the results of a guess.
 */
Dict *refine_dict(const Dict *dict, const GuessResults *guess_results);

/*
 * Free the memory used by the word guess results.
 */
void free_guess_results(GuessResults *guess_results);

/*
 * Free the memory used by the guess results parse error object.
 */
void free_guess_results_parse_error(GuessResultsParseError *error);

#endif // SOLVER_H
