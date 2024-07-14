#include <stdbool.h>
#define byte unsigned char

typedef enum sides {
    TOP, LEFT, FRONT, RIGHT, BACK, BOTTOM
} Side;

int print_cube(byte*, bool);

int print(byte*);

int print_nums(byte* cube);
