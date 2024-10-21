#include <stdio.h>

#define LENGTH_BIT (51)
#define HIGHEST_BIT (LENGTH_BIT - 1)

typedef unsigned long long ull;

ull base[LENGTH_BIT] = {0};

ull compressed[LENGTH_BIT] = {0};
int base_count = 0;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        ull cv;
        scanf("%llu", &cv);
        for (int i = HIGHEST_BIT; i >= 0; i--) {
            if (!(cv >> i))
                continue;
            if (base[i] == 0) {
                base[i] = cv;
                break;
            }
            cv ^= base[i];
        }
    }
    // eliminate
    for (int i = HIGHEST_BIT; i >= 0; i--) {
        for (int j = HIGHEST_BIT; j > i; j--) {
            if (base[j] >> i & 1) {
                base[j] ^= base[i];
            }
        }
    }
    // compress base
    for (int i = 0; i <= HIGHEST_BIT; i++) {
        if (base[i]) {
            compressed[base_count++] = base[i];
        }
    }
    // base_count < n means there can are elements that can be represented by other elements' xor sum
    // which means, a non-empty set whose xor sum = 0 exists
    ull xor_count = (1ull << base_count) - (base_count < n ? 0 : 1);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        ull k;
        scanf("%llu", &k);
        if (k > xor_count) {
            puts("-1");
            continue;
        }
        // Allow 0 existing if n > base_count
        if (base_count < n ? 1 : 0)
            k--;
        ull v = 0;
        for (int j = 0; j < base_count; j++) {
            if (k >> j & 1)
                v ^= compressed[j];
        }
        printf("%llu\n", v);
    }
    return 0;
}