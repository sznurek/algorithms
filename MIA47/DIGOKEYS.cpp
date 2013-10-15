// Problem: Find the treasure
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int DUZO = 100010;
int n;
bool visited[DUZO];
int dist[DUZO];
int parent[DUZO];
vector<int> G[DUZO];

vector<int> bfs(int start, int stop);

int main() {
    int t;
    scanf("%d", &t);
    while(t --> 0) {
        scanf("%d", &n);

        for(int i = 0; i <= n; i++) {
            dist[i] = parent[i] = -1000;
            visited[i] = false;
            G[i].clear();
        }
        for(int i = 1; i < n; i++) {
            int boxes;
            scanf("%d", &boxes);

            for(int j = 0; j < boxes; j++) {
                int x;
                scanf("%d", &x);
                G[i].push_back(x);
            }
        }

        for(int i = 1; i <= n; i++)
            sort(G[i].begin(), G[i].end());

        vector<int> path = bfs(1,n);
        if(path.empty()) {
            printf("-1\n");
        } else {
            printf("%d\n", path.size());
            for(int i = 0; i < path.size(); i++)
                printf("%d ", path[i]);
            printf("\n");
        }

        printf("\n");
    }

    return 0;
}

vector<int> bfs(int start, int stop) {
    queue<int> q;
    dist[start] = 0;
    visited[start] = true;
    q.push(start);

    bool found = false;
    while(!q.empty()) {
        int v = q.front();
        q.pop();

        if(v == stop) {
            found = true;
            break;
        }

        visited[v] = true;
        for(int i = 0; i < G[v].size(); i++) {
            if(visited[G[v][i]]) continue;

            visited[G[v][i]] = true;
            dist[G[v][i]] = dist[v] + 1;
            parent[G[v][i]] = v;
            q.push(G[v][i]);
        }
    }

    vector<int> path;
    if(!found)
        return path;

    int current = stop;
    while(current != start) {
        current = parent[current];
        path.push_back(current);
    }
    reverse(path.begin(), path.end());

    return path;
}
