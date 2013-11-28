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
    freopen("energy.in", "r", stdin);
    freopen("energy.out", "w", stdout);
#endif

    int n;
    int ones = 0, twos = 0;
    ll result = 0;
    string plants;

    cin >> n >> plants;
    for(int i = 0; i < plants.size(); i++) {
        int free = n - ones - 2 * twos;
        if(plants[i] == '2' && free >= 2) {
            twos++;
        } else if(plants[i] == '1' && free >= 1) {
            ones++;
        } else if(plants[i] == '1' && twos > 0) {
            twos--;
            ones++;
        }

        result += ones + twos;
    }

    cout << result << endl;

    return 0;
}

