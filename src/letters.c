#include <stdio.h>
#include <stdlib.h>
#include "letters.h"
#include "globals.h"

int *new_letters(void) {
  int *letters = malloc(26 * sizeof(int));
  return letters;
}

int read_letter_commonality(int *letters, const char *letters_path) {
  char letter;
  int commonality;

  FILE *fp;
  if (fopen_s(&fp, letters_path, "r") != 0) {
    return LETTERS_OPEN_FILE_ERROR;
  }

  while (!feof(fp)) {
    fscanf_s(fp, "%c %d\n", &letter, 1, &commonality);
    letters[letter - 'a'] = commonality;
  }

  if (fclose(fp) != 0) {
    return LETTERS_CLOSE_FILE_ERROR;
  }

  return LETTERS_SUCCESS;
}

int get_commonality(const int *letters, const char letter) {
  return letters[letter - 'a'];
}

void free_letters(int *letters) {
  free(letters);
}

BOOL *new_flagged_letters(void) {
  int *letters = malloc(26 * sizeof(BOOL));

  for (int i = 0; i < 26; i++) {
    letters[i] = FALSE;
  }

  return letters;
}

void flag_letter(BOOL *letters, const char letter) {
  letters[letter - 'a'] = TRUE;
}

void unflag_letter(BOOL *letters, const char letter) {
  letters[letter - 'a'] = FALSE;
}

BOOL is_letter_flagged(const BOOL *letters, const char letter) {
  return letters[letter - 'a'];
}

void free_flagged_letters(BOOL *letters) {
  free(letters);
}
