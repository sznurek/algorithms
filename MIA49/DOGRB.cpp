#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

struct burak {
    burak(double w, int c = 1) : w(w), c(c) {}
    bool operator<(const burak& b) const {
        return piece() < b.piece();
    }
    double piece() const {
        return ((double)w/c);
    }

    double w;
    int c;
};

int main() {
    int n;
    double t;

    priority_queue<burak> q;
    scanf("%lf %d", &t, &n);

    double maximum = -1, minimum = 1000000000;
    for(int i = 0; i < n; i++) {
        double w;
        scanf("%lf", &w);

        q.push(burak(w));
        minimum = min(minimum, w);
        maximum = max(maximum, w);
    }

    int cuts = 0;
    while(t * (q.top().piece()) >= minimum) {
        burak b = q.top();
        q.pop();

        b.c++;
        cuts++;
        q.push(b);
        minimum = min(minimum, b.piece());
    }

    printf("%d\n", cuts);

    return 0;
}

