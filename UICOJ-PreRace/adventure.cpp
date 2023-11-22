#include <iostream>

const size_t MAX_N = 1e5 + 5;

typedef long long ll;

using std::cin;
using std::cout;

ll A[MAX_N];
ll Y[MAX_N];

int main() {
    ll N, M, T;
    cin >> N >> M >> T;
    //  Array initialization
    for (ll i = 1; i <= N - 1; i++) {
        cin >> A[i];
    }
    for (ll i = 1; i <= M; i++) {
        ll Xi;
        cin >> Xi;
        cin >> Y[Xi];
    }
    for (int i = 1; i < N; i++) {
        T += Y[i];
        T -= A[i];
        if (T <= 0) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}