#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_reader.h"

char **create_program(char *filename) {
  FILE *file = fopen(filename, "rb");
  long length;
  char *buffer;

  if (!file) {
    fprintf(stderr, "\nsource file \"%s\" not found\n", filename);
    return 0;
  }

  fseek(file, 0L, SEEK_END);
  length = ftell(file);
  rewind(file);

  buffer = malloc(sizeof(char) * length);
  if(!buffer) {
    fclose(file);
    fprintf(stderr, "\ncould not create file buffer\n");
    return 0;
  }

  if(1 != fread(buffer, length, 1, file)) {
    fclose(file);
    free(buffer);
    fprintf(stderr, "\ncould not load file data into buffer\n");
    return 0;
  }
  fclose(file);

  char** program = create_grid(buffer);
  free(buffer);
  if (!program) {
    fprintf(stderr, "\ncould not create program\n");
    return 0;
  }
  return program;
}