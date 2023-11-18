#ifndef CELL_LOCATOR_H_
#define CELL_LOCATOR_H_

#include "grid_funcs.h"
#include "terrain.h"

void access_fisherman(char **program, int col, int i, int width, int height);
void seek_initialise(int col, int i, int dir);
void seek_cleanup(char **program, int col);
Value *fetch_value(int i, const char *error, int col);
Value *seek_next_register(char **program, int width, int height);
Value *seek_next_immediate(char **program, int width, int height);
Value *seek_next_value(char **program, int width, int height);

#endif