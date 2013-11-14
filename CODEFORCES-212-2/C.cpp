#include <cstdio>

using namespace std;

int n;
int perm[5010];
int mem[5010][5010];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", perm + i);

    int inversions = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(perm[i] > perm[j]) inversions++;
        }
    }

    for(int y = 0; y < n; y++) {
        for(int x = 1; x <= n; x++) {
            mem[y][x] = mem[y][x - 1];
            if(perm[x - 1] < y)
                mem[y][x]++;
        }
    }

    int ways = 0;
    int best = -1;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(perm[i] < perm[j])
                continue;

            int between = j - i - 1;
            int less_than_left  = mem[perm[i]][j] - mem[perm[i]][i+1];
            int less_than_right = mem[perm[j]][j] - mem[perm[j]][i+1];
            int left_delta = less_than_left - (between - less_than_left);
            int right_delta = (between - less_than_right) - less_than_right;
            int delta = left_delta + right_delta + 1;

            if(delta == best) {
                ways++;
            } else if(delta > best) {
                best = delta;
                ways = 1;
            }
        }
    }

    printf("%d %d\n", inversions - best, ways);

    return 0;
}
