/*
RUBIX CUBE 2000 
Copyright (c) July 2024 - jp@armstrong.sh
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "rubix.h"

#define RUBIX_SIZE 55
byte cube_[RUBIX_SIZE]; // prev state


// rotation matrix
const byte F[] = {6, 3, 0, 7, 4, 1, 8, 5, 2};

// adjacency matrix (face and rotation: T, R, L, B)
const byte X[][4] = {
  {0x40, 0x30, 0x20, 0x10}, // U
  {0x02, 0x22, 0x52, 0x41}, // L
  {0x03, 0x32, 0x50, 0x11}, // F
  {0x01, 0x42, 0x51, 0x21}, // R
  {0x00, 0x12, 0x53, 0x31}, // B
  {0x13, 0x23, 0x33, 0x43}  // D
};

// adjacent edges
const byte E[][4] = {
  {0, 1, 2}, // TOP
  {2, 5, 8}, // RIGHT
  {0, 3, 6}, // LEFT
  {6, 7, 8}  // BOTTOM
};


// get face and rotation from adjacent matrix
#define fs(x, y) ((X[x][y] & 0xF0) >> 4)
#define as(x, y)  (X[x][y] & 0x07)
#define ss(x, y, z) ((z>0xF0)!=((X[x][y] & 0x08) >> 3))

void rotate_face(byte *cube, byte f, byte a) {
  for(int i=0;i<9;i++) {
    cube[f*9+F[8-i]] = cube_[f*9 + i];
  }
}

// f = face, a = number of rotations
void rotate(byte *cube, byte f, byte a) {
  while(a--%4) {
    // copy prev state
    memcpy(cube_, cube, 55);
    rotate_face(cube, f, a);
 
    int n = 0;
    for(int i=0;i<4;i++) {
      for(int j=0;j<3;j++) {
        n = (4+i-1)%4;
        int js =  E[as(f,n)][(i%2==0)?(2-j):j];
        printf("js: %d, %d, %d, %d \n", a, (i%2==1)?(2-i):j, j, js);
        *(cube + fs(f,i)*9 + E[as(f,i)][j]) = *(cube_ + (fs(f,n)*9) + js);
      }
    }
  }
}

void reset(byte* cube) {  
  srand(time(NULL));
  for (int i=0;i<6;i++) {
    for (int j=0;j<9;j++) {
      cube[i*9+j] = i;
    }
  }
}

void scramble(byte* cube) {
  int n=5;
  for(int i=0;i<n;i++) {
     int cmd = rand() % 6 + 1;
     int rot = rand() % 2 + 1;
     rotate(cube, cmd, rot ? -1 : 1);
  }
}

