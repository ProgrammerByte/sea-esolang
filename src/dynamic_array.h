#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#define EMPTY_VALUE (Value) {.type = '\0', .temporary = 0, .data = {.f = 0}}

typedef union {
  float f;
  int i;
} Data;

typedef struct {
  char type;
  int temporary;
  Data data;
} Value;

typedef struct {
  int capacity;
  int items;
  Value **values;
} Array;

Array *array_create(int length);
Array *array_append(Array *a, Value *value);
Value *array_pop(Array *a);
void array_free(Array *a);

int value_numeric(Value *v);
float value_extract_number(Value *v, int col);
void value_free(Value *v);

#endif