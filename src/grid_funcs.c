#include <stdlib.h>
#include <string.h>

#include "grid_funcs.h"

char *allocate_row(int size) {
  char *result = (char *)malloc(sizeof(char) * (size + 1));
  for (int i = 0; i < size; i++) {
    result[i] = ' ';
  }
  result[size] = '\0';
  return result;
}

char **create_grid(char *str) {
  int columns = 0;
  int rows = 0;
  int total_length = strlen(str) + 1;
  int last = 0;
  for (int i = 0; i < total_length; i++) {
    if (str[i] == '\n' || str[i] == '\0') {
      int curr_columns = i - last;
      if (curr_columns > columns) {
        columns = curr_columns;
      }
      last = i;
      rows += 1;
    }
  }

  char **result = (char **)malloc(sizeof(char *) * (rows + 1));
  result[rows] = NULL;
  int curr_row = 0;
  int curr_col = 0;
  result[curr_row] = allocate_row(columns);
  for (int i = 0; i < total_length - 1; i++) {
    if (str[i] == '\n') {
      curr_row += 1;
      if(curr_row < rows) {
        result[curr_row] = allocate_row(columns);
      } else {
        break;
      }
      curr_col = 0;
    } else {
      result[curr_row][curr_col] = str[i];
      curr_col += 1;
    }
  }
  return result;
}

void free_grid(char **grid) {
  if (grid) {
    for (int i = 0; *(grid + i); i++) {
      free(*(grid + i));
    }
    free(grid);
  }
}

char read_value(char **grid, int col, int row) {
  if (col < 0 || row < 0 || !*(grid + row)) {
    return 0;
  }
  return *(*(grid + row) + col);
}