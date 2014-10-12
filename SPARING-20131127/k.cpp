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

int main() {
#ifndef BLASZAK
    freopen("kids.in", "r", stdin);
    freopen("kids.out", "w", stdout);
#endif

    ll ff, fm, mf, mm;
    cin >> ff >> fm >> mf >> mm;

    ll g = __gcd(mf, fm);
    ll M = fm / g;
    ll F = mf / g;

    ll cliques = 1;
    while(M < max(mm + 1, fm) || F < max(ff + 1, mf)) {
        M *= 2;
        F *= 2;
        cliques *= 2;
    }

    cout << F << " " << M << endl;
    for(int i = 1; i <= F; i++) {
        for(int j = 0; j < fm; j++) {
            cout << i << " " << F + 1 + (i-1)*fm + j << endl;
        }
    }

    for(int i = 0; i < cliques; i++) {
        ll clique_start = 1 + i * (M/cliques);
        for(int j = 0; j < M/cliques; j++) {
            
        }
    }

    return 0;
}

