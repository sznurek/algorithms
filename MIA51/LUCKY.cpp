#include <cstdio>
#include <vector>

using namespace std;

const int DUZO = 100010;

struct edge {
    int number;
    int fst;
    int snd;
    int bcc;
    bool linked;
};

int n, m;
int bccs;
vector<int> graph[DUZO];
edge edges[DUZO];
bool visited[DUZO];

inline int other(const edge& e, int v) {
    if(e.fst == v)
        return e.snd;

    return e.fst;
}

void dfs(int v, vector<edge>& s);

int main() {
    int t;
    scanf("%d", &t);

    while(t --> 0) {
        scanf("%d %d", &n, &m);

        bccs = 0;
        for(int i = 0; i <= n; i++) {
            graph[i].clear();
            visited[i] = false;
        }

        for(int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);

            edges[i].number = i;
            edges[i].fst = a;
            edges[i].snd = b;
            edges[i].bcc = i;
            edges[i].linked = false;

            graph[a].push_back(i);
            graph[b].push_back(i);
        }

        for(int i = 1; i <= n; i++) {
            if(visited[i])
                continue;

            vector<edge> stack;
            dfs(i, stack);
        }

        for(int i = 1; i <= m; i++) {
            printf("EDGE[%d] = (%d, %d) BCC: %d, linked: %d\n", i, edges[i].fst, edges[i].snd, edges[i].bcc, edges[i].linked);
        }
    }

    return 0;
}

void dfs(int v, vector<edge>& s) {
    visited[v] = true;

    for(int i = 0; i < graph[v].size(); i++) {
        edge& e = edges[graph[v][i]];
        int u = other(e, v);

        if(!visited[u]) {
            s.push_back(e);
            dfs(u, s);
            s.pop_back();
        } else {
            int current = v;
            int pos = s.size() - 1;
            while(other(s[pos], current) != u && !s[pos].linked) {
                current = other(s[pos], current);
                pos--;
            }

            for(int i = pos; i < s.size(); i++) {
                s[i].bcc = s[pos].bcc;
                s[i].linked = true;
            }

            e.bcc = s[pos].bcc;
            e.linked = true;
        }
    }
}

