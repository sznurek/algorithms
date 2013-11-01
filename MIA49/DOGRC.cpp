#include <cstdio>
#include <cmath>

using namespace std;

const double EPS = 0.0000001;

inline bool eps_eq(double a, double b) {
    return fabs(a - b) < EPS;
}

inline bool is_natural(double a) {
    return eps_eq(a, floor(a));
}

int count_digits(int n) {
    int digits = 0;
    int power = 1;

    if(n == 0)
        return 0;

    while(power <= n) {
        power *= 10;
        digits++;
    }

    return digits;
}

double solution(double x, int digits, int first_digit);
bool trick_works(double a, int digits, int first_digit);

int main() {
    double x;

    scanf("%lf", &x);
    if(eps_eq(x, 10)) {
        printf("No solution\n");
    } else {
        bool solution_exists = false;
        for(int digits = 1; digits <= 8; digits++) {
            for(int first_digit = 1; first_digit < 10; first_digit++) {
                double a = solution(x, digits, first_digit);
                if(!trick_works(a, digits, first_digit))
                    continue;

                solution_exists = true;
                printf("%.0lf\n", a);
            }
        }

        if(!solution_exists)
            printf("No solution\n");
    }

    return 0;
}

double solution(double x, int digits, int first_digit) {
    return 1.0 * double(first_digit) * (pow(10.0, double(digits)) - 1.0) / (10.0 - x);
}

bool trick_works(double a, int digits, int first_digit) {
    if(!is_natural(a))
        return false;

    int an = floor(a);
    int maybe_first = an / pow(10, digits - 1);

    if(count_digits(an) != digits)
        return false;

    return maybe_first == first_digit;
}

