#include <stdbool.h>
#define byte unsigned char

typedef enum sides {
    TOP, LEFT, FRONT, RIGHT, BACK, BOTTOM
} Side;

void rotate(byte*, byte, byte);

void rotate_face(byte*, byte, byte);

void reset(byte*);

void scramble(byte*);

