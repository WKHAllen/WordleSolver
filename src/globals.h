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

#endif // GLOBALS_H
