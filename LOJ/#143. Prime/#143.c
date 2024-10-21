#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef unsigned long long ull;
typedef __uint128_t uxl;

ull randl() {
    return ((ull)rand() << 32) + rand();
}

uxl fpow(uxl x, uxl n, uxl p) {
    static uxl pow[64];
    pow[0] = x;
    for (int i = 1; n >> i; i++)
        pow[i] = (pow[i - 1] * pow[i - 1]) % p;
    uxl result = 1;
    for (int i = 0; n >> i; i++)
        if (n >> i & 1)
            result = (result * pow[i]) % p;
    return result;
}

const ull bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 61, 73, 0};

bool naive(ull n, const ull* bases) {
    for (int i = 0; bases[i] != 0; i++)
        if (n != bases[i] && n % bases[i] == 0)
            return false;
    return true;
}

bool miller_rabin(ull n, ull a) {
    ull r = 1, d = (n - 1);
    for (ull s = 1; !((n - 1) >> (s - 1) & 1); s++) {
        d = (n - 1) / (1 << s);
        r = s;
    }

    ull x = fpow(a, d, n);
    if (x == 1 || x == (n - 1)) {
        return true;
    }
    for (ull i = 1; i < r; i++) {
        x = ((uxl)x * (uxl)x) % (uxl)n;
        if (x == n - 1)
            return true;
    }
    return false;
}

bool miller_rabin_mixed(ull n) {
    if (!naive(n, bases))
        return false;
    for (int i = 0; bases[i] != 0; i++)
        if (n > bases[i])
            if (!miller_rabin(n, bases[i]))
                return false;
    return true;
}

int main() {
    srand(time(NULL));
    ull n;
    while (scanf("%llu", &n) != EOF) {
        if (n == 1) {
            puts("N");
            continue;
        }
        if (n <= 3) {
            puts("Y");
            continue;
        }
        bool result = miller_rabin_mixed(n);
        puts(result ? "Y" : "N");
    }
}