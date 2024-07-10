#define byte char

typedef enum sides {
    TOP, BOTTOM, LEFT, FRONT, RIGHT, BACK
} Side;

enum colors {
    WHITE, YELLOW, GREEN, RED, BLUE, ORANGE
};

int print_cube(byte*);

int print(byte*);


