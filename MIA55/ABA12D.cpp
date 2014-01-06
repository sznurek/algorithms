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

const int DUZO = 2000200;
int sieve[DUZO];
int value[DUZO];

inline bool is_prime(int x);

int main() {
    for(int i = 2; i < DUZO; i++) {
        if(sieve[i] != 0) continue;

        for(int j = 2*i; j < DUZO; j += i)
            sieve[j] = 1;
    }

    for(int i = 2; i < 46349; i++) {
        if(!is_prime(i))
            continue;

        long long int k = i * i;
        while(k/i < DUZO/2) {
            value[k/i] = is_prime((k-1)/(i-1)) ? 1 : 0;
            k *= i;
        }
    }

    for(int i = 2; i < DUZO/2; i++)
        value[i] += value[i-1];

    int t, a, b;
    scanf("%d", &t);

    while(t --> 0) {
        scanf("%d", &a);
        scanf("%d", &b);

        printf("%d\n", value[b] - value[a-1]);
    }

    return 0;
}

bool is_prime(int x) {
    if(x < 2)
        return false;

    return sieve[x] == 0;
}

