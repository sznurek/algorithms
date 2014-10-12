#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef unsigned int ui;
typedef pair<ui, ui> pui;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

const int MALO = 16;
const int BASE = 33;

int n;
int pattern_len;
string text;
string patterns[MALO];
ui pattern_hashes[MALO];
int perm[MALO];

inline bool realcmp(int start);
ui power(ui base, int e);

int main() {
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> patterns[i];
        pattern_len += patterns[i].size();
    }

    cin >> text;

    if(pattern_len > text.size()) {
        cout << "0\n";
        return 0;
    }

    for(int i = 0; i < n; i++)
        perm[i] = i;

    vector<pui> text_hashes;
    ui text_hash = 0;
    ui base_k = 1;
    for(int i = 0; i < pattern_len; i++) {
        text_hash = BASE * text_hash + text[i];
        base_k *= BASE;
    }

    text_hashes.push_back(make_pair(text_hash, 0));

    //cout << "text hash (before sort) " << text_hash << endl;
    for(int j = 1; j <= text.size() - pattern_len; j++) {
        text_hash = BASE * text_hash + text[pattern_len - 1 + j];
        text_hash -= (ui)text[j-1] * base_k;

        text_hashes.push_back(make_pair(text_hash, j));
        //cout << "text hash (before sort) " << text_hash << endl;
    }

    sort(text_hashes.begin(), text_hashes.end());
    /*
    for(int i = 0; i < text_hashes.size(); i++) {
        cout << "text_hash " << text_hashes[i].first << endl;
    }
    */

    for(int i = 0; i < n; i++) {
        pattern_hashes[i] = 0;
        for(int j = 0; j < patterns[i].size(); j++) {
            pattern_hashes[i] = BASE * pattern_hashes[i] + patterns[i][j];
        }
        //cout << "pattern " << i << " hash " << pattern_hashes[i] << endl;
    }

    map<ui, long long int> was;

    long long int result = 0;
    do {
        ll local_res = 0;
        ui pattern_hash = 0;
        int lengths = 0;
        for(int i = 0; i < n; i++) {
            pattern_hash += pattern_hashes[perm[i]] * power(BASE, lengths);
            lengths += patterns[perm[i]].size();
        }

        if(was.count(pattern_hash) != 0) {
            result += was[pattern_hash];
            continue;
        }

        //cout << "pattern hash " << pattern_hash << endl;

        vector<pui>::iterator start = lower_bound(text_hashes.begin(), text_hashes.end(),
                make_pair(pattern_hash, (unsigned int)0));

        while(start != text_hashes.end() && start->first == pattern_hash) {
            //cout << "YEAH!\n";
            if(realcmp(start->second)) {
                //cout << "GREAT!\n";
                local_res++;
            }

            start++;
        }

        result += local_res;
        was[pattern_hash] = local_res;
    } while(next_permutation(perm, perm + n));

    cout << result << endl;

    return 0;
}

bool realcmp(int start) {
    int current_pattern = 0;
    int pattern_diff = 0;
    for(int i = 0; i < pattern_len; i++) {
        if(__builtin_expect(patterns[perm[current_pattern]].size() <= i - pattern_diff, 0)) {
            pattern_diff += patterns[perm[current_pattern]].size();
            current_pattern++;
        }

        if(__builtin_expect(text[start + i] != patterns[perm[current_pattern]][i - pattern_diff], 0))
            return false;
    }

    return true;
}

ui power(ui base, int e) {
    if(e == 0)
        return 1;

    if(e % 2 == 0) {
        ui a = power(base, e/2);
        return a * a;
    }

    return base * power(base, e - 1);
}

