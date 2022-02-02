#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "readdict.h"

#define DICT_PATH "assets/american-english-dict"

BOOL is_five_lowercase_letters(const char *word) {
  if (strlen(word) != 5) {
    return FALSE;
  }

  for (size_t i = 0; i < 5; i++) {
    if (!(word[i] >= 97 && word[i] <= 122)) {
      return FALSE;
    }
  }

  return TRUE;
}

int main(int argc, char **argv) {
  // Read dictionary
  Dict *full_dict = new_dict();
  if (read_dict(full_dict, DICT_PATH) != READDICT_SUCCESS) {
    printf("Error: failed to read dictionary file\n");
    free_dict(full_dict);
    return 1;
  }
  printf("Full dictionary size: %zd\n", full_dict->size);

  // Filter out all words that are not five letters
  Dict *five_letter_dict = filter_dict(full_dict, is_five_lowercase_letters);
  free_dict(full_dict);
  printf("Five letter dictionary size: %zd\n", five_letter_dict->size);
  printf("First five letter word: %s\n", five_letter_dict->next->word);

  // Done
  free_dict(five_letter_dict);
  printf("Done\n");
  return 0;
}
