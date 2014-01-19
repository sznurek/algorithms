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
    int n;
    priority_queue<int> astr;

    scanf("%d", &n);
    int time = 0;
    int power = 0;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int t, d;
        scanf("%d %d", &t, &d);

        power += t - time;
        power -= d;

        astr.push(d);

        while(power < 0) {
            power += astr.top();
            astr.pop();
            res++;
        }

        time = t;
    }

    printf("%d\n", res);

    return 0;
}

