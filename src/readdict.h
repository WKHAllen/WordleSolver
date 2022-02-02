/*
 * Read dictionary files.
 */

#pragma once
#ifndef READDICT_H
#define READDICT_H

#define READDICT_SUCCESS          0
#define READDICT_OPEN_FILE_ERROR  1
#define READDICT_CLOSE_FILE_ERROR 2

#define MAX_LINE_LEN 64

#include <stdio.h>
#include <stddef.h>

/*
 * A node in the dictionary.
 */
typedef struct dictnode {
  char *word;
  struct dictnode *next;
  size_t size;
} Dict;

/*
 * Create a new dictionary.
 */
Dict *new_dict(void);

/*
 * Read a dictionary from a file.
 */
int read_dict(Dict *dict, const char *dictpath);

/*
 * Free the memory used by the dictionary.
 */
void free_dict(Dict *dict);

#endif // READDICT_H
