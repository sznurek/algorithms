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

const ll DUZO = 1024;
ll costs[DUZO];
ll best[DUZO];

int main() {
    int n;
    scanf("%d", &n);

    for(ll i = 0; i < n; i++)
        scanf("%lld", costs + i);

    best[0] = 1;
    for(ll i = 1; i < n-1; i++) {
        best[i] = costs[0] + ((i + 1)*i)/2;
        for(ll j = 1; j <= i; j++) {
            best[i] = min(best[i], best[j-1] + costs[j] + ((i-j) * (i-j+1))/2);
        }
    }

    printf("%lld\n", best[n-2] + costs[n-1]);

    return 0;
}

