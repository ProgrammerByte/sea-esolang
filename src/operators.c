#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operators.h"

void binary_operator(char** program, int col, int i, int width, int height, char op, int dir) {
  seek_initialise(col, 0, dir);
  Value *v1 = seek_next_value(program, width, height);
  Value *v2 = seek_next_value(program, width, height);
  Value *store = seek_next_register(program, width, height);
  if (v1->type == 'i' && v2->type == 'i') {
    store->type = 'i';
    switch(op) {
      case '+':
        store->data.i = v1->data.i + v2->data.i;
        break;
      case '-':
        store->data.i = v1->data.i - v2->data.i;
        break;
      case '/':
        store->data.i = v1->data.i / v2->data.i;
        break;
      case '*':
        store->data.i = v1->data.i * v2->data.i;
        break;
      default:
        fprintf(stderr, "\ninvalid integer operator used at column %d\n", col);
        exit(1);
        break;
    }
  } else if (value_numeric(v1) && value_numeric(v2)) {
    store->type = 'f';
    switch(op) {
      case '+':
        store->data.f = value_extract_number(v1, col) + value_extract_number(v2, col);
        break;
      case '-':
        store->data.f = value_extract_number(v1, col) - value_extract_number(v2, col);
        break;
      case '/':
        store->data.f = value_extract_number(v1, col) / value_extract_number(v2, col);
        break;
      case '*':
        store->data.f = value_extract_number(v1, col) * value_extract_number(v2, col);
        break;
      default:
        fprintf(stderr, "\ninvalid floating point operator used at column %d\n", col);
        exit(1);
        break;
    }
  }
  value_free(v1);
  value_free(v2);
  seek_cleanup(program, col);
}