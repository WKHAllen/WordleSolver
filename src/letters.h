/*
 * Read and store letter lists.
 */

#pragma once
#ifndef LETTERS_H
#define LETTERS_H

#define LETTERS_SUCCESS          0
#define LETTERS_OPEN_FILE_ERROR  1
#define LETTERS_CLOSE_FILE_ERROR 2

/*
 * Create a new array of letters.
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

#endif // LETTERS_H
