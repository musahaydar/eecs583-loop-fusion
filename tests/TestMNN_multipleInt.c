#include <stdio.h>

int main() {
    int x = 1;
    int y = 1;
    int z = 1;

    // these two loops should be merged
    for (int i = 0; i < 5; ++i) {
        x = x + i;
    }
    for (int j = 0; j < 5; ++j) {
        y = y * (1 + j);
    }
    for (int k = 0; k < 5; ++k) {
        y = z + k * 2;
    }

    // printing
    printf("x: %d y: %d z: %d\n", x, y, z);
}