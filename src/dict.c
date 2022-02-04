#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "globals.h"

Dict *new_dict(void) {
  Dict *dict = (Dict *)malloc(sizeof(Dict));
  dict->word = "";
  dict->next = NULL;
  dict->size = 0;
  return dict;
}

void dict_set_next_word(Dict *node, const char *word) {
  Dict *new_node = new_dict();
  new_node->word = strdup(word);
  new_node->next = NULL;
  node->next = new_node;
}

int read_dict(Dict *dict, const char *dict_path) {
  Dict *current = dict;
  char buffer[MAX_LINE_LEN];

  FILE *fp;
  if (fopen_s(&fp, dict_path, "r") != 0) {
    return DICT_OPEN_FILE_ERROR;
  }

  size_t linelen = 1;
  while ((linelen = get_file_line(fp, buffer, MAX_LINE_LEN)) > 0) {
    dict_set_next_word(current, buffer);
    current = current->next;
    dict->size++;
  }

  if (fclose(fp) != 0) {
    return DICT_CLOSE_FILE_ERROR;
  }

  return DICT_SUCCESS;
}

Dict *filter_dict(const Dict *dict, BOOL (*filter_callback)(const char *)) {
  Dict *filtered_dict = new_dict();
  Dict *filtered_current = filtered_dict;
  dict = dict->next;

  while (dict != NULL) {
    if ((*filter_callback)(dict->word)) {
      dict_set_next_word(filtered_current, dict->word);
      filtered_current = filtered_current->next;
      filtered_dict->size++;
    }

    dict = dict->next;
  }

  return filtered_dict;
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
