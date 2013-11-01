#include <cstdio>

using namespace std;

typedef long long int ll;

char linearian(char start, ll a, ll b, ll pos);
char child(char lin, int number);

int main() {
    ll y, p;

    scanf("%lld %lld", &y, &p);
    char result = linearian('R', 0, (1ll << y), p);

    printf("%s\n", result == 'R' ? "red" : "blue");

    return 0;
}

char linearian(char start, ll a, ll b, ll pos) {
    if(a == pos && b == a + 1)
        return start;

    ll mid = (a + b) / 2;
    if(pos < mid) {
        return linearian(child(start, 0), a, mid, pos);
    }
    return linearian(child(start, 1), mid, b, pos);
}

char child(char lin, int number) {
    if(number == 1)
        return lin;

    return (lin == 'B') ? 'R' : 'B';
}
