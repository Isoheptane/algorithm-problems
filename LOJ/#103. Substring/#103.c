#include <stdio.h>

#define MAX_L (1000002)

char str[MAX_L];
char pattern[MAX_L];
int fail[MAX_L];

int main() {
    scanf("%s%s", &str, &pattern);
    // Root is -1, first element's fail always points to root
    fail[0] = -1;
    for (int i = 1; pattern[i] != '\0'; i++) {
        // For every node, fail pointer initially points to their parent.
        // When the next char is not matched, we try to match on node->fail.
        // If still not matched, try to match node->fail->fail until match or we reach the root.
        // We can simplify this fail pointer chain making the fail pointer points to the matched node/root
        int cur_fail = fail[i - 1];
        // Try match on fail until fail matches or fail goes to root
        while (cur_fail != -1 && pattern[cur_fail + 1] != pattern[i]) {
            cur_fail = fail[cur_fail];
        }
        // Matched on cur_fail, this fail pointer points to cur_fail's next
        if (pattern[cur_fail + 1] == pattern[i]) {
            fail[i] = cur_fail + 1;
        } else {
            // Reached root
            fail[i] = cur_fail;
        }
    }
    int occurence = 0, matched_ptr = -1;
    for (int i = -1; i == -1 || str[i] != '\0'; i++) {
        // Matched to the end
        if (pattern[matched_ptr + 1] == '\0') {
            occurence++;
        }
        // Try match on fail until fail matches or fail goes to root
        while (matched_ptr != -1 && str[i + 1] != pattern[matched_ptr + 1]) {
            matched_ptr = fail[matched_ptr];
        }
        // If next matches
        if (str[i + 1] == pattern[matched_ptr + 1]) {
            matched_ptr++;
            continue;
        }
    }
    printf("%d\n", occurence);
    return 0;
}