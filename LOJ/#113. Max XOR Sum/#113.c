#include <stdio.h>

#define LENGTH_BIT (64)
#define HIGHEST_BIT (LENGTH_BIT - 1)

typedef unsigned long long ull;

ull base[LENGTH_BIT] = {0};

void insert(ull v) {
    for (int i = HIGHEST_BIT; i >= 0; i--) {
        if (!(v >> i))
            continue;
        if (base[i] == 0) {
            base[i] = v;
            break;
        }
        v ^= base[i];
    }
}

void eliminate() {
    for (int i = HIGHEST_BIT; i >= 0; i--) {
        for (int j = HIGHEST_BIT; j > i; j--) {
            if (base[j] >> i & 1) {
                base[j] ^= base[i];
            }
        }
    }
}

void print() {
    for (int i = HIGHEST_BIT; i >= 0; i--) {
        for (int j = HIGHEST_BIT; j >= 0; j--)
            putchar((base[i] >> j & 1) ? '1' : '0');
        putchar('\n');
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        ull cv;
        scanf("%llu", &cv);
        insert(cv);
    }
    // print();
    eliminate();
    // print();
    ull value = 0;
    for (int i = HIGHEST_BIT; i >= 0; i--) {
        ull new_value = value ^ base[i];
        if (new_value > value) {
            value = new_value;
        }
    }
    printf("%llu\n", value);
    return 0;
}