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
int n, r, k;
int passengers[DUZO];
vector<int> in_row[DUZO];
int inversions[DUZO][DUZO];

struct ITree {
    int mem[2*DUZO];

    ITree() {
        for(int i = 0; i < 2*DUZO; i++) {
            mem[i] = 0;
        }
    }

    void add(int x) {
        x += DUZO;
        while(x != 0) {
            mem[x]++;
            x /= 2;
        }
    }

    int query(int a, int b) {
        a += DUZO;
        b += DUZO;

        int result = 0;
        while(a < b) {
            if(a % 2 == 0) {
                a /= 2;
            } else {
                result += mem[a];
                a = a/2 + 1;
            }

            if(b % 2 == 1) {
                b /= 2;
            } else {
                result += mem[b];
                b = b/2 - 1;
            }
        }

        if(a == b)
            result += mem[a];
        return result;
    }
};

int dyn[64][DUZO];
void preprocess();

#define d if(0)

int main() {
#ifndef BLASZAK
    freopen("flight.in", "r", stdin);
    freopen("flight.out", "w", stdout);
#endif

    scanf("%d %d %d", &n, &r, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", passengers + i);
        in_row[passengers[i]].push_back(i);
    }

    preprocess();
    d printf("INversions:\n");
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= r; j++) {
            d printf("%d ", inversions[i][j]);
        }
        d printf("\n");
    }

    for(int start = r; start >= 1; start--) {
        for(int p = 1; p <= k; p++) {
            if(r - start + 1 < p)
                continue;

            if(p == 1) {
                dyn[p][start] = inversions[start][r];
            } else {
                dyn[p][start] = dyn[p-1][start+1];
                for(int next = start + 1; next <= r; next++) {
                    dyn[p][start] = min(dyn[p-1][next+1] + inversions[start][next], dyn[p][start]);
                }
            }
        }
    }

    d printf("DYN:\n");
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= k; j++) {
            d printf("%d ", dyn[j][i]);
        }
        d printf("\n");
    }

    cout << dyn[k][1] << endl;

    return 0;
}

void preprocess() {
    for(int i = 1; i <= r; i++) {
        ITree tree;

        inversions[i][i] = 0;
        for(int x = 0; x < in_row[i].size(); x++) {
            tree.add(in_row[i][x]);
        }

        for(int j = i + 1; j <= r; j++) {
            inversions[i][j] = inversions[i][j-1];
            for(int x = 0; x < in_row[j].size(); x++) {
                inversions[i][j] += tree.query(0, in_row[j][x]);
            }

            for(int x = 0; x < in_row[j].size(); x++) {
                tree.add(in_row[j][x]);
            }
        }
    }
}

