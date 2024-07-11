#define byte char

typedef enum sides {
    TOP, LEFT, FRONT, RIGHT, BACK, BOTTOM
} Side;

enum colors {
    WHITE, GREEN, RED, BLUE, ORANGE, YELLOW 
};

int print_cube(byte*);

int print(byte*);

int print_nums(byte* cube);
