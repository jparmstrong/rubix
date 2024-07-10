#include <stdio.h>
#include "print.h"

const char *blocks[] = {
    "\x1B[47m  \x1b[0m\0",
    "\x1B[43m  \x1b[0m\0",
    "\x1B[42m  \x1b[0m\0",
    "\x1B[41m  \x1b[0m\0",
    "\x1B[44m  \x1b[0m\0",
    "\x1B[45m  \x1b[0m\0"
};

int print_side(byte* cube, Side side, byte padding) {
    for (int i=0; i<9; i++) {
        if (i%3==0&padding) printf("\n      ");
        int a = cube[side*9+i];
        printf(blocks[a]);
    }
    printf("\n");
}

int print_cube(byte* cube) {
    print_side(cube, TOP, 1);

    for (int j=0; j<3; j++) {
        for (Side i=BOTTOM; i<=RIGHT; i++) {
            for (int k=0; k<3; k++) {
                int a = cube[i*9 + j + k];
                printf(blocks[a]);
            }
        }
        if(j<2) printf("\n");
    }
    print_side(cube, BACK, 1);
}

int print(byte* cube) {
  for (int i=0;i<54;i++) {
    if(i%9==0) printf("\n");
    printf("%d ", cube[i]);
  } 
  printf("\n");
}

