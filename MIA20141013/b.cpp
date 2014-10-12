#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

const int DUZO = (1 << 20);
const int SIZE = 2 * DUZO + 10;

struct node {
    int mini, maxi;
};

node tree[SIZE];

void update(int pos, int x) {
    tree[DUZO + pos].mini = tree[DUZO + pos].maxi = x;

    int cur = (DUZO + pos) / 2;
    while(cur >= 1) {
        tree[cur].mini = min(tree[2*cur].mini, tree[2*cur + 1].mini);
        tree[cur].maxi = max(tree[2*cur].maxi, tree[2*cur + 1].maxi);

        cur /= 2;
    }
}

// [start, stop]
node query(int start, int stop) {
    node result;
    result.mini = SIZE;
    result.maxi = -1;

    int left = start + DUZO, right = stop + DUZO;

    while(left <= right) {
        if(right % 2 == 0) {
            result.mini = min(tree[right].mini, result.mini);
            result.maxi = max(tree[right].maxi, result.maxi);

            right = right / 2 - 1;
        } else {
            right /= 2;
        }

        if(left % 2 == 1) {
            result.mini = min(tree[left].mini, result.mini);
            result.maxi = max(tree[left].maxi, result.maxi);

            left = left / 2 + 1;
        } else {
            left /= 2;
        }
    }

    return result;
}

int n, m;
int dwarfs[DUZO];

int main() {
    scanf("%d %d", &n, &m);

    for(int i = 0; i < DUZO; i++) {
        tree[DUZO + i].mini = SIZE;
        tree[DUZO + i].maxi = -1;
    }

    for(int i = 1; i <= n; i++) {
        int d;
        scanf("%d", &d);

        dwarfs[i] = d;
        tree[DUZO + d].mini = tree[DUZO + d].maxi = i;
    }

    for(int i = DUZO - i; i >= 1; i--) {
        tree[i].mini = min(tree[2*i].mini, tree[2*i + 1].mini);
        tree[i].maxi = max(tree[2*i].maxi, tree[2*i + 1].maxi);
    }

    for(int i = 0; i < m; i++) {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);

        if(c == 1) {
            int d1 = dwarfs[x];
            int d2 = dwarfs[y];

            swap(dwarfs[x], dwarfs[y]);
            update(d1, y);
            update(d2, x);
        } else {
            node result = query(x, y);
            if(result.maxi - result.mini == y - x)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }

    return 0;
}

