#include <cstdio>
#include <vector>

using namespace std;

int n;
int diffletters;
int letters[128];
vector<int> found_letters;

int fac(int n) {
    if(n == 0)
        return 1;

    return fac(n - 1) * n;
}

int newton(int n, int k) {
    return fac(n) / (fac(k) * fac(n - k));
}

int main() {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);

        if(letters[k] == 0) {
            diffletters++;
            found_letters.push_back(k);
        }

        letters[k]++;
    }

    if(diffletters == 1) {
        printf("No\n");
    } else if(diffletters >= 3 || n >= 6) {
        printf("Yes\n");
    } else {
        int fst = found_letters[0];
        int snd = found_letters[1];

        int a = letters[fst];
        int b = letters[snd];

        if(newton(n, a) >= 6 || newton(n, b) >= 6) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}

