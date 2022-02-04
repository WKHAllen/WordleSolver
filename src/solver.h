/*
 * Solve wordle puzzles.
 */

#pragma once
#ifndef SOLVER_H
#define SOLVER_H

#include "globals.h"
#include "dict.h"
#include "letters.h"

#define SOLVER_SUCCESS                   0
#define SOLVER_GUESS_RESULTS_PARSE_ERROR 1

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
 * Create a new guess results object.
 */
GuessResults *new_guess_results(void);

/*
 * Parse a word guess results.
 */
int parse_guess_results(GuessResults *guess_results, const char *guess);

/*
 * Guess a word.
 */
char *guess_word(const Dict *dict, const int *letters);

/*
 * Filter out words in the dictionary based on the results of a guess.
 */
Dict *narrow_dict(const Dict *dict, const GuessResults *guess_results);

/*
 * Free the memory used by the word guess results.
 */
void free_guess_results(GuessResults *guess_results);

#endif // SOLVER_H
