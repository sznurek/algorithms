#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <set>

using namespace std;

typedef long long int ll;

vector<int> which_digits(int x) {
    vector<int> result;
    result.resize(10);

    while(x > 0) {
        result[x % 10] = 1;
        x /= 10;
    }

    return result;
};

bool k_good(vector<int> stat, int k) {
    for(int i = 0; i <= k; i++) {
        if(stat[i] == 0)
            return false;
    }

    return true;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int result = 0;
    for(int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        if(k_good(which_digits(a), k))
            result++;
    }

    printf("%d\n", result);

    return 0;
}

