#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::set;

const size_t MAX_V = 1e5 + 5;

enum State {
    True = 1,
    False = -1,
    Unknown = 0
};

struct Value {
    bool is_ref;
    int state;
    //  When is_ref = true, state indicates its equals to init state
    //  negative means negative reference
    //  When is_ref = false, state indicates its state
    friend std::ostream& operator<<(std::ostream& out, const Value value) {
        if (value.is_ref) {
            int refvalue = std::abs(value.state);
            cout << "Reference of " << (value.state > 0 ? "" : "negative ") << refvalue << '\n'; 
        } else {
            switch (value.state) {
                case 0:
                    cout << "Unknown\n";
                    break;
                case 1:
                    cout << "True\n";
                    break;
                case -1:
                    cout << "False\n";
                    break;
            }
        }
        return out;
    }
};

Value values[MAX_V];

bool defined[MAX_V];
bool unique[MAX_V];
bool checked[MAX_V];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        values[i] = { true, i };
        defined[i] = false;
        checked[i] = false;
    }
}

void assign(Value& a, Value& b, bool reverse) {
    a.state = b.state * (reverse ? -1 : 1);
}

void compress(int i) {
    Value& v = values[i];
}

int check_ring(int i, set<int>& history) {
    Value& v = values[i];
    if (checked[i])
        return 0;
    if (v.is_ref) {
        if (history.find(i) != history.end())
            return i;
        history.insert(i);
        int result = check_ring(abs(v.state), history);
        checked[i] = true;
        return result;
    } else {
        checked[i] = true;
        return 0;
    }
}

void count_ring(int begin, int i, set<int>& history) {
    Value& v = values[i];
    history.insert(i);
    if (abs(v.state) == begin)
        return;
    else
        return count_ring(begin, abs(v.state), history);
}

bool define(int i) {
    if (defined[i])
        return unique[i];
    Value& v = values[i];
    defined[i] = true;
    if (v.is_ref) {
        if (-v.state == i)
            unique[i] = false;
        else if (v.state == i)
            unique[i] = true;
        unique[i] = define(abs(v.state));
    } else {
        if (v.state == 0)
            unique[i] = false;
        else
            unique[i] = true;
    }
    return unique[i];
}

void single_solve() {
    int n, m;
    cin >> n >> m;
    init(n);
    for (int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if (c == '+' || c == '-') {
            int i, j;
            cin >> i >> j;
            assign(values[i], values[j], c == '-');
        } else {
            int i;
            cin >> i;
            values[i].is_ref = false;
            switch (c) {
                case 'T':
                    values[i].state = True;
                    break;
                case 'F':
                    values[i].state = False;
                    break;
                case 'U':
                    values[i].state = Unknown;
                    break;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        static set<int> history;
        int ring_start = check_ring(i, history);
        history.clear();
        if (ring_start == 0)
            continue;
        count_ring(ring_start, ring_start, history);
        int ncount = 0;
        for (int i: history)
            if (values[i].is_ref && values[i].state < 0)
                ncount++;
        bool ring_unique = (ncount % 2 == 0);
        for (int i: history) {
            defined[i] = true;
            unique[i] = ring_unique;
        }
        history.clear();
    }
    /*
    for (int i = 1; i <= n; i++) {
        cout << values[i];
    }
    */
    for (int i = 1; i <= n; i++) {
        define(i);
    }
    int count = 0;
    for (int i = 1; i <= n; i++)
        if (unique[i] == false)
            count++;
    cout << count << '\n';
}

int main() {
    int c, t;

    // std::ifstream in("tribool1.in");
    // cin.rdbuf(in.rdbuf());
    
    cin >> c >> t;
    for (int i = 0; i < t; i++) {
        single_solve();
    }
    return 0;
}