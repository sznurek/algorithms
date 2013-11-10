#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

typedef long long int ll;
const int DUZO = 1 << 20;

ll d, n;
pair<ll, ll> input[DUZO];
vector<pair<ll, ll> > intervals;

bool valid(ll t) {
    intervals.clear();

    for(int i = 0; i < n; i++) {
        if(input[i].second > t)
            continue;

        ll delta = t - input[i].second;
        intervals.push_back(make_pair(input[i].first - delta, input[i].first + delta));
    }

    sort(intervals.begin(), intervals.end());

    if(intervals.empty())
        return false;

    if(intervals[0].first > 0)
        return false;

    ll most_right = intervals[0].second;
    for(int i = 1; i < intervals.size(); i++) {
        if(intervals[i].first > most_right)
            return false;

        most_right = max(most_right, intervals[i].second);
    }

    return most_right >= d;
}

int main() {
    scanf("%lld %lld", &d, &n);

    for(int i = 0; i < n; i++) {
        ll x, t;
        scanf("%lld %lld", &x, &t);
        input[i] = make_pair(x, t);
    }

    ll start = 0;
    ll stop = 4000000010;

    while(stop - start > 10) {
        ll mid = (start + stop) / 2;

        if(valid(mid)) {
            stop = mid + 1;
        } else {
            start = mid;
        }
    }

    for(ll i = start; i <= stop; i++) {
        if(valid(i)) {
            printf("%lld\n", i);
            return 0;
        }
    }

    return 0;
}

