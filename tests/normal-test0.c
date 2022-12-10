#include <stdio.h>

int main() {
    int x = 1;
    int y = 1;
    int z;
    int A[2] = {10,11};

    scanf("%d", &z);
    // these two loops should be merged
    for (int i = 0; i < 5; ++i) {
        x = x + i;
    }

    for (int j = 0; j < 5; ++j) {
        y = y * (1 + j);
    }

    // printing
    printf("x: %d y: %d\n", x, y);
    printf("zzzzzz: %d \n", z);
}