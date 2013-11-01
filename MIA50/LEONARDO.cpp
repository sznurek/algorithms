#include <iostream>
#include <string>
#include <vector>

using namespace std;

int cycle_length(vector<int>& perm, int start, vector<bool>& was) {
    int length = 1;
    int current = perm[start];
    was[start] = true;
    was[perm[start]] = true;

    while(perm[start] != perm[current]) {
        was[perm[current]] = true;
        current = perm[current];
        length++;
    }

    return length;
}

vector<int> cycles_lengths(vector<int>& perm) {
    vector<int> result;
    result.resize(27);
    vector<bool> was;
    was.resize(perm.size());

    for(int i = 1; i <= 26; i++) {
        if(was[i])
            continue;

        result[cycle_length(perm, i, was)]++;
    }

    return result;
}

int main() {
    int t;
    cin >> t;

    while(t --> 0) {
        string s;
        cin >> s;

        vector<int> perm;
        perm.resize(27);
        for(int i = 0; i < s.length(); i++) {
            perm[i + 1] = s[i] - 'A' + 1;
        }

        vector<int> cycles = cycles_lengths(perm);
        bool can_be = true;
        for(int i = 2; i <= 26; i += 2) {
            can_be = can_be && (cycles[i] % 2 == 0);
        }

        cout << (can_be ? "Yes" : "No") << endl;
    }

    return 0;
}
