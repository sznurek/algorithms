#include <cstdio>
#include <set>
#include <iostream>

using namespace std;

typedef long long int ll;

set<ll> s;

int main() {
    int n, m;

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        ll c;
        cin >> c;
        s.insert(c);
    }

    ll waste = 0;
    for(int i = 0; i < m; i++) {
        ll c;
        cin >> c;

        waste += (*(s.lower_bound(c)) - c);
    }

    cout << waste << endl;

    return 0;
}

