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

const int DUZO = (1 << 14);

pi people[DUZO];
int first_free[DUZO];
int result[DUZO];

class DynamicStat {
    public:
        void clear(int n) {
            for(int i = 0; i < n; i++)
                tree[DUZO + i] = 1;

            for(int i = DUZO - 1; i >= 1; i--)
                tree[i] = tree[2*i] + tree[2*i + 1];
        }

        void erase(int pos) {
            int current = DUZO + pos;
            while(current >= 1) {
                tree[current]--;
                current /= 2;
            }
        }

        int kth(int k) {
            int current = 1;

            while(current < DUZO) {
                if(k < tree[2*current]) {
                    current *= 2;
                } else {
                    k -= tree[2*current];
                    current = 2*current + 1;
                }
            }

            return current - DUZO;
        }

        int tree[2*DUZO];
};

DynamicStat dyn;
void insert(int pos, int h);

int main() {
    int t;
    
    scanf("%d", &t);
    while(t --> 0) {
        int n;
        scanf("%d", &n);

        for(int i = 0; i < n; i++)
            scanf("%d", &people[i].first);

        for(int i = 0; i < n; i++)
            scanf("%d", &people[i].second);

        sort(people, people + n);

        dyn.clear(n);
        for(int i = 0; i < n; i++) {
            insert(people[i].second, people[i].first);
        }

        for(int i = 0; i < n; i++)
            printf("%d ", result[i]);
        printf("\n");
    }

    return 0;
}

void insert(int pos, int h) {
    int real_pos = dyn.kth(pos);
    dyn.erase(real_pos);

    result[real_pos] = h;
}

