#define byte char

typedef enum sides {
    TOP, LEFT, FRONT, RIGHT, BACK, BOTTOM
} Side;

int print_cube(byte*);

int print_cube2(byte*);

int print(byte*);

int print_nums(byte* cube);
