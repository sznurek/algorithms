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

const int DUZO = 1000010;
int tab[DUZO];

inline int statistic(int start, int stop, int k);
inline int readint();

int main() {
    int t;

    scanf("%d", &t);
    while(t --> 0) {
        int n;

        n = readint();
        for(int i = 0; i < n; i++) {
            tab[i] = readint();
        }

        //int median = statistic(0, n, n/2);
        sort(tab, tab + n);
        int median = tab[n/2];
        int median_cnt = 0;
        bool all_less = true;
        bool all_more = true;

        for(int i = 0; i < n; i++) {
            if(tab[i] == median)
                median_cnt++;
            if(tab[i] < median)
                all_more = false;
            if(tab[i] > median)
                all_less = false;
        }

        if(median_cnt <= n/2) {
            printf("TAK\n");
        } else if(n % 2 == 1 && median_cnt == (n + 1) / 2 && (all_more || all_less)) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }

    return 0;
}

int statistic(int start, int stop, int k) {
    while(k != 0) {
        int pivot = (start + stop) / 2; //start + (rand() % (stop - start));
        int pivotVal = tab[pivot];

        swap(tab[pivot], tab[stop-1]);
        int store = start;
        for(int i = start; i < stop - 1; i++) {
            if(tab[i] <= pivotVal) {
                swap(tab[i], tab[store]);
                store++;
            }
        }

        swap(tab[store], tab[stop-1]);
        if(k < store - start) {
            stop = store;
        } else {
            k -= store - start;
            start = store;
        }
    }

    return tab[start];
}

int readint() {
    char c = fgetc_unlocked(stdin);
    while(isspace(c))
        c = fgetc_unlocked(stdin);

    int res = 0;
    while(isdigit(c)) {
        res *= 10;
        res += c - '0';

        c = fgetc_unlocked(stdin);
    }

    return res;
}

