#include <iostream>

using std::cin;
using std::cout;

int main() {
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    for (int i: a) {
        switch (i % 4)
        {
        case 0:
            cout << 'L';
            break;
        case 1:
            cout << 'X';
            break;
        case 2:
            cout << 'T';
            break;
        case 3:
            cout << 'W';
            break;
        }
    }
    return 0;
}