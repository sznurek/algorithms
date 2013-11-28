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

string names[1024];
string ballots[1024];
int votes[1024];
int ids[1024];

bool cmp(int a, int b) {
    return votes[a] > votes[b];
}

int vote_for(string& b) {
    int cnt = 0;
    int last = -1;
    for(int i = 0; i < b.size(); i++) {
        if(b[i] == 'X') {
            cnt++;
            last = i;
        }
    }

    if(cnt != 1)
        return -1;

    return last;
}

int main() {
#ifndef BLASZAK
    freopen("bad.in", "r", stdin);
    freopen("bad.out", "w", stdout);
#endif

    int n, m;
    int invalid_votes = 0;
    cin >> n >> m;

    for(int i = 0; i < n; i++) {
        ids[i] = i;
        cin >> names[i];
    }

    for(int i = 0; i < m; i++) {
        string ballot;
        cin >> ballot;

        int number;
        if((number = vote_for(ballot)) == -1) {
            invalid_votes++;
        } else {
            votes[number]++;
        }
    }

    stable_sort(ids, ids + n, cmp);
    for(int i = 0; i < n; i++) {
        printf("%s %.2lf%%\n", names[ids[i]].c_str(), 100.0 * (double)votes[ids[i]]/m);
    }
    printf("Invalid %.2lf%%\n", 100.0 * (double)invalid_votes/m);

    return 0;
}

