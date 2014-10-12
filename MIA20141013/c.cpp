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

const int DUZO = 300000;

int n;
int middle;
ll heights[2][DUZO];

ll single_cost(int k, ll hmiddle);
ll cost(ll hmiddle);

int main() {
    scanf("%d", &n);
    middle = n / 2;

    for(int k = 0; k < 2; k++) {
        for(int i = 0; i < n; i++) {
            scanf("%d", &heights[k][i]);
        }
    }

    ll left = middle, right = 10e12 + 100;

    while(right - left > 10) {
        ll m1 = (2 * left + right) / 3;
        ll m2 = (left + 2 * right) / 3;

        ll c1 = cost(m1), c2 = cost(m2);
        if(c1 <= c2) {
            right = m2;
        }

        if(c2 <= c1) {
            left = m1;
        }
    }

    ll result = 10e12 + 100;
    for(ll i = left; i <= right; i++) {
        result = min(result, cost(i));
    }

    printf("%lld\n", result);

    return 0;
}

inline ll cost(ll hmiddle) {
    return single_cost(0, hmiddle) + single_cost(1, hmiddle);
}

inline ll single_cost(int k, ll hmiddle) {
    ll result = 0;

    for(int i = 0; i < n; i++) {
        result += abs(hmiddle + abs(middle - i) - heights[k][i]);
    }

    return result;
}

