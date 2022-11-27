#include <iostream>
using namespace std;

int main() {
    int A[5] = {0, 0, 0, 0, 0};
    int B[5] = {0, 0, 0, 0, 0};

    // these two loops should be merged
    for (int i = 0; i < 5; ++i) {
        A[i] = i;
    }
    A[0] = 5;
    for (int j = 0; j < 4; ++j) {
        B[j] = j;
    }

    // printing
    cout << "A: ";
    for (int i = 0; i < 5; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "B: ";
    for (int i = 0; i < 5; ++i) {
        cout << B[i] << " ";
    }
    cout << endl;
}