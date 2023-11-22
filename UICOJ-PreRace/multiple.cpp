#include <iostream>

using std::cin;
using std::cout;

typedef long long ll;

ll mod(ll a, ll p) {
    return ((a % p) + p) % p;
}

int main() {
    ll N;
    cin >> N;
    cout << mod(N, 998244353) << '\n';
    return 0;
}