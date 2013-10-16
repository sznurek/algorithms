#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int,int> p;

vector<p> tasks;

int main() {
    int n;

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int d, t;
        scanf("%d %d", &d, &t);
        tasks.push_back(make_pair(t, d));
    }

    sort(tasks.begin(), tasks.end());

    int deadline = 1000000000;
    for(int i = n - 1; i >= 0; i--) {
        int end_it_at = min(deadline, tasks[i].first);
        deadline = end_it_at - tasks[i].second;
    }

    printf("%d\n", deadline);

    return 0;
}

