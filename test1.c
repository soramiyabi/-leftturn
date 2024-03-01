#include <stdio.h>

// 2次元ベクトルを表す構造体
typedef struct {
    double x;
    double y;
} Point;

// p,q,rの行列計算
double cross_product(Point p, Point q, Point r) {
    return (p.x*q.y) + (q.x*r.y) + (r.x*p.y) - (p.x*r.y) - (q.x*p.y) - (r.x*q.y);
}

// 点rが線分pqの左側にあるかどうかを判定する関数
int is_left(Point p, Point q, Point r) {
    return cross_product(p, q, r) > 0;
}

// Xの凸包を計算する関数
void convex_hull(Point X[], int n) {
    // 凸包を保存する配列
    Point convex_hull[n];
    int m = 0; // 凸包の点の数

    // 左下の点を見つける
    int min = 0;
    for (int i = 1; i < n; ++i) {
        if (X[i].y < X[min].y || (X[i].y == X[min].y && X[i].x < X[min].x)) {
            min = i;
        }
    }
    Point start = X[min];

    // 凸包の点を求める
    Point current = start;
    do {
        convex_hull[m++] = current;
        Point next = X[0]; // 仮の次点
        for (int i = 0; i < n; ++i) {
            if (X[i].x == current.x && X[i].y == current.y) continue; // 同じ点はスキップ
            if (next.x == current.x && next.y == current.y) { // 初回
                next = X[i];
                continue;
            }
            if (is_left(current, next, X[i])) {
                next = X[i];
            }
        }
        current = next;
    } while (current.x != start.x || current.y != start.y); // ループ終了条件

    // 凸包の点を出力
    printf("凸包の点:\n");
    for (int i = 0; i < m; ++i) {
        printf("(%.2f, %.2f)\n", convex_hull[i].x, convex_hull[i].y);
    }
}

int main() {
    // 例として点の集合Xを作成
    Point X[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(X) / sizeof(X[0]);

    // Xの凸包を計算
    convex_hull(X, n);

    return 0;
}
