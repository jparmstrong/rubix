#include <stdio.h>
#include <stdbool.h>

typedef enum sides {
    TOP, BOTTOM, LEFT, FRONT, RIGHT, BACK
} Side;

enum colors {
    WHITE, YELLOW, GREEN, RED, BLUE, ORANGE
};

const char *blocks[] = {
    "\x1B[47m  \x1b[0m\0",
    "\x1B[43m  \x1b[0m\0",
    "\x1B[42m  \x1b[0m\0",
    "\x1B[41m  \x1b[0m\0",
    "\x1B[44m  \x1b[0m\0",
    "\x1B[45m  \x1b[0m\0"
};

typedef struct Cube {
    int sides[6][3][3];
} Cube;

int print_side(Cube cube, Side side, bool padding) {
    for (int j=0; j<3; j++) {
        if (padding) printf("      ");
        for (int k=0; k<3; k++) {
            int a = cube.sides[side][j][k];
            printf(blocks[a]);
        }
        printf("\n");
    }
}

int print_cube(Cube cube) {
    print_side(cube, TOP, true);
    for (int j=0; j<3; j++) {
        for (Side i=BOTTOM; i<=RIGHT; i++) {
            for (int k=0; k<3; k++) {
                int a = cube.sides[i][j][k];
                printf(blocks[a]);
            }
        }
        printf("\n");
    }
    print_side(cube, BACK, true);
}

int main() {
    Cube cube = {};
    for (int i=TOP; i<=BACK; i++) {
        for (int j=0; j<3; j++)
            for (int k=0; k<3; k++)
                cube.sides[i][j][k] = i;
    }
    print_cube(cube);
}
