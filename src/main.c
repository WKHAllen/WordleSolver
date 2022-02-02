#include <stdio.h>
#include "globals.h"
#include "readdict.h"

#define DICT_PATH "dict/american-english"

int main(int argc, char **argv) {
  // Read dictionary
  Dict *dict = new_dict();
  if (read_dict(dict, DICT_PATH) != READDICT_SUCCESS) {
    printf("Error: failed to read dictionary file\n");
    free_dict(dict);
    return 1;
  }
  printf("Dictionary size: %zd\n", dict->size);
  free_dict(dict);

  // Done
  printf("Done\n");
  return 0;
}
