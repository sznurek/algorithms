// Problem: Gra
#include <cstdio>

using namespace std;

int main() {
    int t, n, k;

    scanf("%d", &t);
    while(t --> 0) {
        scanf("%d %d", &n, &k);

        if(k > n)
            printf("NIE\n");
        else if(3 * k > n)
            printf("TAK, ZWIEKSZY SIE\n");
        else if (n == 3 * k)
            printf("NIE\n");
        else
            printf("TAK, ZMNIEJSZY SIE\n");
    }
    
    return 0;
}
