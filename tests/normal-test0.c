#include <stdio.h>

int main() {
    int x = 1;
    int y = 1;

    // these two loops should be merged
    for (int i = 0; i < 5; ++i) {
        x = x + i;
    }
    for (int j = 0; j < 5; ++j) {
        y = y * (1 + j);
    }

    // printing
    printf("x: %d y: %\n", x, y);
}