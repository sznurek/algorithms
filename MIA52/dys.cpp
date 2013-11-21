#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int DUZO = 500010;
int first_free[DUZO];
bool used[DUZO];
vector<int> pointing[DUZO];

int main() {
    int n;
    scanf("%d", &n);

    first_free[1] = 2;
    for(int i = 2; i < n; i++) {
        first_free[i] = i + 1;
        pointing[i].push_back(i - 1);
    }
    first_free[n] = -1;
    pointing[n].push_back(n - 1);

    for(int i = 0; i < n; i++) {
        int q;
        scanf("%d", &q);

        for(unsigned int j = 0; j < pointing[q].size(); j++) {
            if(used[pointing[q][j]])
                continue;

            first_free[pointing[q][j]] = first_free[q];
            if(first_free[q] != -1)
                pointing[first_free[q]].push_back(pointing[q][j]);
        }

        used[q] = true;

        if(first_free[q] != -1) 
            printf("%d\n", first_free[q]);
        else
            printf("NIE\n");
    }

    return 0;
}

