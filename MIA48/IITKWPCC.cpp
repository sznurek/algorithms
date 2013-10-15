// Problem: Count right angle triangles
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int DUZO = 100010;
const int MOD  = 1000007;

typedef pair<int, int> point;
typedef enum {
    X_AXIS,
    Y_AXIS
} Axis;

int n;
vector<point> all_points;
vector<point> hashed[MOD];
vector<point> by_x[MOD];
vector<point> by_y[MOD];

inline int abs(int x) {
    return x >= 0 ? x : -x;
}

inline int hash(const point& p) {
    return (37 * abs(p.first) + 7 * abs(p.second)) % MOD;
}

inline int axis_hash(int x) { // or y
    return (37 * x) % MOD;
}

inline int get_axis(Axis a, const point& p) {
    if(a == X_AXIS)
        return p.first;
    return p.second;
}

inline Axis neg(Axis a) {
    if(a == X_AXIS)
        return Y_AXIS;
    return X_AXIS;
}

point third_point(Axis search_by, const point& p, int diff) {
    if(search_by == Y_AXIS)
        return make_pair(p.first, p.second - diff);
    return make_pair(p.first - diff, p.second);
}

bool exists(const point& p) {
    int h = hash(p);
    for(int i = 0; i < hashed[h].size(); i++) {
        if(p == hashed[h][i])
            return true;
    }

    return false;
}

int main() {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        point p;
        scanf("%d %d", &p.first, &p.second);

        all_points.push_back(p);
        hashed[hash(p)].push_back(p);
        by_x[axis_hash(p.first)].push_back(p);
        by_y[axis_hash(p.second)].push_back(p);
    }

    long long int answer = 0;
    for(int i = 0; i < n; i++) {
        const point& p = all_points[i];

        int x_hash = axis_hash(p.first);
        int y_hash = axis_hash(p.second);
        vector<point>* to_search;
        Axis search_by;

        if(by_x[x_hash].size() < by_y[y_hash].size()) {
            search_by = X_AXIS;
            to_search = &by_x[x_hash];
        } else {
            search_by = Y_AXIS;
            to_search = &by_y[y_hash];
        }

        for(int j = 0; j < to_search->size(); j++) {
            const point& pp = (*to_search)[j];
            if(pp == p || get_axis(search_by, pp) != get_axis(search_by, p))
                continue;

            int diff = get_axis(neg(search_by), p) - get_axis(neg(search_by), pp);
            if(exists(third_point(search_by, p, diff)))
                answer++;

            if(exists(third_point(search_by, p, -diff)))
                answer++;
        }
    }

    printf("%lld\n", answer);

    return 0;
}

