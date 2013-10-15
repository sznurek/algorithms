// Problem: Wycieczka 2
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int DUZO = 2048;
int n;
int A[DUZO][DUZO];
int B[DUZO][DUZO];

vector<int> multiply(int M[DUZO][DUZO], vector<int> v);
vector<int> rand_vector();

int main() {
    srand(7642342);
    int t;
    scanf("%d", &t);

    n = 2000;
    vector<int> v = rand_vector();
    while(t --> 0) {
        scanf("%d", &n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &A[i][j]);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &B[i][j]);

        bool valid = true;
        for(int i = 0; i < 1; i++) {
            vector<int> a1 = multiply(A, v);
            vector<int> a2 = multiply(A, a1);
            vector<int> b = multiply(B, v);

            if(a2 != b) {
                valid = false;
                break;
            }
        }

        printf("%s\n", valid ? "TAK" : "NIE");
    }

    return 0;
}

vector<int> rand_vector() {
    vector<int> result;

    for(int i = 0; i < n; i++)
        result.push_back(rand());

    return result;
}

vector<int> multiply(int M[DUZO][DUZO], vector<int> v) {
    vector<int> result;

    for(int i = 0; i < n; i++) {
        int row = 0;
        for(int j = 0; j < n; j++) {
            row += M[i][j] * v[j];
        }
        result.push_back(row);
    }

    return result;
}

