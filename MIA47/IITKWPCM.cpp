// Problem: Coprime again
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <inttypes.h>

using namespace std;

typedef unsigned long long int ll;
ll gcd(ll a, ll b);
ll brute(ll n);
ll fast(ll n);
bool is_prime(ll n);
bool is_prime_power(ll n);

ll qpow(ll a, ll b, ll m);
ll qpow_fast(ll a, ll b, ll m);
ll npow(ll a, ll b, ll limit);
ll qmul(ll a, ll b, ll m);
bool single_rm_probably_prime(ll prime, ll witness);
bool rm_is_prime(ll n);
bool rm_is_prime_small(ll n);
bool rm_is_prime_power(ll n);

vector<ll> witnesses, small_witnesses;
const int PRIMES_TO = 1024;
bool small_primes[PRIMES_TO];
vector<int> primes;

int main() {
    witnesses.push_back(2);
    witnesses.push_back(3);
    //witnesses.push_back(5);
    witnesses.push_back(7);
    //witnesses.push_back(11);
    witnesses.push_back(13);
    witnesses.push_back(17);
    //witnesses.push_back(19);
    witnesses.push_back(23);
    witnesses.push_back(29);

    small_witnesses.push_back(31);
    small_witnesses.push_back(73);

    for(int i = 2; i < PRIMES_TO; i++) {
        small_primes[i] = is_prime(i);
    }
#if 0
    printf("Is prime power 3^40? %d\n", rm_is_prime_power(npow(3, 40, 1000000000000000000ll)));
    printf("Is prime power 5^25? %d\n", rm_is_prime_power(npow(5, 25, 1000000000000000000ll)));
    printf("Is prime power 7^20? %d\n", rm_is_prime_power(npow(7, 20, 1000000000000000000ll)));
    printf("Is prime power 3571^5? %d\n", rm_is_prime_power(npow(3571, 5, 1000000000000000000ll)));
    printf("Is prime power 115249^3? %d\n", rm_is_prime_power(npow(115249, 3, 1000000000000000000ll)));

    for(ll i = 2; i <= 10000; i++) {
        if(fast(i) != brute(i)) {
            printf("SOLUTION MISMATCH at %lld! Brute: %lld Fast: %lld\n", i, brute(i), fast(i));
        }
    }

    printf("SOLUTION TESTING DONE\n");

    /*
    for(ll i = 2; i <= 10000; i++) {
        if(is_prime(i) != rm_is_prime(i)) {
            printf("PRIME MISMATCH at %lld! Brute: %d RM: %d\n", i, is_prime(i), rm_is_prime(i));
        }
    }

    printf("PRIMALITY TESTING DONE\n");

    for(ll i = 2; i <= 10000; i++) {
        if(is_prime_power(i) != rm_is_prime_power(i)) {
            printf("PRIME POWER MISMATCH at %lld! Brute: %d RM: %d\n", i, is_prime_power(i), rm_is_prime_power(i));
            break;
        }
    }

    printf("PRIMALITY POWER TESTING DONE\n");
    */
#else
    int t;
    scanf("%d", &t);
    while(t --> 0) {
        ll n;
        scanf("%llu", &n);
        printf("%llu\n", fast(n));
    }

    return 0;
#endif
}

ll fast(ll n) {
    if(n == 1)
        return 0;

    ll rest = n;
    int alpha0 = 0;
    while(rest % 2 == 0) {
        rest /= 2;
        alpha0++;
    }

    if(rest == 1) {
        if(alpha0 == 2)
            return 3;
        return 1;
    }

    if(alpha0 >= 2)
        return 1;

    if(alpha0 == 1) {
        if(rm_is_prime_power(rest))
            return n - 1;
        return 1;
    }

    // No powers of two.
    if(rm_is_prime_power(n))
        return n - 1;
    return 1;
}

ll qmul(ll a, ll b, ll m) {
    if(a < b)
        swap(a, b);
    if(a > m)
        a %= m;
    if(b > m)
        b %= m;

    ll result = 0, acc = a;

    while(b != 0) {
        while(acc < m) {
            if((b & 1) != 0)
                result += acc;
            acc *= 2;
            b /= 2;

            if(acc == 0)
                return 0;
        }

        acc -= m;
        while(result >= m)
            result -= m;
        if(acc < b)
            swap(acc, b);
    }

    return result % m;
}


bool rm_is_prime_power(ll n) {
    if(rm_is_prime(n))
        return true;

    for(int idx = 0; idx < witnesses.size(); idx++) {
        ll i = witnesses[idx];
        if(n % i != 0) continue;

        while(n % i == 0) n /= i;
        if(n == 1)
            return true;
        else
            return false;
    }

    for(int i = 2; i <= 12; i++) {
        ll maybe_prime = round(pow(n, 1.0 / i));
        if(npow(maybe_prime, i, n) != n)
            continue;

        if(i >= 3) {
            if(rm_is_prime_small(maybe_prime))
                return true;
        } else {
            if(rm_is_prime(maybe_prime))
                return true;
        }
    }

    return false;
}

bool rm_is_prime(ll n) {
    if(n < PRIMES_TO && small_primes[n])
        return true;

    for(int i = 0; i < witnesses.size(); i++) {
        if(witnesses[i] > n - 2) continue;
        if(!single_rm_probably_prime(n, witnesses[i]))
            return false;
    }

    return true;
}

bool rm_is_prime_small(ll n) {
    if(n < PRIMES_TO && small_primes[n])
        return true;

    for(int i = 0; i < small_witnesses.size(); i++) {
        if(small_witnesses[i] > n - 2) continue;
        if(!single_rm_probably_prime(n, small_witnesses[i]))
            return false;
    }

    return true;
}

bool single_rm_probably_prime(ll prime, ll witness) {
    ll m = prime - 1;
    int alpha = 0;
    while(m % 2 == 0) {
        m /= 2;
        alpha++;
    }

    ll t;
    if(prime < 1000000000)
        t = qpow_fast(witness, m, prime);
    else
        t = qpow(witness, m, prime);
    if(t == 1 || t == prime - 1)
        return true;

    while(alpha > 0) {
        if(t == prime - 1)
            return true;
        if(prime < 1000000000) {
            t *= t;
            t %= prime;
        } else {
            t = qmul(t, t, prime);
        }
        alpha--;
    }

    return false;
}

ll qpow(ll a, ll b, ll m) {
    ll result = 1, acc = a % m;
    while(b != 0) {
        if((b & 1) != 0) {
            result = qmul(result, acc, m);
            b--;
        }

        acc = qmul(acc, acc, m);
        b /= 2;
    }

    return result % m;
}

ll qpow_fast(ll a, ll b, ll m) {
    ll result = 1, acc = a % m;
    while(b != 0) {
        if((b & 1) != 0) {
            result *= acc;
            if(result >= 1000000000)
                result %= m;
            b--;
        }

        acc *= acc;
        if(acc >= 1000000000)
            acc %= m;
        b /= 2;
    }

    return result % m;
}

ll npow(ll a, ll b, ll limit) {
    ll result = 1, acc = a;
    while(b != 0) {
        if((b & 1) != 0) {
            result *= acc;
            b--;
        }

        acc = acc * acc;
        b /= 2;

        if(result > limit)
            return result;
    }

    return result;
}

bool is_prime_power(ll n) {
    for(ll p = 2; p <= n; p++) {
        if(!is_prime(p)) continue;

        ll current = p;
        while(current < n) {
            current *= p;
        }

        if(current == n)
            return true;
    }
    return false;
}

bool is_prime(ll n) {
    for(ll i = 2; i * i <= n; i++) {
        if(n % i == 0)
            return false;
    }
    return true;
}

ll gcd(ll a, ll b) {
    if(a < b) swap(a, b);
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

ll brute(ll n) {
    ll result = 1;
    for(ll i = 2; i < n; i++) {
        if(gcd(i, n) != 1) continue;
        result *= i;
        result %= n;
    }
    return result;
}

