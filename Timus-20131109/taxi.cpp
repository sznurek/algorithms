#include <cstdio>
#include <algorithm>

using namespace std;

const int DUZO = 5;

int dist[DUZO][DUZO];
int possible[4][5] = {
    {1, 2, 3, 4, 5},
    {1, 3, 2, 4, 5},
    {1, 3, 4, 2, 5},
    {1, 4, 3, 2, 5}
};

int main() {
    for(int i = 0; i < DUZO; i++) {
        for(int j = 0; j < DUZO; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    int mini_len = 10000000;
    int mini_num = -1;
    for(int p = 0; p < 4; p++) {
        int len = 0;

        for(int i = 0; i < 4; i++) {
            len += dist[possible[p][i] - 1][possible[p][i+1] - 1];
        }

        if(len < mini_len) {
            mini_len = len;
            mini_num = p;
        }
    }

    printf("%d\n", mini_len);
    for(int i = 0; i < 5; i++) {
        printf("%d ", possible[mini_num][i]);
    }
    puts("");

    return 0;
}

