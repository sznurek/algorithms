#include <cstdio>
#include <vector>

using namespace std;

typedef long long int ll;
const int DUZO = 200010;
const ll INF = 2000000000000000ll;

int n;
ll u[DUZO];
ll z[DUZO];
vector<ll> g[DUZO];

bool traversing[DUZO];
ll cached[DUZO];

ll dfs(int head);

int main() {
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        int r;
        cached[i] = -1;
        scanf("%lld %lld %d", &u[i], &z[i], &r);

        for(int j = 0; j < r; j++) {
            int gie;
            scanf("%d", &gie);

            g[i].push_back(gie);
        }
    }

    printf("%lld\n", dfs(1));

    return 0;
}

ll dfs(int head) {
    if(cached[head] != -1)
        return cached[head];

    traversing[head] = true;
    ll cost = 0;

    for(int i = 0; i < g[head].size(); i++) {
        int next = g[head][i];
        if(traversing[next]) {
            cost = INF;
            break;
        }

        cost += dfs(next);
    }

    traversing[head] = false;
    return cached[head] = min(z[head], u[head] + cost);
}

