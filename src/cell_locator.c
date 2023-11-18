#include <stdio.h>
#include <stdlib.h>

#include "cell_locator.h"

Value *fetch_value(int i, const char *error, int col) {
  int idx = (i - sea_level) - 1;
  if (idx >= values->items) {
    fprintf(stderr, error, col);
    exit(1);
  }
  return values->values[idx];
}

void access_fisherman(char **program, int col, int i, int width, int height) {
  col += 4;
  i += 1;
  if (col >= width) {
    fprintf(stderr, "\nillegal attempt to access fisherman at column %d", col);
    exit(1);
  }
  while(i < height && program[i][col] != '0' && program[i][col] != 'o') {
    i += 1;
  }
  Value *value = fetch_value(i, "\na fishing pole attempted to make an illegal access at column %d", col);
  if (program[i][col] == '0') {
    switch(value->type) {
      case 'i':
        printf("%d", value->data.i);
        break;
      case 'f':
        printf("%g", value->data.f);
        break;
      default:
        fprintf(stderr, "\nattempt to output a non-numerical value as a numerical value at column %d", col);
        exit(1);
    }
  } else {
    if (value->type == 'i') {
      printf("%c", value->data.i);
    } else {
      fprintf(stderr, "\nattempt to output an invalid data type as a char at column %d", col);
      exit(1);
    }
  }
}

int seek_col = -1;
int seek_i = -1;
int seek_dir = 0;

void seek_initialise(int col, int i, int dir) {
  seek_col = col;
  seek_i = i;
  seek_dir = dir;
}

void seek_cleanup(char **program, int col) {
  for (int col_itr = seek_col; col_itr != col; col_itr -= seek_dir) {
    find_sea_bed(program, col_itr, -seek_dir);
  }
  seek_col = -1;
  seek_i = -1;
  seek_dir = 0;
}

Value *seek_next_value_i(char **program, int width, int height, int include_registers, int include_literals) {
  if (seek_col < 0 || seek_i < 0) {
    fprintf(stderr, "\nattempt to fetch value without initialising seek");
    exit(1);
  }
  for (int col_itr = seek_col; col_itr >= 0 && col_itr < width; col_itr += seek_dir) {
    if (col_itr != seek_col) {
      find_sea_bed(program, col_itr, seek_dir);
    }
    if (include_literals && (seek_i <= sea_level || col_itr != seek_col)) {
      if (read_value(program, col_itr, sea_level) == '.') {
        float value = 0;
        float pow = 1;
        char curr;
        for (int i_itr = sea_level - 1; i_itr >= 0; i_itr--) {
          curr = read_value(program, col_itr, i_itr);
          if (curr >= '0' && curr <= '9') {
            value += (curr - '0') * pow;
            pow *= 10;
          } else {
            break;
          }
        }
        pow = 0.1f;
        curr = read_value(program, col_itr, sea_level + 1);
        Value *result = malloc(sizeof(Value));
        result->temporary = 1;
        seek_i = sea_level + 1;
        if (curr >= '0' && curr <= '9') { // floating_point
          for (int i_itr = sea_level + 1; i_itr < height; i_itr++) {
            curr = read_value(program, col_itr, i_itr);
            if (curr >= '0' && curr <= '9') {
              value += (curr - '0') * pow;
              pow /= 10;
            } else {
              break;
            }
          }
          result->type = 'f';
          result->data.f = value;
        } else {
          result->type = 'i';
          result->data.i = value;
        }
        seek_col = col_itr;
        return result;
      } else if (read_value(program, col_itr, sea_level) == ',') { // char
        Value *result = malloc(sizeof(Value));
        result->temporary = 1;
        result->type = 'i';
        result->data.i = read_value(program, col_itr, sea_level - 1);
        seek_i = sea_level + 1;
        seek_col = col_itr;
        return result;
      }
    }
    if (include_registers) {
      for (int i_itr = (col_itr == seek_col ? seek_i : 0); i_itr < height; i_itr++) {
        if (read_value(program, col_itr, i_itr) == 'X') {
          Value* result = fetch_value(i_itr, "\nillegal memory access at column %d", col_itr);
          seek_col = col_itr;
          seek_i = i_itr + 1;
          return result;
        }
      }
    }
  }
  return NULL;
}

Value *seek_next_register(char **program, int width, int height) {
  Value *result = seek_next_value_i(program, width, height, 1, 0);
  if (!result) {
    fprintf(stderr, "\ncould not locate another X starting from column %d", seek_col);
    exit(1);
  }
  return result;
}

Value *seek_next_immediate(char **program, int width, int height) {
  Value *result = seek_next_value_i(program, width, height, 0, 1);
  if (!result) {
    fprintf(stderr, "\ncould not locate floating point value starting from column %d", seek_col);
    exit(1);
  }
  return result;
}

Value *seek_next_value(char **program, int width, int height) {
  Value *result = seek_next_value_i(program, width, height, 1, 1);
  if (!result) {
    fprintf(stderr, "\ncould not locate X or floating point value starting from column %d", seek_col);
    exit(1);
  }
  return result;
}