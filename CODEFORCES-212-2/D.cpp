#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long int ll;
const int DUZO = 100010;

struct edge {
    edge(int v=0, ll l=0) : v(v), length(l) {}
    int v;
    ll length;
};

int n, m, p, q;
vector<edge> G[DUZO];

int components;
int component[DUZO];
int representative[DUZO];
ll edges_length[DUZO];

int find_components(int v);

int main() {
    scanf("%d %d %d %d", &n, &m, &p, &q);

    for(int i = 0; i < m; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        G[a].push_back(edge(b, l));
        G[b].push_back(edge(a, l));
    }

    int nonsingular = -1;
    for(int i = 1; i <= n; i++) {
        if(component[i])
            continue;

        components++;
        int vertexes = find_components(i);
        representative[components] = i;
        edges_length[components] /= 2;

        if(vertexes > 1) {
            nonsingular = components;
        }
    }

    if(components < q || components - q > p) {
        printf("NO\n");
        return 0;
    }

    set<pair<ll, int> > comps;
    for(int i = 1; i <= components; i++) {
        comps.insert(make_pair(edges_length[i], i));
    }

    vector<pair<int, int> > added_edges;
    for(int i = 0; i < components - q; i++) {
        pair<ll, int> first_component = *comps.begin();
        pair<ll, int> second_component = *(++comps.begin());

        added_edges.push_back(make_pair(representative[first_component.second], representative[second_component.second]));

        comps.erase(first_component);
        comps.erase(second_component);
        comps.insert(make_pair(min(1000000000ll, 2 * (first_component.first + second_component.first) + 1), first_component.second));

        if(nonsingular == -1) {
            nonsingular = first_component.second;
            component[second_component.second] = first_component.second;
        }
    }

    if(nonsingular == -1 && p - (components - q) > 0) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    vector<int> two;
    for(int i = 1; i <= n; i++) {
        if(component[i] == nonsingular)
            two.push_back(i);

        if(two.size() == 2)
            break;
    }

    for(int i = 0; i < p - (components - q); i++) {
        added_edges.push_back(make_pair(two[0], two[1]));
    }

    for(int i = 0; i < added_edges.size(); i++)
        printf("%d %d\n", added_edges[i].first, added_edges[i].second);

    return 0;
}

int find_components(int v) {
    if(component[v])
        return 0;

    int vertexes = 0;
    component[v] = components;
    for(int i = 0; i < G[v].size(); i++) {
        edges_length[components] += G[v][i].length;
        vertexes += find_components(G[v][i].v);
    }

    return vertexes + 1;
}

