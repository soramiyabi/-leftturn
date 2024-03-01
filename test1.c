#include <stdio.h>

// 2次元ベクトルを表す構造体
typedef struct {
    double x;
    double y;
} Point;

// ベクトルABとベクトルBCの外積を計算する
double cross_product(Point A, Point B, Point C) {
    return (A.x*B.y)+(B.x*C.y)+(C.x*A.y)-(A.x*C.y)-(B.x*A.y)-(C.x*B.y);
}

// pからqへのベクトルからp->q->rの左ターンがあるかどうかをチェック
 int left_turn(Point p, Point q, Point r) {
                        double cross = cross_product(p, q, r);
                        return cross >0 ;
                        }


// Xの凸包を計算する関数
void convex_hull(Point X[], int n) {
    // 凸包を保存する配列
    Point convex_hull[n];
    int m = 0; // 凸包の点の数

    // すべての点の組み合わせをチェック
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // pとqを選択
            Point p = X[i];
            Point q = X[j];

            // Bに追加するかどうかを判断する
            int add_edge = 1;
            for (int k = 0; k < n; ++k) {
                if (k != i && k != j) {
                    Point r = X[k];
                    if (!left_turn(p, q, r) >0) {
                        add_edge = 0;
                        break;
                    }
                }
            }

            // 有効辺をBに追加
            if (add_edge) {
                convex_hull[m++] = p;
                convex_hull[m++] = q;
            }
        }
    }

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
