#include <iostream>

using std::cin;
using std::cout;

int main() {
    u_int64_t n;
    cin >> n;
    cout << ((1ULL << n) - 1);
    return 0;
}