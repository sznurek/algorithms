// Problem: Equalize the Sectors
#include <cstdio>

using namespace std;

typedef long long int ll;
const int DUZO = 128;

int n;
ll input[DUZO];
ll deltas[DUZO];
bool cycled[DUZO];

inline int next(int i) {
    return (i + 2) % n;
}

ll cyclesum(int start) {
    if(cycled[start])
        return 0;

    cycled[start] = true;
    return deltas[start] + cyclesum(next(start));
}

int main() {
    int t;

    scanf("%d", &t);
    while(t --> 0) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%lld", &input[i]);

        for(int i = 0; i < n; i++) {
            int second = (i + 1) % n;
            deltas[i] = input[i] - input[second];
            cycled[i] = false;
        }

        bool valid = true;
        for(int i = 0; i < n; i++) {
            if(cyclesum(i) != 0) {
                valid = false;
                break;
            }
        }

        printf("%s\n", valid ? "YES" : "NO");
    }

    return 0;
}
