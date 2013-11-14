#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

const int SIZE = 8;
char board[SIZE + 10][SIZE + 10];

inline int abs(int x) {
    if(x < 0)
        return -x;
    return x;
}

bool can_go_to(int x, int y, int kx, int ky) {
    return ((x + y) % 4) == ((kx + ky) % 4) && kx % 2 == x % 2 && ky % 2 == y % 2;
}

int moves_parity(int x, int y, int kx, int ky) {
    return abs(kx - x) % 4 == 0;
}

int main() {
    int t;
    scanf("%d", &t);

    while(t --> 0) {
        for(int i = 0; i < SIZE; i++)
            scanf("%s", board[i]);

        vector<pair<int, int> > pos;
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(board[i][j] == 'K') {
                    pos.push_back(make_pair(i, j));
                }
            }
        }

        bool can_be = false;
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(board[i][j] == '#')
                    continue;

                bool move_possible = can_go_to(i, j, pos[0].first, pos[0].second) && can_go_to(i, j, pos[1].first, pos[1].second);
                bool parity_good = moves_parity(i, j, pos[0].first, pos[0].second) == moves_parity(i, j, pos[1].first, pos[1].second);
                if(move_possible && parity_good) {
                    can_be = true;
                    break;
                }
            }
        }

        printf("%s\n", can_be ? "YES" : "NO");
    }

    return 0;
}

