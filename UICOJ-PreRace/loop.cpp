#include <iostream>
#include <string>
#include <set>
#include <tuple>

using std::cin;
using std::cout;
using std::string;
using std::tuple;
using std::set;
using std::get;

typedef unsigned long long ull;
typedef tuple<size_t, size_t> point;

const size_t MAX_HW = 505;
char map[MAX_HW][MAX_HW];

bool inbound(point p, ull max_h, ull max_w) {
    return !(get<0>(p) < 1 || get<0>(p) > max_h || get<1>(p) < 1 || get<1>(p) > max_w);
}

int main() {
    size_t H, W;
    cin >> H >> W;
    for (size_t row = 1; row <= H; row++) {
        string line;
        cin >> line;
        for (size_t col = 1; col <= W; col++)
            map[row][col] = line[col - 1];
    }
    point cur = point(1, 1);
    set<point> history;
    while (history.find(cur) == history.end()) {
        history.insert(cur);
        point next;
        switch (map[get<0>(cur)][get<1>(cur)])
        {
        case 'U':
            next = point(get<0>(cur) - 1, get<1>(cur));
            break;
        case 'D':
            next = point(get<0>(cur) + 1, get<1>(cur));
            break;
        case 'L':
            next = point(get<0>(cur), get<1>(cur) - 1);
            break;
        case 'R':
            next = point(get<0>(cur), get<1>(cur) + 1);
            break;
        }
        if (!inbound(next, H, W)) {
            cout << get<0>(cur) << ' ' << get<1>(cur) << '\n';
            return 0;
        }
        cur = next;
    }
    cout << "-1\n";
    return 0;
}