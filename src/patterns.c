#include <stdlib.h>

#include "patterns.h"

int check_pattern(char **program, char **pattern, int col, int i, int pcol, int pi, int pwidth, int pheight) { // p = pattern
  int min_col = col - pcol;
  int min_i = i - pi;
  for(int itr_col = 0; itr_col < pwidth; itr_col++) {
    for (int itr_i = 0; itr_i < pheight; itr_i++) {
      char pattern_char = read_value(pattern, itr_col, itr_i);
      char program_char = read_value(program, min_col + itr_col, min_i + itr_i);
      if (pattern_char != ' ' && pattern_char != program_char) {
        return 0;
      }
    }
  }
  return 1;
}

int check_fisherman(char **program, int col, int i) {
  char* operator =
    "O _  \n"
    "L/ \\ \n"
    "A   |\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 2, 5, 3);
  free_grid(pattern);
  return result;
}

int check_diver(char **program, int col, int i) {
  char* operator =
    "O\n"
    "|\n"
    "^\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 1, 1, 3);
  free_grid(pattern);
  return result;
}

int check_addition(char **program, int col, int i) {
  char* operator =
    " > \n"
    ">>>\n"
    " > \n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 1, 3, 3);
  free_grid(pattern);
  return result;
}

int check_subtraction(char **program, int col, int i) {
  char* operator =
    ">>>\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 0, 3, 1);
  free_grid(pattern);
  return result;
}

int check_division(char **program, int col, int i) {
  char* operator =
    "  >\n"
    " > \n"
    ">  \n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 2, 3, 3);
  free_grid(pattern);
  return result;
}

int check_multiplication(char **program, int col, int i) {
  char* operator =
    "> >\n"
    " > \n"
    "> >\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 2, 3, 3);
  free_grid(pattern);
  return result;
}

int check_reverse_addition(char **program, int col, int i) {
  char* operator =
    " < \n"
    "<<<\n"
    " < \n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 1, 3, 3);
  free_grid(pattern);
  return result;
}

int check_reverse_subtraction(char **program, int col, int i) {
  char* operator =
    "<<<\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 0, 3, 1);
  free_grid(pattern);
  return result;
}

int check_reverse_division(char **program, int col, int i) {
  char* operator =
    "  <\n"
    " < \n"
    "<  \n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 2, 3, 3);
  free_grid(pattern);
  return result;
}

int check_reverse_multiplication(char **program, int col, int i) {
  char* operator =
    "< <\n"
    " < \n"
    "< <\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 2, 3, 3);
  free_grid(pattern);
  return result;
}

int check_branch_back(char **program, int col, int i) {
  char* operator =
    "<-\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 0, 2, 1);
  free_grid(pattern);
  return result;
}

int check_branch_forward(char **program, int col, int i) {
  char* operator =
    "->\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 1, 0, 2, 1);
  free_grid(pattern);
  return result;
}

int check_branch_back_immediate(char **program, int col, int i) {
  char* operator =
    "<~\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 0, 0, 2, 1);
  free_grid(pattern);
  return result;
}

int check_branch_forward_immediate(char **program, int col, int i) {
  char* operator =
    "~>\n"
  ;
  char **pattern = create_grid(operator);
  int result = check_pattern(program, pattern, col, i, 1, 0, 2, 1);
  free_grid(pattern);
  return result;
}