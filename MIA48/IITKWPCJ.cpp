// Problem: Check the string powers
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int t;
    ios_base::sync_with_stdio(0);

    cin >> t;
    while(t --> 0) {
        string A, B, AA, BB;
        cin >> A >> B;

        int d = __gcd(A.length(), B.length());
        string C = A.substr(0, d);
        while(AA.length() < A.length()) AA += C;
        while(BB.length() < B.length()) BB += C;

        if(A == AA && B == BB)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}

