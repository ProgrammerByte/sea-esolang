#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "dynamic_array.h"
#include "grid_funcs.h"

Array *values;
Array *reserve_l;
Array *reserve_r;

extern int sea_level;
extern int sea_bed;

void print_values();
void find_sea_level(char **program);
void find_sea_bed(char **program, int column, int dir);

#endif