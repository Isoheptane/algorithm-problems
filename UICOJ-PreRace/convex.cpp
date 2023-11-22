#include <iostream>
#include <cmath>

using std::cin;
using std::cout;

struct Vector {
    int x;
    int y;
    friend Vector operator+(Vector a, Vector b) {
        return {a.x + b.x, a.y + b.y};
    }
    friend Vector operator-(Vector a, Vector b) {
        return {a.x - b.x, a.y - b.y};
    }
};

int cross_product(Vector a, Vector b) {
    return (a.x * b.y) - (b.x * a.y);
}

bool a_cross_b(Vector a1, Vector a2, Vector b1, Vector b2) {
    Vector ad = a2 - a1;
    Vector ab = b1 - a1;
    Vector ac = b2 - a1;
    int sum = cross_product(ad, ab) * cross_product(ad, ac);
    return sum <= 0;
}

bool cross(Vector a1, Vector a2, Vector b1, Vector b2) {
    return a_cross_b(a1, a2, b1, b2) && a_cross_b(b1, b2, a1, a2);
}

int main() {
    Vector p[4];
    for (int i = 0; i < 4; i++) {
        cin >> p[i].x;
        cin >> p[i].y;
    }
    bool result = cross(p[0], p[2], p[1], p[3]);
    cout << (result ? "Yes" : "No") << '\n';
    return 0;
}