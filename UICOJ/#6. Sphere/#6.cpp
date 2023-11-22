#include <iostream>

using std::cin;
using std::cout;

int main() {
    double R;
    cin >> R;
    cout.setf(std::ios::fixed);
    cout.precision(5);
    cout << (4.0 / 3.0 * 3.14) * R * R * R;
    return 0;
}