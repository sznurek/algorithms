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

const int MALO = 64;
const int DUZO = 10010 * MALO;

int n, d;
int price[MALO];
int backpack[DUZO];

void backpackize(int max_cost);

int main() {
    scanf("%d %d", &n, &d);

    int summa = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", price + i);
        summa += price[i];
    }

    summa += d + 10;
    backpackize(summa);

    int days = 0;
    int value = 0;

    while(true) {
        int next_best = -1;
        for(int i = value + d; i > value; i--) {
            if(backpack[i]) {
                next_best = i;
                break;
            }
        }

        if(next_best == -1)
            break;

        days++;
        value = next_best;
    }

    printf("%d %d\n", value, days);

    return 0;
}

void backpackize(int max_cost) {
    backpack[0] = 1;

    for(int i = 0; i < n; i++) {
        for(int j = max_cost - price[i]; j >= 0; j--) {
            if(!backpack[j]) continue;

            backpack[j + price[i]] = 1;
        }
    }
}

