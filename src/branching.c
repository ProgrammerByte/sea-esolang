#include <stdio.h>
#include <stdlib.h>

#include "branching.h"

int check_label(char **program, int col, int l_col, int l_i, int dir) {
  find_sea_bed(program, col, dir);
  int i = sea_bed + 1;
  while(1) {
    char l = read_value(program, l_col, l_i);
    char v = read_value(program, col, i);
    if (!v) {
      if (l == ' ' || !l) {
        return 1;
      }
      break;
    }
    if (l == v) {
      if (l == ' ') {
        return 1;
      }
      l_col += 1;
      i += 1;
    } else {
      break;
    }
  }
  return 0;
}

int branch_back(char **program, int col, int i, int width, int height) {
  Value *value = fetch_value(i, "\ninvalid register read from back branch at column %d", col);
  if (value_extract_number(value, col) <= 0) {
    int l_col = col + 3;
    for (int col_itr = col; col_itr >= 0; col_itr--) {
      if (check_label(program, col_itr, l_col, i, -1)) {
        return col_itr;
      }
    }
    for (int col_itr = 0; col_itr <= col; col_itr++) {
      find_sea_bed(program, col_itr, 1);
    }
  }
  return -1;
}

int branch_forward(char **program, int col, int i, int width, int height) {
  Value *value = fetch_value(i, "\ninvalid register read from branch forward at column %d", col);
  if (value_extract_number(value, col) <= 0) {
    int l_col = col + 2;
    for (int col_itr = col; col_itr < width - 2; col_itr++) {
      if (check_label(program, col_itr, l_col, i, 1)) {
        return col_itr;
      }
    }
    for (int col_itr = width - 2; col_itr >= col; col_itr--) {
      find_sea_bed(program, col_itr, -1);
    }
  }
  return -1;
}

int branch_back_immediate(char **program, int col, int i, int width, int height) {
  Value *value = fetch_value(i, "\ninvalid register read from branch back immediate at column %d", col);
  int end_column = value_extract_number(value, col);
  if (end_column > col) {
    fprintf(stderr, "\nattempted to branch back when destination was forward at column %d", col);
    exit(1);
  }
  for (int col_itr = col; col_itr >= end_column; col_itr -= 1) {
    find_sea_bed(program, col_itr, -1);
  }
  return end_column;
}

int branch_forward_immediate(char **program, int col, int i, int width, int height) {
  Value *value = fetch_value(i, "\ninvalid register read from branch forward immediate at column %d", col);
  int end_column = value_extract_number(value, col);
  if (end_column < col) {
    fprintf(stderr, "\nattempted to branch forward when destination was backward at column %d", col);
    exit(1);
  }
  for (int col_itr = col; col_itr <= end_column; col_itr += 1) {
    find_sea_bed(program, col_itr, 1);
  }
  return end_column;
}
