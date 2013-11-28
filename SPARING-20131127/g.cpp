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
    freopen("garage.in", "r", stdin);
    freopen("garage.out", "w", stdout);
#endif

    ll W, H, w, h;
    cin >> W >> H >> w >> h;

    int ww = round((double)W / (2.0 * w));
    int hh = round((double)H / (2.0 * h));

    cout << ww * hh << endl;

    return 0;
}

