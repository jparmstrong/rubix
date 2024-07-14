/*
RUBIX CUBE 1000 
Copyright (c) July 2024 - jp@armstrong.sh
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rubix.h"

#define NUM_CUBES 0
#define SIZE 55
byte cube[SIZE];
byte cube_[SIZE]; // prev state

// rotation matrix
const byte F[] = {6, 3, 0, 7, 4, 1, 8, 5, 2};

// adjacency matrix (face and rotation: T, R, L, B)
const byte X[][4] = {
  {0x40, 0x30, 0x20, 0x10},
  {0x02, 0x22, 0x52, 0x41},
  {0x03, 0x32, 0x50, 0x11},
  {0x01, 0x42, 0x51, 0x21},
  {0x00, 0x12, 0x53, 0x31},
  {0x13, 0x23, 0x33, 0x43}
};

// adjacent edges
const byte E[][4] = {
  {0, 1, 2}, // TOP
  {2, 5, 8}, // RIGHT
  {0, 3, 6}, // LEFT
  {6, 7, 8}  // BOTTOM
};

typedef struct Marquee {
  char text[100];
  int size;
  int count;
} Marquee;

// get face and rotation from adjacent matrix
#define fs(x, y) ((X[x][y] & 0xF0) >> 4)
#define as(x, y)  (X[x][y] & 0x0F)


void rotate_face(byte f, byte a) {
  while(a--%4) {
    for(int i=0;i<9;i++)
      cube[f*9+F[8-i]] = cube_[f*9 + i];
  }
}

// f = face, a = number of rotations
void rotate(byte f, byte a) {
  while(a--%4) {
    // copy prev state
    memcpy(cube_, cube, 55);
    rotate_face(f, a);
 
    byte n = 0;
    for(byte i=0;i<4;i++) {
//      printf("projection: 0x%02X,  %d, %d\n", X[f][i], fs(f,i), as(f,i));
      rotate_face(fs(f,i), as(f,i));
      for(byte j=0;j<3;j++) {
        n = (4+i-1)%4;
       // printf("%d, %d, %d \n", fs(f,i), E[as(f,i)][j], n);
        *(cube + fs(f,i)*9 + E[as(f,i)][j]) = *(cube_ + (fs(f,n)*9) + E[as(f,n)][j]);
      }
    }
  }
}

void reset() {  
  for (int i=0;i<6;i++) {
    for (int j=0;j<9;j++) {
      cube[i*9+j] = i;
    }
  }
}

void print_cmd(char* cmd) {
  printf("RUBIX CUBE 1000\nby JP Armstrong - July 2024\n\nCmds: ");

  for(int i=0;cmd[i]!='\0';i++) {
    printf("%c", cmd[i]);
  }
  printf("\n");
}

int main() {
  reset();
  
  int ci = 0;
  char cmd[180] = {0};
  char* cmds = "ulfrbd";
  byte skip = 0;
  while(1) {
    if (!skip) {
        printf("\e[1;1H\e[2J");
        print_cmd(cmd);
        print_cube(cube, NUM_CUBES);
    }
    printf("> ");

    if (fgets(cmd + ci, sizeof(cmd), stdin) == NULL) {
      return 0;
    }
     
    if(skip = cmd[ci]=='\n')
      continue;

    if(cmd[ci]=='q')
      return 0;

    if(cmd[ci]=='c') {
      reset();
      continue;
    }

    // Help 
    if(cmd[ci]=='?') {
      printf("commands: q ? ");
      for(int j=0;j<6;j++) 
         printf("%c %c' ", cmds[j], cmds[j]);
      printf("\n");
      continue;
    }

    for(int i=0;i<6;i++) {
      if(cmd[ci]==cmds[i]) {
        printf("command: %d\n", i);
        rotate(i, (cmd[ci+1] == '\'') ? -1 : 1);
      }
    }
    
    while(cmd[ci]!='\n'&&cmd[ci]!=0) ci++;
    cmd[ci++] = ' ';
  } 
}
