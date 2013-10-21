#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int, int> point;

int c;
point points[100010];

inline int dist2(const point& a, const point& b) {
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) * (a.second - b.second);
}

inline int cross(const point& o, const point& a, const point& b) {
    return (a.first - o.first) * (b.second - o.second) -
           (b.first - o.first) * (a.second - o.second);
}

inline bool turns_left(const point& p, const point& a, const point& b) {
    return cross(p, a, b) <= 0;
}

template <typename T>
inline T revat(const vector<T>& v, int i) {
    return v[v.size() - 1 - i];
}

inline bool turns_bad(const vector<point>& pts, const point& next) {
    if(pts.size() < 2)
        return false;

    return turns_left(revat(pts, 0), revat(pts, 1), next);
}

int main() {
    scanf("%d", &c);
    for(int i = 0; i < c; i++)
        scanf("%d %d", &points[i].first, &points[i].second);

    sort(points, points + c);
    vector<point> lower, upper;

    for(int i = 0; i < c; i++) {
        const point& p = points[i];
        while(turns_bad(lower, p))
            lower.pop_back();

        lower.push_back(p);
    }

    for(int i = c - 1; i >= 0; i--) {
        const point& p = points[i];
        while(turns_bad(upper, p))
            upper.pop_back();

        upper.push_back(p);
    }

    vector<point> hull;
    for(int i = 0; i < lower.size() - 1; i++)
        hull.push_back(lower[i]);

    for(int i = 0; i < upper.size() - 1; i++)
        hull.push_back(upper[i]);

    int first = 0;
    int second = 1;

    double best = 0;
    while(first < hull.size()) {
        while(second < hull.size() - 1 && 
              dist2(hull[first], hull[second]) < dist2(hull[first], hull[second + 1])) {
            second++;
        }

        best = max(best, sqrt(dist2(hull[first], hull[second])));
        first++;
    }

    printf("%.8lf\n", best);

    return 0;
}

