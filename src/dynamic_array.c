#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

Array *array_create(int length) {
  int pow = 1;
  while (pow < length) {
    pow = pow << 1;
  }
  Array* array = malloc(sizeof(Array));
  array->capacity = pow;
  array->items = length;
  array->values = malloc(sizeof(Value *) * pow);
  for (int i = 0; i < pow; i++) {
    array->values[i] = malloc(sizeof(Value));
    array->values[i]->type = '\0';
    array->values[i]->temporary = 0;
    array->values[i]->data.f = 0;
  }
  return array;
}

Array *array_append(Array *a, Value *value) {
  if (a->items < a->capacity) {
    a->values[a->items] = value;
    a->items += 1;
    return a;
  }
  Array *new = malloc(sizeof(Array));
  new->capacity = a->capacity * 2;
  new->items = a->items + 1;
  new->values = malloc(sizeof(Value) * new->capacity);
  for (int i = 0; i < a->capacity; i++) {
    new->values[i] = a->values[i];
  }
  new->values[a->capacity] = value;
  array_free(a);
  return new;
}

Value *array_pop(Array *a) {
  if (a->items <= 0) {
    Value *result = malloc(sizeof(Value));
    result->type = '\0';
    result->temporary = 0;
    result->data.f = 0;
    return result;
  }
  a->items -= 1;
  return a->values[a->items];
}

void array_free(Array *a) {
  free(a->values);
  free(a);
}

int value_numeric(Value *v) {
  return v->type == 'i' || v->type == 'f';
}

float value_extract_number(Value *v, int col) {
  if (v->type == 'i') {
    return v->data.i;
  } else if (v->type == 'f') {
    return v->data.f;
  }
  fprintf(stderr, "\nattempted to extract a number from a non-numerical value at column %d", col);
  exit(1);
}

void value_free(Value *v) {
  if (v->temporary) {
    free(v);
  }
}