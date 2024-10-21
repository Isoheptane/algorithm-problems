#include <stdio.h>

typedef long long ll;
const ll mod = 1e9 + 7;

int main() {
    int n;
    scanf("%d", &n);
    // 1: up, -1: down, 0: not decided
    int status = 0;
    ll result = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int v;
            scanf("%d", &v);
            // Add
            if (i == j) {
                result = result * v % mod;
            }
            // Check 
            if (v != 0 && i != j) {
                int cur_status = (i > j) ? -1 : 1;
                if (status == 0) {
                    status = cur_status;
                } else if (cur_status != status) {
                    puts("Arknights!");
                    return 0;
                }
            }
        }
    }
    printf("%lld\n", result);
}