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

const int DUZO = 200200;

ll inversions(const vector<int>& a);
pair<vector<int>, ll> merge(const vector<int>& a, const vector<int>& b);
pair<vector<int>, ll> msort(const vector<int>& a);

int main() {
    int n;
    vector<int> a;

    scanf("%d", &n);
    a.resize(n);
    for(int i = 0; i < n; i++) {
        int ai, bi;
        scanf("%d %d", &ai, &bi);

        a[ai-1] = bi;
    }

    printf("%lld\n", inversions(a));

    return 0;
}

pair<vector<int>, ll> merge(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    ll invs = 0;

    int left = 0, right = 0;
    while(left < a.size() && right < b.size()) {
        if(a[left] <= b[right]) {
            result.push_back(a[left]);
            left++;
        } else {
            result.push_back(b[right]);
            invs += a.size() - left;
            right++;
        }
    }

    while(right < b.size()) {
        result.push_back(b[right]);
        right++;
    }

    while(left < a.size()) {
        result.push_back(a[left]);
        left++;
    }

    return make_pair(result, invs);
}

pair<vector<int>, ll> msort(const vector<int>& a) {
    if(a.size() <= 1) {
        return make_pair(a, 0);
    }

    vector<int> left, right;

    for(int i = 0; i < a.size() / 2; i++) {
        left.push_back(a[i]);
    }

    for(int j = a.size() / 2; j < a.size(); j++) {
        right.push_back(a[j]);
    }

    pair<vector<int>, ll> lres = msort(left);
    pair<vector<int>, ll> rres = msort(right);
    pair<vector<int>, ll> mres = merge(lres.first, rres.first);

    return make_pair(mres.first, lres.second + rres.second + mres.second);
}

ll inversions(const vector<int>& a) {
    //for(int i = 0; i < a.size(); i++)
    //    printf("%d ", a[i]);
    //printf("\n");
    pair<vector<int>, ll> res = msort(a);
    return res.second;
}

