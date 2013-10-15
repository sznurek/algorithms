// Problem: Wycieczka 1
#include <cstdio>

using namespace std;
const int DUZO = 128;

int n;
int input[DUZO][DUZO];
int verify[DUZO][DUZO];

int main() {
    int t;
    scanf("%d", &t);

    while(t --> 0) {
        scanf("%d", &n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &input[i][j]);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &verify[i][j]);

        bool valid = true;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int result = 0;
                for(int k = 0; k < n; k++) {
                    result += input[i][k] * input[k][j];
                }

                if(result != verify[i][j]) {
                    valid = false;
                    break;
                }
            }

            if(!valid)
                break;
        }

        printf("%s\n", valid ? "TAK" : "NIE");
    }

    return 0;
}

