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

const int DUZO = 10000010;
long long int prep[DUZO];
int sieve[DUZO];

long long int sqmobius(long long int n);

int main() {
    long long int N;
    cin >> N;

    long long int sN = floor(sqrt(N));

    for(long long int i = 2; i * i <= sN; i++) {
        if(sieve[i] != 0)
            continue;

        for(long long int j = 2*i; j <= sN; j += i) {
            sieve[j] = i;
        }
    }

    for(long long int i = 2; i * i <= sN; i++) {
        if(prep[i] != 0)
            continue;

        int p = i * i;

        for(long long int j = p; j <= sN; j += p)
            prep[j] = 1;
    }

    long long int res = 0;

    for(long long int i = 1; i * i <= N; i++) {
        if(prep[i] != 0)
            continue;

        res += sqmobius(i) * (N / (i * i));
    }

    cout << res << endl;

    return 0;
}

long long int sqmobius(long long int n) {
    if(n == 1)
        return 1;

    long long int res = -1;

    while(sieve[n] != 0) {
        res *= -1;
        n /= sieve[n];
    }

    return res;
}

