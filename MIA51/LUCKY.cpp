#include <cstdio>
#include <vector>
#include <cstring>

#define DEBUG if(0)

using namespace std;

const int DUZO = 100010;
const int RED = 1;
const int BLACK = 2;

struct edge {
    int number;
    int fst;
    int snd;
    int bcc;
    bool linked;
};

int n, m;
vector<int> graph[DUZO];
edge edges[DUZO];
int color[DUZO];
int parent_edge[DUZO];
int depth[DUZO];
bool failed_bcc[DUZO];
bool failed_vertex[DUZO];
bool back_edge[DUZO];
bool visited[DUZO];

vector<int> visit_order;

inline int other(const edge& e, int v) {
    if(e.fst == v)
        return e.snd;

    return e.fst;
}

inline int negcol(int color) {
    if(color == RED)
        return BLACK;
    return RED;
}

void dfs(int v, int parent=-1, int depth=1);
void bicolorize(int v);
void connect_bccs(int v);

int main() {
    int t;
    scanf("%d", &t);

    while(t --> 0) {
        scanf("%d %d", &n, &m);

        visit_order.clear();
        for(int i = 0; i <= n; i++) {
            graph[i].clear();
            depth[i] = color[i] = parent_edge[i] = 0;
            failed_vertex[i] = visited[i] = false;
        }

        for(int i = 0; i <= m; i++) {
            back_edge[i] = false;
            failed_bcc[i] = false;
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

        for(int i = 1; i <= n; i++)
            dfs(i);

        for(int i = 1; i <= n; i++)
            DEBUG printf("Parent of %d is %d.\n", i, other(edges[parent_edge[i]], i));

        for(int i = 0; i < visit_order.size(); i++)
            connect_bccs(visit_order[i]);

        for(int i = 1; i <= m; i++)
            DEBUG printf("EDGE[%d] = (%d, %d) BCC: %d, linked: %d\n", i, edges[i].fst, edges[i].snd, edges[i].bcc, edges[i].linked);

        for(int i = 1; i <= n; i++) {
            if(color[i])
                continue;

            bicolorize(i);
        }

        for(int i = 1; i <= m; i++) {
            edge& e = edges[i];
            if(failed_bcc[e.bcc]) {
                failed_vertex[e.fst] = failed_vertex[e.snd] = true;
            }
        }

        int lucky_cities = 0;
        for(int i = 1; i <= n; i++) {
            if(failed_vertex[i])
                lucky_cities++;
        }

        printf("%d\n", lucky_cities);
    }

    return 0;
}

void connect_bccs(int v) {
    DEBUG printf("Connecting %d...\n", v);
    for(int i = 0; i < graph[v].size(); i++) {
        edge& e = edges[graph[v][i]];
        int u = other(e, v);

        if(!back_edge[e.number] || depth[u] < depth[v])
            continue;

        DEBUG printf("Found backedge to %d!\n", u);
        int current_down = u;
        int current_edge = parent_edge[u];
        vector<int> visited_edges;
        while(other(edges[current_edge], current_down) != v && !edges[current_edge].linked) {
            DEBUG printf("Current %d, other: %d\n", current_down, other(edges[current_edge], current_down));
            visited_edges.push_back(current_edge);

            int new_vertex = other(edges[current_edge], current_down);
            current_edge = parent_edge[new_vertex];
            current_down = new_vertex;
        }

        for(int i = 0; i < visited_edges.size(); i++) {
            edges[visited_edges[i]].bcc = edges[current_edge].bcc;
            edges[visited_edges[i]].linked = true;
        }

        edges[current_edge].linked = true;
        e.bcc = edges[current_edge].bcc;
        e.linked = true;
    }
}

void bicolorize(int v) {
    for(int i = 0; i < graph[v].size(); i++) {
        int u = other(edges[graph[v][i]], v);

        if(color[u] && color[u] == color[v]) {
            failed_bcc[edges[graph[v][i]].bcc] = true;
        } else if(color[u] == 0) {
            color[u] = negcol(color[v]);
            bicolorize(u);
        }
    }
}

void dfs(int v, int parent, int depth_) {
    if(visited[v])
        return;

    DEBUG printf("DFS is visiting %d...\n", v);
    visited[v] = true;
    depth[v] = depth_;

    visit_order.push_back(v);
    for(int i = 0; i < graph[v].size(); i++) {
        edge& e = edges[graph[v][i]];
        int u = other(e, v);

        if(visited[u] && u != parent && depth[u] < depth[v]) {
            DEBUG printf("BACKEDGE (%d, %d)!\n", e.fst, e.snd);
            back_edge[e.number] = true;
        } else if(!visited[u]) {
            parent_edge[u] = e.number;
            dfs(u, v, depth[v] + 1);
        }
    }
}
