DEBUG_FLAGS = -g -fno-omit-frame-pointer -Wall -pedantic

ifeq ($(OS),Windows_NT)
    RM = del /Q /F
else
    RM = rm -f
endif

all:
	gcc -c src/branching.c
	gcc -c src/cell_locator.c
	gcc -c src/dynamic_array.c
	gcc -c src/file_reader.c
	gcc -c src/grid_funcs.c
	gcc -c src/operators.c
	gcc -c src/patterns.c
	gcc -c src/sea.c
	gcc -c src/terrain.c
	gcc -o sea sea.o branching.o cell_locator.o dynamic_array.o file_reader.o grid_funcs.o operators.o patterns.o terrain.o
	${RM} *.o

debug:
	gcc ${DEBUG_FLAGS} -c branching.c
	gcc ${DEBUG_FLAGS} -c cell_locator.c
	gcc ${DEBUG_FLAGS} -c dynamic_array.c
	gcc ${DEBUG_FLAGS} -c file_reader.c
	gcc ${DEBUG_FLAGS} -c grid_funcs.c
	gcc ${DEBUG_FLAGS} -c operators.c
	gcc ${DEBUG_FLAGS} -c patterns.c
	gcc ${DEBUG_FLAGS} -c sea.c
	gcc ${DEBUG_FLAGS} -c terrain.c
	gcc ${DEBUG_FLAGS} -o sea sea.o branching.o cell_locator.o dynamic_array.o file_reader.o grid_funcs.o operators.o patterns.o terrain.o