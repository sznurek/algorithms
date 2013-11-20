#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <map>
#include <queue>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

struct edge {
    edge(int d = 0, ll w = 0, char t = 'O') : dest(d), weight(w), type(t) {}
    int dest;
    ll weight;
    char type;
};

const int DUZO = 4096;
int n, m, p;
vector<edge> G[DUZO];
bool visited[DUZO];
pl best_dists[DUZO];

void dijkstra(int start);

int main() {
    cin >> n >> m >> p;

    for(int i = 0; i < m; i++) {
        int a, b, w;
        string t;

        cin >> a >> b >> w >> t;
        G[a].push_back(edge(b, w, t[0]));
        G[b].push_back(edge(a, w, t[0]));
    }

    for(int i = 0; i < p; i++) {
        for(int i = 0; i < n; i++) {
            visited[i] = false;
            best_dists[i] = make_pair(10000000000000ll, 10000000000000ll);
        }

        int start, stop;

        cin >> start >> stop;
        dijkstra(start);

        cout << best_dists[stop].first << " " << best_dists[stop].first + best_dists[stop].second << endl;
    }

    return 0;
}

void dijkstra(int start) {
    typedef pair<pl, int> state;
    priority_queue<state, vector<state>, greater<state> > q;

    best_dists[start] = make_pair(0, 0);
    q.push(make_pair(make_pair(0, 0), start));

    while(!q.empty()) {
        state s = q.top();
        q.pop();

        int v = s.second;
        pl dist = s.first;

        if(visited[v])
            continue;

        visited[v] = true;
        if(best_dists[v] > dist)
            best_dists[v] = dist;

        for(int i = 0; i < G[v].size(); i++) {
            edge& e = G[v][i];

            if(visited[e.dest])
                continue;

            if(e.type == 'I')
                q.push(make_pair(make_pair(dist.first, dist.second + e.weight), e.dest));
            else
                q.push(make_pair(make_pair(dist.first + e.weight, dist.second), e.dest));
        }
    }
}


