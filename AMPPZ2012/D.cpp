#include <cstdio>

using namespace std;

const int DUZO = 10010;
const int NLETTERS = 4;
char letters[4] = {'A', 'C', 'G', 'T'};

int n;
char input[DUZO];
int counts[256];

int main() {
    scanf("%d %s", &n, input);

    for(int i = 0; i < n; i++)
        counts[input[i]]++;

    char minimal = letters[0];
    for(int i = 1; i < NLETTERS; i++) {
        if(counts[minimal] > counts[letters[i]])
            minimal = letters[i];
    }

    printf("%d\n", counts[minimal]);
    for(int i = 0; i < n; i++) {
        printf("%c", minimal);
    }
    printf("\n");

    return 0;
}

