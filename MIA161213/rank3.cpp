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

ll inversions(const vector<int>& a, const vector<int>& b);
pair<vector<int>, ll> merge(const vector<int>& a, const vector<int>& b);
pair<vector<int>, ll> msort(const vector<int>& a);

int main() {
    int n;
    vector<int> a, b, c;

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int ai, bi, ci;
        scanf("%d %d %d", &ai, &bi, &ci);

        a.push_back(ai-1);
        b.push_back(bi-1);
        c.push_back(ci-1);
    }

    printf("%lld\n", (inversions(a, b) + inversions(b, c) + inversions(a, c)) / 2);

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

ll inversions(const vector<int>& a, const vector<int>& b) {
    vector<int> perm;
    perm.resize(a.size());

    for(int i = 0; i < a.size(); i++)
        perm[a[i]] = b[i];

    pair<vector<int>, ll> res = msort(perm);
    return res.second;
}

