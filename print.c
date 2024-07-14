#include <stdio.h>
#include <stdbool.h>
#include "rubix.h"

const char *blocks[] = {
    "\x1B[30;47m %c\x1b[0m\0", // WHITE
    "\x1B[30;45m %c\x1b[0m\0", // MAGENTA
    "\x1B[30;42m %c\x1b[0m\0", // GREEN
    "\x1B[30;41m %c\x1b[0m\0", // RED
    "\x1B[30;44m %c\x1b[0m\0", // BLUE
    "\x1B[30;43m %c\x1b[0m\0"  // YELLOW
};

int print_nums(byte* cube) {
  for (int i=0;i<6;i++) {
    for (int j=0;j<9;j++) {
      int a = cube[i*9+j];
      printf(blocks[a],'0'+a);
    }
    printf("\n");
  }
}

int print_side(byte* cube, Side side, bool padding, bool num) {
    for (int i=0; i<9; i++) {
        if (i%3==0&padding) printf("\n      ");
        int a = cube[side*9+i];
        printf(blocks[a], !num ? ' ' : '0' + i);
    }
    printf("\n");
}

int print_cube(byte* cube, bool num) {
    print_side(cube, TOP, 1, num);

    for (int j=0; j<3; j++) {
        for (Side i=LEFT; i<=BACK; i++) {
            for (int k=0; k<3; k++) {
                int a = cube[i*9 + j*3 + k];
                // printf("%d ", j*3 +k);
                printf(blocks[a], !num ? ' ' : '0' + j*3+k);
            }
        }
        if(j<2) printf("\n");
    }
    print_side(cube, BOTTOM, 1, num);
}

int print_line(byte* cube) {
  for (int i=0;i<54;i++) {
    if(i%9==0) printf("\n");
    printf("%d ", cube[i]);
  } 
  printf("\n");
}

