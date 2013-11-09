#include <cstdio>

using namespace std;

int F(int x, int n) {
    return (((x & ((1 << (n / 2)) - 1)) << ((n + 1) / 2)) | (x >> (n / 2)));
}

int main() {
    for(int i = 0; i < 256; i++) {
        printf("0x%x -> 0x%x\n", i, F(i, 8));
    }

    return 0;
}
