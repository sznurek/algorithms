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
    ll n, m;

    scanf("%lld %lld", &n, &m);

    ll r = n % m;
    ll k = n - r;
    ll sign = (k % 2 == 0) ? 1 : (m - 1);

    ll result = sign;

    for(int i = 1; i <= r; i++) {
        result *= i;
        sign *= (m - 1);
        sign %= m;
        result += sign;
        result %= m;
    }

    result *= result;
    result %= m;

    printf("%lld\n", result);

    return 0;
}

