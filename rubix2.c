#include <stdio.h>
#include "print.h"

byte cube[55];

// Source: https://stackoverflow.com/a/62558531
const byte // symmetry
  M[] = {2,4,3,5},
  I[] = {2,0,4,6};

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

int main() {
  for (int i=0;i<6;i++) {
    for (int j=0;j<9;j++) {
      cube[i*9+j] = i;
    }
  }

  // swap(9, 18, 3);
  print_cube(cube);
  print_nums(cube);

  printf("%d \n", m9(0, 3));
  //for (int i=0;i<4;i++)
  rotate(0, 1), print_cube(cube);
  print_nums(cube);
}


