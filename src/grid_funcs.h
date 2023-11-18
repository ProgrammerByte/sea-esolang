#ifndef GRID_FUNCS_H_
#define GRID_FUNCS_H_

char **create_grid(char *str);
void free_grid(char **grid);
char read_value(char **grid, int col, int row);

#endif