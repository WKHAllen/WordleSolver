#include <stdio.h>
#include <string.h>
#include "globals.h"

size_t get_file_line(FILE *fp, char *line, const int max) {
  if (fgets(line, max, fp) == NULL) {
    return 0;
  } else {
    size_t linelen = strlen(line);
    line[linelen - 1] = '\0';
    return linelen - 1;
  }
}

size_t input(const char *prompt, char *line, const int max) {
  printf(prompt);
  return get_file_line(stdin, line, max);
}

void pause(const char *prompt) {
  printf(prompt);
  getchar();
}

BOOL is_letter(const char chr) {
  return (chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z');
}

char *to_upper(const char *str) {
  char *upcase = strdup(str);

  for (int i = 0; upcase[i] != '\0'; i++) {
    if (upcase[i] >= 'a' && upcase[i] <= 'z') {
      upcase[i] += 'A' - 'a';
    }
  }

  return upcase;
}

char *to_lower(const char *str) {
  char *lowcase = strdup(str);

  for (int i = 0; lowcase[i] != '\0'; i++) {
    if (lowcase[i] >= 'A' && lowcase[i] <= 'Z') {
      lowcase[i] += 'a' - 'A';
    }
  }

  return lowcase;
}

char to_upper_char(const char chr) {
  if (chr >= 'a' && chr <= 'z') {
    return chr + ('A' - 'a');
  }

  return chr;
}

char to_lower_char(const char chr) {
  if (chr >= 'A' && chr <= 'Z') {
    return chr + ('a' - 'A');
  }

  return chr;
}
