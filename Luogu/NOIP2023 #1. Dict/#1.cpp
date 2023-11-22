#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

const size_t MAX_V = 3005;

struct StringData {
    int char_count[26];
    int begin, end;
};

// nnbaaaa
// nnn

StringData dict[MAX_V];

bool compare_can_greater(const StringData& a, const StringData& b) {
    if (a.begin < b.end) {
        return true;
    } else if (a.begin > b.end) {
        return false;
    } else {
        return a.char_count[a.begin] < b.char_count[b.end];
    }
}

int main() {
    size_t n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        for (char c: str)
            dict[i].char_count[c - 'a']++;
        for (int j = 0; j < 26; j++) {
            if (dict[i].char_count[j] != 0) {
                dict[i].begin = j;
                break;
            }
        }
        for (int j = 25; j >= 0; j--) {
            if (dict[i].char_count[j] != 0) {
                dict[i].end = j;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            if (!compare_can_greater(dict[i], dict[j])) {
                flag = false;
                break;
            }
        }
        cout << (flag ? '1' : '0');
    }
    return 0;
}