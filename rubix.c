#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rubix.h"

#define SIZE 55
byte cube[SIZE];
byte cube_[SIZE]; // prev state

// Inspiration: https://stackoverflow.com/questions/500221/how-would-you-represent-a-rubiks-cube-in-code/62558531#62558531

const byte F[] = {6, 3, 0, 7, 4, 1, 8, 5, 2};
const byte A[][6] = {
  { -1,   4,   1,   2,   3,  -1},
  {  2,  -1,   5,  -1,   0,   4},
  {  3,   0,  -1,   5,  -1,   1},
  {  4,  -1,   0,  -1,   5,   2},
  {  1,   5,  -1,   0,  -1,   3},
  { -1,   2,   3,   4,   1,  -1}
};
const byte B[][4] = {
  {0, 1, 2},
  {0, 3, 6},
  {2, 5, 8},
  {6, 7, 8}
};
const byte C[][4] = {
  {0, 0, 0, 0}, // TOP
  {1, 1, 1, 2}, // LEFT
  {3, 1, 0, 2}, // FRONT
  {0, 1, 3, 2}, // RIGHT
  {0, 1, 3, 2}, // BACK
  {3, 3, 3, 3}  // BOTTOM
};

// f = face, a = number of rotations
void rotate(byte f, byte a) {
  while(a--%4) {
    // copy prev state
    memcpy(cube_, cube, 55);

    // face
    for(int i=0;i<9;i++)
      cube[f*9+F[8-i]] = cube_[f*9 + i];
    
    // adj faces
    int i_ = 0;
    for(int i=0;i<6;i++) {
      if(A[f][i] == -1) continue;
      byte f_ = A[f][i];
      for(int k=0;k<3;k++) {
         byte s = B[C[f][i_]][k];
         printf("f: %d, f_: %d, i_: %d, k: %d, s: %d\n", f, f_, i_, k, s);
         *(cube + f_*9 + s) = *(cube_ + i*9 + s);
      }
      i_++;
      printf("-\n");
      print_cube(cube);
//     memcpy(cube + A[f][i] * 9, cube_ + i*9, 3);
//      printf("A: %d, %d, %d\n", f, i, A[f][i]);
   }
   print_nums(cube);
   print_cube(cube);
  }
}

int main() {
  for (int i=0;i<6;i++) {
    for (int j=0;j<9;j++) {
      cube[i*9+j] = i; // j
    }
  }

  char cmd[10] = {0};
  char* cmds = "ulfrbd";
  while(1) {
    print_cube(cube);
    printf("> ");

    if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
      return 0;
    }

    *cmd = tolower(*cmd);
  
    if(cmd[0]=='q')
      return 0;

    // Help 
    if(cmd[0]=='?') {
      printf("commands: q ? ");
      for(int j=0;j<6;j++) 
         printf("%c %c' ", cmds[j], cmds[j]);
      printf("\n");
      continue;
    }

    for(int i=0;i<6;i++) {
      if(cmd[0]==cmds[i]) {
        printf("command: %d\n", i);
        rotate(i, (cmd[1] == '\'') ? -1 : 1);
      }
    } 
  } 
}
