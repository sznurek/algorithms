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

bool power_of_two(ll x);

int main() {
    int n;
    scanf("%d", &n);

    while(n --> 0) {
        ll a, b;
        scanf("%lld %lld", &a, &b);

        if(power_of_two(a) || power_of_two(b))
            printf("Y\n");
        else
            printf("N\n");
    }

    return 0;
}

bool power_of_two(ll x) {
    while(x % 2 == 0) x /= 2;

    return x == 1;
}
