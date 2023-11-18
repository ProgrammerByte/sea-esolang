#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid_funcs.h"
#include "file_reader.h"
#include "patterns.h"
#include "cell_locator.h"
#include "operators.h"
#include "branching.h"

extern int sea_level;
extern int sea_bed;

int run_program(char **program) {
  find_sea_level(program);
  if (sea_level == -1) {
    fprintf(stderr, "\nat least one sea level token \"-\", \",\", or \".\" must be specified in column 0\n");
    return 1;
  }
  int width = 0;
  int height = 0;
  for (int i = 0; *(program + i); i++) {
    height += 1;
  }
  for (int col = 0; *((*program) + col); col++) {
    width += 1;
  }
  for (int col = 0; col < width; col++) {
    find_sea_bed(program, col, 1);
    for (int i = 0; i < height; i++) {
      char c = read_value(program, col, i);
      if (c) {
        if (i == sea_level && sea_bed > sea_level) {
          switch(c) {
            case '-':
            case '.':
            case ',':
              break;
            case 'A':
              if (check_fisherman(program, col, i)) {
                access_fisherman(program, col, i, width, height);
              }
              break;
            case '|':
              if (check_diver(program, col, i)) {
                seek_initialise(col, i, 1);
                Value *value = seek_next_register(program, width, height);
                value->type = 'i';
                value->data.i = getchar();
                seek_cleanup(program, col);
              }
              break;
            default:
              fprintf(stderr, "\ninconsistent sea level found at %d\n", col);
              exit(1);
          }
        } else {
          switch(c) {
            case '>':
              if (check_addition(program, col, i)) {
                binary_operator(program, col, i, width, height, '+', 1);
              } else if (check_subtraction(program, col, i)) {
                binary_operator(program, col, i, width, height, '-', 1);
              } else if (check_multiplication(program, col, i)) {
                binary_operator(program, col, i, width, height, '*', 1);
              } else if (check_division(program, col, i)) {
                binary_operator(program, col, i, width, height, '/', 1);
              } else if (check_branch_forward(program, col, i)) {
                int branch = branch_forward(program, col, i, width, height);
                if (branch >= 0) {
                  col = branch;
                  i = 0;
                }
              } else if (check_branch_forward_immediate(program, col, i)) {
                int branch = branch_forward_immediate(program, col, i, width, height);
                if (branch >= 0) {
                  col = branch;
                  i = 0;
                }
              }
            case '<':
              if (check_reverse_addition(program, col, i)) {
                binary_operator(program, col, i, width, height, '+', -1);
              } else if (check_reverse_subtraction(program, col, i)) {
                binary_operator(program, col, i, width, height, '-', -1);
              } else if (check_reverse_multiplication(program, col, i)) {
                binary_operator(program, col, i, width, height, '*', -1);
              } else if (check_reverse_division(program, col, i)) {
                binary_operator(program, col, i, width, height, '/', -1);
              } else if (check_branch_back(program, col, i)) {
                int branch = branch_back(program, col, i, width, height);
                if (branch >= 0) {
                  col = branch;
                  i = 0;
                }
              } else if (check_branch_back_immediate(program, col, i)) {
                int branch = branch_back_immediate(program, col, i, width, height);
                if (branch >= 0) {
                  col = branch;
                  i = 0;
                }
              }
              break;
            case '@':
              printf("\nbreakpoint character detected at column %d, values:\n", col);
              print_values();
              printf("\n");
              break;
            default:
              break;
          }
        }
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "\nUsage: sea <filename>");
    return 1;
  }

  char **program = create_program(argv[1]);
  if (!program) {
    fprintf(stderr, "\nunable to load program");
    return 1;
  }
  int code = run_program(program);
  free_grid(program);
  return code;
}