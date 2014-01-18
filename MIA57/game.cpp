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

typedef unsigned long long int ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

ll node(ll level, ll k) {
    if(level == 0)
        return 3;

    ll left = 3;
    for(int i = 0; i < level; i++)
        left = 4*left - 3;

    ll diff = 0;
    ll p = 2;
    for(int i = 0; i < level; i++) {
        diff += (k / 2) * p;
        p = ((p * 3 - 2) * 4 + 2) / 3;

        k = (k+1)/2;
    }

    return left + diff;
}

int main() {
    ll N;
    cin >> N;

    if(N < 3) {
        cout << "0\n";
        return 0;
    }

    if(N < 9) {
        cout << "1\n";
        return 0;
    }

    ll level = 0;
    while(node(level, (1 << level)) < N)
        level++;

    ll start = 1;
    ll stop = (1 << level);

    while(stop - start > 5) {
        ll mid = (start + stop) / 2;
        //cout << "Mid " << mid << " -> " << node(level, mid) << endl;

        if(node(level, mid) <= N)
            start = mid + 1;
        else
            stop = mid;
    }

    //cout << "After bin: " << start << " " << stop << endl;

    while(node(level, start) <= N && start <= stop)
        start++;

    //cout << "Level: " << level << " new start: " << start << endl;
    cout << (1 << level) - 1 + (start - 1) << endl;

    return 0;
}

