#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define d if(0)

using namespace std;

const int DUZO = 5010;
int n, t;

vector<pair<int, int> > strips[DUZO];

int main() {
    scanf("%d %d", &n, &t);

    for(int i = 0; i < t; i++) {
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);

        strips[a - b + 1].push_back(make_pair(b, b + k));
    }

    int result = 0;
    vector<pair<int, int> > current(strips[1]);
    sort(current.begin(), current.end());
    d printf("First strip size: %d\n", current.size());
    for(int i = 1; i <= n; i++) {
        d printf("Processing strip %d...\n", i);
        int y = 1;
        int pos = 0;

        d printf("CURRENT STRIP LIMIT: %d\n", n - i + 1);
        while(pos < current.size() && y <= n - i + 1) {
            while(pos < current.size() && y > current[pos].second) {
                pos++;
            }

            if(pos == current.size())
                break;

            d printf("At strip [%d, %d] y: %d\n", current[pos].first, current[pos].second, y);

            if(y >= current[pos].first) {
                d printf("HIT!\n");
                result++;
            }

            y++;
        }

        for(int j = 0; j < current.size(); j++) {
            current[j].second--;
        }

        for(int j = 0; j < strips[i + 1].size(); j++) {
            current.push_back(strips[i + 1][j]);
        }

        sort(current.begin(), current.end());
        if(current.size() > 0) {
            vector<pair<int, int> > new_current;
            new_current.push_back(current[0]);

            for(int i = 1; i < current.size(); i++) {
                int new_right = new_current.back().second;
                if(current[i].second <= new_right)
                    continue;

                if(current[i].second - current[i].first >= 0) {
                    new_current.push_back(current[i]);
                }
            }

            current.swap(new_current);
        }
    }

    printf("%d\n", result);

    return 0;
}

