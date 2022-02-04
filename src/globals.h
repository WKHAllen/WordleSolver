/*
 * Global definitions.
 */

#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define strdup _strdup

/*
 * Read a line from a file.
 */
size_t get_file_line(FILE *fp, char *line, int max);

/*
 * Read input from stdin.
 */
size_t input(const char *prompt, char *line, int max);

/*
 * Pause and wait for a key press.
 */
void pause(const char *prompt);

/*
 * Check if a character is a letter.
 */
BOOL is_letter(char chr);

/*
 * Uppercase a string.
 */
char *to_upper(const char *str);

/*
 * Lowercase a string.
 */
char *to_lower(const char *str);

/*
 * Uppercase a character.
 */
char to_upper_char(char chr);

/*
 * Lowercase a character.
 */
char to_lower_char(char chr);

#endif // GLOBALS_H
