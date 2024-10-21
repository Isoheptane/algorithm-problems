#include <cstdio>
#include <map>

std::map<int, int> savings;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0 ; i < n; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x;
            scanf("%d", &x);
            savings[x]++;
        } else if (op == 2) {
            int x, c;
            scanf("%d%d", &x, &c);
            savings[x] = std::max(savings[x] - c, 0);
        } else if (op == 3) {
            while (savings.begin()->second == 0)
                savings.erase(savings.begin()->first);
            while (savings.rbegin()->second == 0)
                savings.erase(savings.rbegin()->first);
            int val = savings.rbegin()->first - savings.begin()->first;
            printf("%d\n", val);
        }
    }
    return 0;
}