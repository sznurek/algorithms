#include <cstdio>
#include <algorithm>

using namespace std;

const int DUZO = 100010;
int n;
int tab[DUZO];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", tab + i);

    int fst, snd;
    scanf("%d %d", &fst, &snd);

    if(fst == snd) {
        int fst_sum = 0;
        int snd_sum = 0;

        for(int i = 1; i < fst; i++)
            fst_sum += tab[i];

        for(int i = fst + 1; i <= n; i++)
            snd_sum += tab[i];

        printf("%d %d\n", max(fst_sum, snd_sum) + tab[fst], min(snd_sum, fst_sum));

        return 0;
    }

    int diff = max(fst, snd) - min(fst, snd) - 1;
    int divide = min(fst, snd) + diff / 2;

    if(diff % 2 == 1 && fst < snd)
        divide++;

    int fst_sum = 0;
    int snd_sum = 0;

    for(int i = 1; i <= divide; i++)
        fst_sum += tab[i];

    for(int i = divide + 1; i <= n; i++)
        snd_sum += tab[i];

    if(fst > snd)
        swap(snd_sum, fst_sum);

    printf("%d %d\n", fst_sum, snd_sum);

    return 0;
}

