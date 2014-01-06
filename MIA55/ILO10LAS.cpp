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

const int DUZO = 512;

int n, d;
int forest[DUZO][DUZO];
bool visited[DUZO][DUZO];

int maximal_place(int max_h);
int component_size(int max_h, int i, int j);

int main() {
    scanf("%d %d", &n, &d);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &forest[i][j]);

    int start = 1, stop = 1000000001;

    while(stop - start > 10) {
        int mid = (start + stop) / 2;
        if(maximal_place(mid) >= d)
            stop = mid;
        else
            start = mid;
    }

    for(int i = start; i <= stop; i++) {
        if(maximal_place(i) >= d) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}

int maximal_place(int max_h) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            visited[i][j] = false;

    int result = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(visited[i][j]) continue;

            result = max(result, component_size(max_h, i, j));
        }
    }

    //printf("Maximal place for %d is %d\n", max_h, result);
    return result;
}

int component_size(int max_h, int i, int j) {
    if(visited[i][j] || forest[i][j] > max_h)
        return 0;

    visited[i][j] = true;
    int result = 0;
    queue<pi> q;
    q.push(make_pair(i, j));
    while(!q.empty()) {
        pi p = q.front();
        q.pop();

        int x = p.first;
        int y = p.second;

        result += 1;

        for(int dx = -1; dx <= 1; dx += 1) {
            for(int dy = -1; dy <= 1; dy += 1) {
                if(abs(dx) + abs(dy) != 1)
                    continue;

                int xp = x + dx;
                int yp = y + dy;

                if(xp < 0 || xp >= n || yp < 0 || yp >= n || visited[xp][yp] || forest[xp][yp] > max_h)
                    continue;

                visited[xp][yp] = true;
                q.push(make_pair(xp, yp));
            }
        }
    }

    //printf("Component size %d %d is %d.\n", i, j, result);

    return result;
}

