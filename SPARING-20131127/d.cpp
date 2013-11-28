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

const int DUZO = 100010;

int n, m;
ll costs[DUZO];
vector<pl> exchange[DUZO];
vector<pl> where[DUZO];

int main() {
#ifndef BLASZAK
    freopen("dwarf.in", "r", stdin);
    freopen("dwarf.out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);

    priority_queue<pl, vector<pl>, greater<pl> > q;
    for(int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);
        costs[i] = c;
        q.push(make_pair(costs[i], i));
    }

    for(int i = 0; i < m; i++) {
        int a, x, y;
        scanf("%d %d %d", &a, &x, &y);

        exchange[a].push_back(make_pair(min(x, y), max(x, y)));
        where[x].push_back(make_pair(a, exchange[a].size() - 1));
        where[y].push_back(make_pair(a, exchange[a].size() - 1));
    }

    while(!q.empty()) {
        pl p = q.top();
        q.pop();

        int k = p.second;
        ll cost = p.first;

        if(k == 1) {
            cout << cost << endl;
            return 0;
        }

        costs[k] = min(costs[k], cost);
        for(int i = 0; i < where[k].size(); i++) {
            int creates = where[k][i].first;
            int pos = where[k][i].second;
            pl& par = exchange[creates][pos];

            if(par.first == k) {
                par.first = -costs[k];
            }

            if(par.second == k) {
                par.second = -costs[k];
            }

            ll c = -par.first - par.second;
            if(par.first <= 0 && par.second <= 0 && c < costs[creates]) {
                q.push(make_pair(c, creates));
            }
        }
    }

    return 0;
}

