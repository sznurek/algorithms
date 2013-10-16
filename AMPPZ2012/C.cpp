#include <cstdio>
#include <algorithm>

using namespace std;

const int DUZO = 1000010;

int n, k;
int input[DUZO];
int zeros[DUZO];
int ones[DUZO];

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &input[i]);
        input[i] %= 2;
    }

    for(int i = 0; i < k; i++) {
        for(int j = 0; j * k + i < n; j++) {
            if(input[j * k + i] == 0)
                zeros[i]++;
            else
                ones[i]++;
        }
    }

    int result = 0;
    int first_sum = 0;
    int best_diff = 0;
    for(int i = 0; i < k; i++) {
        result += min(zeros[i], ones[i]);
        if(zeros[i] < ones[i]) {
            first_sum += 1;
        }

        int diff = max(zeros[i], ones[i]) - min(zeros[i], ones[i]);
        int bdiff = max(zeros[best_diff], ones[best_diff]) - min(zeros[best_diff], ones[best_diff]);
        if(diff < bdiff)
            best_diff = i;
    }

    if(first_sum % 2 != 0) {
        result -= min(zeros[best_diff], ones[best_diff]);
        result += max(zeros[best_diff], ones[best_diff]);
    }

    printf("%d\n", result);

    return 0;
}
