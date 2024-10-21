#include <stdio.h>
#include <string.h>

#define MAX_N (500001)

typedef long long ll;

char ptsd[MAX_N], word[MAX_N];
int ptsd_len, word_len;

ll prefix_len(char* ptsd, char* word) {
    ll len = 0;
    while (*ptsd != '\0' && *word != '\0') {
        if (*ptsd == *word) {
            len++;
            ptsd++;
        }
        word++;
    }
    return len;
}

ll suffix_len(char* ptsd, char* word, int ptsd_len, int word_len) {
    ll len = 0;
    int ptsd_ptr = ptsd_len - 1;
    int word_ptr = word_len - 1;
    while (ptsd_ptr >= 0 && word_ptr >= 0) {
        if (ptsd[ptsd_ptr] == word[word_ptr]) {
            len++;
            ptsd_ptr--;
        }
        word_ptr--;
    }
    return len;
}

int prefix[MAX_N], suffix[MAX_N];
int suffix_count[MAX_N] = {0};

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", &ptsd);
    ptsd_len = strlen(ptsd);
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        word_len = strlen(word);
        prefix[i] = prefix_len(ptsd, word);
        suffix[i] = suffix_len(ptsd, word, ptsd_len, word_len);
        suffix_count[suffix[i]]++;
    }
    for (int i = ptsd_len - 1; i >= 0; i--) {
        suffix_count[i] += suffix_count[i + 1];
    }
    ll count = 0;
    for (int i = 0; i < n; i++) {
        count += suffix_count[ptsd_len - prefix[i]];
    }
    printf("%lld\n", count);
}