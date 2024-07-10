#include<stdio.h>
#define byte char

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

// Source: https://stackoverflow.com/a/62558531
const byte // symmetry
  M[] = {2,4,3,5},
  I[] = {2,0,4,6};

byte cube[55]; // 0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1, ... need to be filled first

#define m9(f, m) (m6(f, m)*9)

byte m6(byte f, byte m) {return ((f&~1)+M[m+(f&1)*(3-2*m)])%6;}

void swap(byte a, byte b, byte n) {
  while (n--) {byte t=cube[a+n]; cube[a+n]=cube[b+n]; cube[b+n]=t;}
}

void rotate(byte f, byte a) { // where f is face, and a is number of 90 degree turns
  int c=m9(f, 3), i;
  swap(c, c+8, 1);
  while (a--%4) for (i=2; i>=0; --i)
    swap(m9(f, i) + I[i], m9(f, i+1) + I[i+1], 3),
    swap(f*9+i*2, f*9+i*2+2, 2);
  swap(c, c+8, 1);
}

int print_side(Side side, byte padding) {
    for (int i=0; i<9; i++) {
        if (i%3==0&padding) printf("\n      ");
        int a = cube[side*9+i];
        printf(blocks[a]);
    }
    printf("\n");
}

int print_cube() {
    print_side(TOP, 1);

    for (int j=0; j<3; j++) {
        for (Side i=BOTTOM; i<=RIGHT; i++) {
            for (int k=0; k<3; k++) {
                int a = cube[i*9 + j + k];
                printf(blocks[a]);
            }
        }
        if(j<2) printf("\n");
    }
    print_side(BACK, 1);
}

int print() {
  for (int i=0;i<54;i++) {
    if(i%9==0) printf("\n");
    printf("%d ", cube[i]);
  } 
  printf("\n");
}

int main() {
  for (int i=0;i<9;i++) {
    for (int j=0;j<9;j++) {
      cube[i*9+j] = i;
    }
  }
  print_cube();
  //printf("%d \n", m9(0, 3));
  //swap(0, 51, 3);
  for (int i=0;i<4;i++)
    rotate(0, 1), print_cube();
}


