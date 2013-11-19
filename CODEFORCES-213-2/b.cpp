#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <set>

using namespace std;

typedef pair<int,int> pi;
typedef long long int ll;

const int DUZO = 100010;
int n;
bool valid[DUZO];
int input[DUZO];

pi longest_valid();

int main() {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", input + i);
        if(i > 1 && input[i] == input[i-1] + input[i-2])
            valid[i] = true;
    }

    pi best = longest_valid();
    if(best.first == 0 && best.second == 0) {
        printf("%d\n", n == 1 ? 1 : 2);
    } else {
        printf("%d\n", best.second - best.first + 2);
    }

    return 0;
}

pi longest_valid() {
    pi best = make_pair(0, 0);

    int start = 0;
    int stop = 0;
    while(start < n) {
        while(start < n && !valid[start]) {
            start++;
        }

        if(start == n) {
            break;
        }

        stop = start;
        while(stop < n && valid[stop]) {
            stop++;
        }

        if(best.second - best.first <= stop - start)
            best = make_pair(start, stop);

        start = stop;
    }

    return best;
}

