#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

#define d if(1)

using namespace std;

const int DUZO  = (1 << 23);
const int FIRST = DUZO / 2;;
const int DIFF = 1000000;

struct segment {
    pair<int, int> lower, upper;
    segment(int x1, int y1, int x2, int y2) {
        lower = make_pair(x1, y1);
        upper = make_pair(x2, y2);

        if(y2 < y1)
            swap(lower, upper);
    }

    bool operator<(const segment& s) const {
        if(lower == s.lower)
            return upper > s.upper;
        return lower > s.lower;
    }
};

int tree[DUZO];
vector<pair<int, segment> > segments;

void add(int start, int stop, int val, int v=1, int left=0, int right=FIRST);
int query(int point);

int main() {
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        segment s(x1, y1, x2, y2);
        segments.push_back(make_pair(s.lower.second, s));
        segments.push_back(make_pair(s.upper.second, s));
    }

    int x_ball;
    scanf("%d", &x_ball);

    sort(segments.rbegin(), segments.rend());
    for(int i = 0; i < segments.size(); i++) {
        segment& s = segments[i].second;
        int min_x = min(s.lower.first, s.upper.first);
        int max_x = max(s.lower.first, s.upper.first);
        if(segments[i].first == s.upper.second) {
            d printf("First time: (%d, %d) - (%d, %d)\n", s.lower.first, s.lower.second,
                    s.upper.first, s.upper.second);
            add(min_x + DIFF, max_x + DIFF, 1);
        } else {
            d printf("Second time: (%d, %d) - (%d, %d)\n", s.lower.first, s.lower.second,
                    s.upper.first, s.upper.second);
            add(min_x + DIFF, max_x + DIFF, -1);
            int covered_by = query(x_ball + DIFF);
            if(covered_by == 0 && min_x <= x_ball && x_ball <= max_x) {
                x_ball = s.lower.first;
                d printf("Changing x_ball: %d\n", x_ball);
            }
        }
    }

    printf("%d\n", x_ball);

    return 0;
}

void add(int start, int stop, int val, int v, int left, int right) {
    if((left == start && stop + 1 == right) || left + 1 == right) {
        tree[v] += val;
        return;
    }

    int middle = (right + left) / 2;
    int smiddle = (start + stop) / 2;
    if(stop < middle) {
        add(start, stop, val, 2*v, left, middle);
    } else if(start >= middle) {
        add(start, stop, val, 2*v+1, middle, right);
    } else {
        add(start, smiddle, val, 2*v, left, middle);
        add(smiddle, stop, val, 2*v+1, middle, right);
    }
}

int query(int point) {
    int result = 0;
    point += FIRST;

    while(point != 0) {
        result += tree[point];
        point /= 2;
    }

    return result;
}

