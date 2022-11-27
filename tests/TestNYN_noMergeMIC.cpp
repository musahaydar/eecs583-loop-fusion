#include <iostream>
using namespace std;

int main() {
    int A[5] = {0, 0, 0, 0, 0};
    int B[5] = {0, 0, 0, 0, 0};
    // these two loops should not be fused
    for (int i = 0; i < 5; ++i) {
        A[i] = i;
    }
    B[0] = A[1];
    for (int j = 0; j < 5; ++j) {
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