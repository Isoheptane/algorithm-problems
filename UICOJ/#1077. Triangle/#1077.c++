#include <stdio.h>

typedef long long ll;

// icnt[x] = Count of i (i <= n) such that: i === x (mod m)
// i2cnt[x] = Count of i^2 (i <= n) such that: i^2 === x (mod m)
// ll icnt[1000005] = { 0 };
int i2cnt[1000005] = {0};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    /*
        Construct icnt array;
        Suppose that n = 10 and m = 4
        1 2 3 4 5 6 7 8 9 10 -> 1 2 3 0 1 2 3 0 1 2
        You can see i % m follows loop segment of [1 2 3 0]
        base count is the segment count
        tail_count is numbers in the final incomplete segment
    */
    ll base_count = n / m;
    ll tail_count = n % m;
    /*
    for (ll x = 0; x < m; x++) {
        icnt[x] = base_count;
        if (x >= 1 && x <= tail_count)
            icnt[x]++;
    }
    */
    // Transfer icnt[x] to i2cnt[x]
    for (ll x = 0; x < m; x++) {
        i2cnt[(x * x) % m] += (x >= 1 && x <= tail_count) ? base_count + 1 : base_count;
    }
    // Calculate all combinations
    ll count = 0;
    for (ll x = 0; x <= (m - x); x++) {
        // Find all possible groups
        ll other = (m - x) % m;
        if (x == other) {
            // Two group of i j are the same, such as 3 and 6
            // We have (3,3), (3,6), (6,6)
            // Count = n*(n+1)
            count += ((ll)i2cnt[x] * ((ll)i2cnt[x] + 1)) / 2;
        } else {
            // Two group of i j do not include same number
            // Directly multiply and then remove symmetric pair
            count += ((ll)i2cnt[x] * (ll)i2cnt[other]);
        }
    }
    printf("%ld\n", count);
}