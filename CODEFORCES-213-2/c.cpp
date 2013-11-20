#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <map>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

const int DUZO = 4096;

int a, n;
char input[DUZO];
ll counts[100 * DUZO];

int main() {
    scanf("%d %s", &a, input);
    n = strlen(input);

    ll max_sum = 0;
    for(int i = 1; i <= n; i++) {
        ll sum = 0;
        for(int j = i; j <= n; j++) {
            sum += input[j-1] - '0';
            counts[sum]++;
        }

        max_sum = max(max_sum, sum);
    }

    ll result = 0;
    if(a == 0) {
        for(int i = 1; i <= max_sum; i++) {
            result += counts[0] * counts[i];
        }

        result *= 2;
        result += counts[0] * counts[0];
    } else {
        for(int i = 1; i <= max_sum; i++) {
            if(a % i != 0 || a/i > max_sum) continue;

            result += counts[i] * counts[a/i];
        }
    }

    cout << result << endl;

    return 0;
}

