#include <stdio.h>

int mark(char* ans, char* std) {
    // Single
    if (ans[1] == '\0' && std[1] == '\0') {
        return ans[0] == std[0] ? 3 : 0;
    }
    // Multiple
    int ansb = 0, stdb = 0;
    for (; *ans != '\0'; ans++)
        ansb |= 1 << (*ans - 'A');
    for (; *std != '\0'; std++)
        stdb |= 1 << (*std - 'A');
    if (ansb == stdb) {
        return 5;
    } else if ((ansb | stdb) == stdb) {
        return 2;
    } else {
        return 0;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int score = 0;
    for (int i = 0; i < n; i++) {
        char ans[5], std[5];
        scanf("%s%s", &ans, &std);
        score += mark(ans, std);
    }
    printf("%d\n", score);
    return 0;
}