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

const int DUZO = 1 << 16;

int k, n;
int numbers[DUZO];

void print_range(int start, int stop);

int main() {
    scanf("%d", &k);
    n = (1 << k) - 1;

    for(int i = 0; i < n; i++)
        scanf("%d", &numbers[i]);

    print_range(0, n-1);
    puts("");

    return 0;
}

void print_range(int start, int stop) {
    queue<pi> q;

    int last_length = stop - start + 1;
    q.push(make_pair(start, stop));

    while(!q.empty()) {
        pi t = q.front();
        q.pop();


        int new_length = t.second - t.first + 1;
        if(new_length < last_length) {
            printf("\n");
        }

        int middle = (t.second + t.first) / 2;

        printf("%d ", numbers[middle]);
        last_length = new_length;

        if(t.first != t.second) {
            q.push(make_pair(t.first, middle - 1));
            q.push(make_pair(middle + 1, t.second));
        }
    }
}

