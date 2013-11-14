#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> d;

int main() {
    scanf("%d %d", &n, &m);

    for(int i = 0; i < m; i++) {
        int a;
        scanf("%d", &a);

        d.push_back(a);
    }

    if(m == 0) {
        printf("YES\n");
        return 0;
    }


    sort(d.begin(), d.end());

    bool canbe = ((d[0] != 1) && (d[m - 1] != n));
    for(int i = 0; i < m - 2; i++) {
        if(d[i] + 1 == d[i + 1] && d[i + 1] + 1 == d[i + 2]) {
            canbe = false;
            break;
        }
    }

    printf("%s\n", canbe ? "YES" : "NO");

    return 0;
}

