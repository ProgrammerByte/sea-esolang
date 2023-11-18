#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "terrain.h"

void print_values() {
  for (int i = 0; i < values->items; i++) {
    Value *val = values->values[i];
    switch(val->type) {
      case 'i':
        printf("%d", val->data.i);
        break;
      case 'f':
        printf("%g", val->data.f);
        break;
      default:
        printf("undefined");
        break;
    }
    if (i < values->items - 1) {
      printf(", ");
    }
  }
}

int sea_level = -1;
int sea_bed = -1;

void find_sea_level(char **program) {
  int col = 0;
  sea_level = -1;
  for (int i = 0; *(program + i); i++) {
    char c = read_value(program, col, i);
    if (c == '-') {
      sea_level = i;
    }
  }
}

void find_sea_bed(char **program, int column, int dir) {
  int last = sea_bed;
  int start = 0;
  if (program[sea_level][column] == '-') {
    start = sea_level + 1;
  }
  sea_bed = -1;
  for (int i = start; *(program + i); i++) {
    switch(program[i][column]) {
      case '_':
        if (last < 0 && i != last && column > 0) {
          fprintf(stderr, "\ninconsistent sea bed floor at column %d", column);
          exit(1);
        }
        sea_bed = i;
        break;
      case '/':
        if (last < 0 && last + 1 != i) {
          fprintf(stderr, "\ninvalid sea bed up slope at column %d", column);
          exit(1);
        }
        if (i > sea_level + 1) {
          if (dir == -1) {
            values = array_append(values, array_pop(reserve_l));
          } else if (dir == 1) {
            reserve_l = array_append(reserve_l, array_pop(values));
          }
        }
        sea_bed = i;
        break;
      case '\\':
        if (last < 0 && last - 1 != i) {
          fprintf(stderr, "\ninvalid sea bed down slope at column %d", column);
          exit(1);
        }
        if (i > sea_level + 1) {
          if (dir == -1) {
            reserve_r = array_append(reserve_r, array_pop(values));
          } else if (dir == 1) {
            values = array_append(values, array_pop(reserve_r));
          }
        }
        sea_bed = i;
        break;
    }
    if (sea_bed != -1) {
      break;
    }
  }
  if (last == -1 && sea_bed != -1) {
    if (column == 0) {
      values = array_create((sea_bed - sea_level) - 1);
      reserve_l = array_create(0);
      reserve_r = array_create(0);
    } else {
      fprintf(stderr, "\nsea bed not found at column %d", column - 1);
      exit(1);
    }
  }
}