#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long int ll;
const ll MOD = 1000000007;

ll inv(ll a);
ll qpower(ll base, int exp);
ll phi(ll n, ll a);

int main() {
    int n, a, b;

    scanf("%d %d %d", &n, &a, &b);
    printf("%llu\n", (phi(n, a) * phi(n, b)) % MOD);

    return 0;
}


ll phi(ll n, ll a) {
    ll result = 1;

    for(ll i = n + a - 1; i >= n; i--) {
        result *= i;
        result %= MOD;
    }

    for(ll i = 2; i <= a; i++) {
        result *= inv(i);
        result %= MOD;
    }

    return result;
}

ll inv(ll a) {
    return qpower(a, MOD - 2);
}

ll qpower(ll base, int exp) {
    if(exp == 0)
        return 1;

    if(exp % 2 == 1)
        return (base * qpower(base, exp - 1)) % MOD;

    ll res = qpower(base, exp/2);
    return (res * res) % MOD;
}

