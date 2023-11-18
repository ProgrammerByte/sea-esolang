#ifndef BRANCHING_H_
#define BRANCHING_H_

#include "cell_locator.h"
#include "grid_funcs.h"
#include "terrain.h"

int branch_back(char **program, int col, int i, int width, int height);
int branch_forward(char **program, int col, int i, int width, int height);
int branch_back_immediate(char **program, int col, int i, int width, int height);
int branch_forward_immediate(char **program, int col, int i, int width, int height);

#endif