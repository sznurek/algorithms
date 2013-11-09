#include <cstdio>

using namespace std;
int n;
int sx, sy;

bool on_board(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

int abs(int x) {
    if(x < 0)
        return -x;
    return x;
}

int min(int a, int b) {
    if(a < b)
        return a;
    return b;
}

int king() {
    int result = 0;

    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            if(dx == 0 && dy == 0)
                continue;

            result += on_board(sx + dx, sy + dy);
        }
    }

    return result;
}

int knight() {
    int result = 0;

    for(int dx = -2; dx <= 2; dx++) {
        for(int dy = -2; dy <= 2; dy++) {
            if(dx == 0 || dy == 0 || abs(dx) == abs(dy))
                continue;

            result += on_board(sx + dx, sy + dy);
        }
    }

    return result;
}

int diagonals() {
    return min(sy - 1, sx - 1) +
           min(sy - 1, n - sx) +
           min(n - sy, sx - 1) +
           min(n - sy, n - sx);
}

int straights() {
    return 2 * n - 2;
}

int main() {
    scanf("%d %d %d", &n, &sx, &sy);

    printf("King: %d\n", king());
    printf("Knight: %d\n", knight());
    printf("Bishop: %d\n", diagonals());
    printf("Rook: %d\n", straights());
    printf("Queen: %d\n", straights() + diagonals());
    return 0;
}

