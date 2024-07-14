#include <stdbool.h>
#define byte unsigned char

typedef enum sides {
    TOP, LEFT, FRONT, RIGHT, BACK, BOTTOM
} Side;

int print_cube(byte*, bool);

int print(byte*);

int print_nums(byte*);

void rotate(byte*, byte, byte);

void rotate_face(byte*, byte, byte);

void reset(byte*);

void scramble(byte*);

