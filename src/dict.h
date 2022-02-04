/*
 * Read dictionary files.
 */

#pragma once
#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stddef.h>
#include "globals.h"

#define DICT_SUCCESS          0
#define DICT_OPEN_FILE_ERROR  1
#define DICT_CLOSE_FILE_ERROR 2

#define MAX_LINE_LEN 64

/*
 * A node in the dictionary.
 */
typedef struct _Dict {
  char *word;
  struct _Dict *next;
  size_t size;
} Dict;

/*
 * Create a new dictionary.
 */
Dict *new_dict(void);

/*
 * Set the next word in a dictionary.
 */
void dict_set_next_word(Dict *node, const char *word);

/*
 * Read a dictionary from a file.
 */
int read_dict(Dict *dict, const char *dict_path);

/*
 * Filter words out of a dictionary.
 */
Dict *filter_dict(const Dict *dict, BOOL (*filter_callback)(const char *));

/*
 * Free the memory used by the dictionary.
 */
void free_dict(Dict *dict);

#endif // DICT_H
