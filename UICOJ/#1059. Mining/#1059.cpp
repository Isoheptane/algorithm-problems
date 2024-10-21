#include <cstdio>
#include <cmath>

inline int distsq(int x1, int y1, int x2, int y2) {
    return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
}

int main() {
    int n, x1, x2, y1, y2;
    scanf("%d%d%d%d%d", &n, &x1, &y1, &x2, &y2);
    int min_id = 1e5 + 5;
    int global_minsq = 100000;
    for (int i = 1; i <= n; i++) {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        int min_distsq = 100000;
        min_distsq = std::min(min_distsq, distsq(xi, yi, x1, y1));
        min_distsq = std::min(min_distsq, distsq(xi, yi, x2, y2));
        min_distsq = std::min(min_distsq, distsq(xi, yi, x1, y2));
        min_distsq = std::min(min_distsq, distsq(xi, yi, x2, y1));
        if (y1 <= yi && yi <= y2) {
            min_distsq = std::min(min_distsq, (xi - x1) * (xi - x1));
            min_distsq = std::min(min_distsq, (xi - x2) * (xi - x2));
        }
        if (x1 <= xi && xi <= x2) {
            min_distsq = std::min(min_distsq, (yi - y1) * (yi - y1));
            min_distsq = std::min(min_distsq, (yi - y2) * (yi - y2));
        }
        if (min_distsq < global_minsq) {
            global_minsq = min_distsq;
            min_id = i;
        }
        double min_dist = std::sqrt((double)min_distsq);
        printf("%.9lf ", min_dist);
    }
    printf("\n%d\n", min_id);
    return 0;
}