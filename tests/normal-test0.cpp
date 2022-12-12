#include <iostream>
using namespace std;

void loops();

int main() {
    loops();
}

void loops() {
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
    cout << "x: " << x << " y: " << y << endl;
}