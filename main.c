#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "rubix.h"
#include "print.h"

// Debug flag, enables numbers in cube output
#define NUM_CUBES 0
#define RUBIX_SIZE 55
byte cube[RUBIX_SIZE];

const char* cmds = "ulfrbd";

void print_cmd(char* cmd) {
  printf(
    "~ RUBIX CUBE 2000 ~~~~~~~~~~~~~~~\n"
    "~ jp@armstrong.sh (c) July 2024 ~\n"
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    "? for help ~ cmds: "
  );

  for(int i=0;cmd[i]!='\0';i++) {
    printf("%c", cmd[i]);
  }
  printf("\n");
}

void usage() {
  printf(
    "\nUSAGE: \n"
    "q        quit\n"
    "?        help\n"
    "!        debug mode\n"
    "c        reset cube\n"
    "s        scramble cube\n"
    "turn cube clockwise (counter-clockwise):\n"
    "u (u')   turn up face\n"
    "l (l')   turn left face\n"
    "r (r')   turn right face\n"
    "f (f')   turn front face\n"
    "b (b')   turn back face\n"
    "d (d')   turn down face\n"
    "\n"
  );
}


int execute(byte* cube, char* cmd, int ci) {
  while(cmd[ci]!='\0'&&cmd[ci]!='\n') {
    if (cmd[ci]>='A' && cmd[ci]<='Z') {
      cmd[ci] += 32;
    }
    for(int i=0;i<6;i++) {
      if(cmd[ci]==cmds[i]) {
        if(cmd[ci+1]>='1'&&cmd[ci+1]<='4'){
          rotate(cube, i, cmd[ci+1]-'0');
          ci++;
        }
        else if(cmd[ci+1] == '\'') {
          rotate(cube, i, -1);
          ci++;
        } else {
          rotate(cube, i, 1);
        }
        break;
      }
    }
    ci++;
  }
  return ci;
}

void prompt() {
  reset(cube);
  
  int ci = 0;
  char cmd[1024] = {0};
  byte skip = 0;
  byte debug = 0;
  while(1) {
    if (!skip) {
        printf("\e[1;1H\e[2J");
        print_cmd(cmd);
        print_cube(cube, NUM_CUBES);
    }

    if(debug) {
      printf("\n");
      print_nums(cube);
      printf("\n");
    }

    printf("> ");

    if (fgets(cmd + ci, sizeof(cmd), stdin) == NULL) {
      return;
    }

    skip = (cmd[ci]=='\n');
    if(skip)
      continue;

    // Quit
    if(cmd[ci]=='q')
      return;

    // reset
    if(cmd[ci]=='c') {
      reset(cube);
      cmd[0] = 0;
      ci = 0;
      continue;
    }

    // scramble
    if(cmd[ci]=='s') {
      scramble(cube);
      cmd[0] = 0;
      ci = 0;
      continue;
    }

    // Debug mode
    if(cmd[ci]=='!'){
      debug=!debug;
      cmd[ci]=0;
      continue;
    }

    // Help 
    if(cmd[ci]=='?') {
      usage();
      printf("Press any key to continue...");
      getchar();
      cmd[ci]= 0;
      continue;
    }

    ci = execute(cube, cmd, ci);
   
    while(cmd[ci]!='\n'&&cmd[ci]!=0) ci++;
    cmd[ci++] = ' ';
  } 
}

void cli(int scram, char* cli_cmds) {
  reset(cube);
  if(scram)
    scramble(cube);

  int ci = 0;
  while(strlen(cli_cmds)>0) {
    ci = execute(cube, cli_cmds, 0);
    cli_cmds = (cli_cmds + ci) ;
  }
  ci = 0;
  char cmd[1024] = {0};
  while(1) {
    print_cli(cube);
    if (fgets(cmd + ci, sizeof(cmd), stdin) == NULL) {
      return;
    }

    // Quit
    if(cmd[ci]=='q')
      return;

    // reset
    if(cmd[ci]=='c') {
      reset(cube);
      cmd[0] = 0;
      ci = 0;
      continue;
    }

    // scramble
    if(cmd[ci]=='s') {
      scramble(cube);
      cmd[0] = 0;
      ci = 0;
      continue;
    }

    ci = execute(cube, cmd, ci); 
    while(cmd[ci]!='\n'&&cmd[ci]!=0) ci++;
    cmd[ci++] = ' '; 
  }
}

int main(int argc, char *argv[]) {
  if(argc>2&&strcmp(argv[1], "-s")==0) {
    if(argv[2][0] == '1')
      cli(1, "\0");
    else {
      cli(0, argv[2]);
    }
  } else {
    prompt();
  }
}


