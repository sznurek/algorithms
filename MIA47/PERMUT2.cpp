// Problem: Ambiguous permutation
#include <cstdio>

const int DUZO = 1000010;

int perm[DUZO];
int invperm[DUZO];

int main() {
    int n;
    while(true) {
        scanf("%d", &n);
        if(n == 0)
            break;

        for(int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);

            perm[i] = a;
            invperm[a] = i;
        }

        bool same = true;
        for(int i = 1; i <= n; i++) {
            if(perm[i] != invperm[i]) {
                same = false;
                break;
            }
        }

        printf("%s\n", same ? "ambiguous" : "not ambiguous");
    }

    return 0;
}
