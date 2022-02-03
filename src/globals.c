#include <stdio.h>
#include <string.h>
#include "globals.h"

/*
 * Get a full line from a file.
 */
size_t get_file_line(FILE *fp, char *line, int max) {
  if (fgets(line, max, fp) == NULL) {
    return 0;
  } else {
    size_t linelen = strlen(line);
    line[linelen - 1] = '\0';
    return linelen - 1;
  }
}
