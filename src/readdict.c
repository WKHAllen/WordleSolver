#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readdict.h"
#include "globals.h"

size_t get_line(FILE *fp, char *line, int max) {
  if (fgets(line, max, fp) == NULL) {
    return 0;
  } else {
    size_t linelen = strlen(line);
    line[linelen - 1] = '\0';
    return linelen - 1;
  }
}

Dict *new_dict(void) {
  Dict *dict = malloc(sizeof(Dict));
  dict->word = "";
  dict->next = NULL;
  dict->size = 0;
  return dict;
}

void dict_set_next_word(Dict *node, char *word) {
  Dict *new_node = new_dict();
  new_node->word = strdup(word);
  new_node->next = NULL;
  node->next = new_node;
}

int read_dict(Dict *dict, const char *dictpath) {
  Dict *current = dict;
  char buffer[MAX_LINE_LEN];

  FILE *fp;
  if (fopen_s(&fp, dictpath, "r") != 0) {
    return READDICT_OPEN_FILE_ERROR;
  }

  size_t linelen = 1;
  while ((linelen = get_line(fp, buffer, MAX_LINE_LEN)) > 0) {
    dict_set_next_word(current, buffer);
    current = current->next;
    dict->size++;
  }

  if (fclose(fp) != 0) {
    return READDICT_CLOSE_FILE_ERROR;
  }

  return READDICT_SUCCESS;
}

void free_dict(Dict *dict) {
  Dict *current = dict->next;
  Dict *next = current->next;
  free(dict);

  while (next != NULL) {
    free(current->word);
    free(current);
    current = next;
    next = current->next;
  }
}
