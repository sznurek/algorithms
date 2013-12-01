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

const int DUZO = 1024;

double times[2][DUZO];
double best[2][1024];

int n;
double p;

int main() {
    int t;
    scanf("%d", &t);

    while(t --> 0) {
        scanf("%d %lf", &n, &p);

        for(int i = 1; i <= n; i++) {
            scanf("%lf %lf", &times[0][i], &times[1][i]);
            best[0][i] = best[0][i-1] + times[0][i];
            best[1][i] = best[1][i-1] + times[1][i];
        }

        for(int o = 0; o < 2; o++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j < i && j <= (i + 1)/2; j++) {
                    best[o][i] = min(best[o][i], best[o][i-j] + p + best[o][j]);
                }
            }
        }

        double fastest = best[1][1] + best[0][n-1] + p;
        for(int i = 2; i < n; i++) {
            fastest = min(fastest, best[1][i] + best[0][n-i] + p);
        }

        printf("%.3lf\n", fastest);
    }


    return 0;
}

