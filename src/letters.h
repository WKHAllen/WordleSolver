/*
 * Read and store letter lists.
 */

#pragma once
#ifndef LETTERS_H
#define LETTERS_H

#include "globals.h"

#define LETTERS_SUCCESS          0
#define LETTERS_OPEN_FILE_ERROR  1
#define LETTERS_CLOSE_FILE_ERROR 2

/*
 * Create a new array of letters representing letter commonality.
 */
int *new_letters(void);

/*
 * Read the letter commonality data from a file.
 */
int read_letter_commonality(int *letters, const char *letters_path);

/*
 * Get the commonality of a letter.
 */
int get_commonality(const int *letters, const char letter);

/*
 * Free the memory used by the letter commonality data.
 */
void free_letters(int *letters);

/*
 * Create a new array flagging the usage of letters.
 */
BOOL *new_flagged_letters(void);

/*
 * Flag a letter.
 */
void flag_letter(BOOL *letters, const char letter);

/*
 * Unflag a letter.
 */
void unflag_letter(BOOL *letters, const char letter);

/*
 * Check if a letter is flagged.
 */
BOOL is_letter_flagged(const BOOL *letters, const char letter);

/*
 * Free the memory used by the flagged letter array.
 */
void free_flagged_letters(BOOL *letters);

#endif // LETTERS_H
