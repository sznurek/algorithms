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
    int n = 100000;
    vector<int> perm1;
    vector<int> perm2;

    for(int i = 1; i <= n; i++) {
        perm1.push_back(i);
        perm2.push_back(i);
    }

    random_shuffle(perm1.begin(), perm1.end());
    random_shuffle(perm2.begin(), perm2.end());

    printf("%d\n", n);
    for(int i = 0; i < n; i++) {
        printf("%d %d\n", perm1[i], perm2[i]);
    }

    return 0;
}

