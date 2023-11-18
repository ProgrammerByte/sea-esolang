#ifndef PATTERNS_H_
#define PATTERNS_H_

#include "grid_funcs.h"

int check_fisherman(char **program, int col, int i);
int check_diver(char **program, int col, int i);

int check_addition(char **program, int col, int i);
int check_subtraction(char **program, int col, int i);
int check_division(char **program, int col, int i);
int check_multiplication(char **program, int col, int i);

int check_reverse_addition(char **program, int col, int i);
int check_reverse_subtraction(char **program, int col, int i);
int check_reverse_division(char **program, int col, int i);
int check_reverse_multiplication(char **program, int col, int i);

int check_branch_back(char **program, int col, int i);
int check_branch_forward(char **program, int col, int i);
int check_branch_back_immediate(char **program, int col, int i);
int check_branch_forward_immediate(char **program, int col, int i);

#endif