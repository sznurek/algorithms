#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int DUZO = 1000010;
int seq[DUZO];

int main() {
    int n;

    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);

    vector<int> ends;
    ends.push_back(0);

    int max_seen = seq[1];
    for(int i = 1; i <= n; i++) {
        max_seen = max(max_seen, seq[i]);

        if(max_seen == i) {
            ends.push_back(i);
        }
    }
    printf("%d\n", ends.size() - 1);
    for(int i = 0; i < ends.size() - 1; i++) {
        printf("%d ", ends[i + 1] - ends[i]);
        for(int j = ends[i] + 1; j <= ends[i + 1]; j++)
            printf("%d ", j);
        printf("\n");
    }

    return 0;
}

