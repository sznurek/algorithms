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

bool was[256];

int main() {
#ifndef BLASZAK
    freopen("arrange.in", "r", stdin);
    freopen("arrange.out", "w", stdout);
#endif
    int n;

    cin >> n;
    string s;
    getline(cin, s);
    for(int i = 0; i < n; i++) {
        getline(cin, s);
        was[s[0]] = true;
    }

    int cnt = 0;
    while(was['A' + cnt] && cnt < 26)
        cnt++;

    cout << cnt << endl;

    return 0;
}

