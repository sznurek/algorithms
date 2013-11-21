#include <cstdio>
#include <algorithm>

using namespace std;

typedef unsigned long long int ll;
const ll MOD = 1000000007ll;
const int DUZO = 128;
int n;
ll k;

struct matrix {
    ll M[DUZO][DUZO];

    matrix mult(const matrix& m) const {
        matrix result;

        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                result.M[i][j] = 0;
                for(int k = 0; k <= n; k++) {
                    result.M[i][j] += (M[i][k] * m.M[k][j]) % MOD;
                    result.M[i][j] %= MOD;
                }
            }
        }

        return result;
    }
};

matrix qpower(const matrix& base, ll exp) {
    if(exp == 1)
        return base;

    if(exp % 2 == 1) {
        matrix res = qpower(base, exp - 1);
        return res.mult(base);
    }

    matrix res = qpower(base, exp/2);
    return res.mult(res);
}

matrix in;

int main() {
    int m;

    scanf("%d %d %llu", &n, &m, &k);
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        in.M[a-1][b-1] = 1;
    }

    in.M[n-1][n] = 1;
    in.M[n][n] = 1;

    matrix result = qpower(in, k + 1);

    printf("%llu\n", result.M[0][n]);

    return 0;
}

