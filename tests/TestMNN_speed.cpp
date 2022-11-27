#include <iostream>
using namespace std;

// This is a test that has very little computation within loop body
// After loop fusion, there is expected to be more speedup than other cases

int main() {
    int x = 0;
    int y = 0;

    // these two loops should be merged
    for (int i = 0; i < 100000; ++i) {
        x += 1;
    }
    for (int j = 0; j < 100000; ++j) {
        y += 2;
    }

    // printing
    cout << "x: " << x << " y: " << y << endl;
}