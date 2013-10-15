// Problem: Klasyka 2
#include <cstdio>
#include <cstring>
#include <vector>

#define d if(0)

using namespace std;

const int DUZO = 100010;

int text_len, pattern_len;
char text[DUZO];
char pattern[DUZO];
char patterns[26][DUZO];
int count_matches(char* text, int patterns_no);

int main() {
    int t;
    scanf("%d", &t);
    while(t --> 0) {
        int matches = 0;
        scanf("%s %s", text, pattern);
        
        bool in_pattern[26] = {0};
        bool in_text[26] = {0};

        int question_pos = -1;
        text_len = 0;
        pattern_len = 0;
        int pos = 0;
    
        while(text[pos]) {
            in_text[text[pos] - 'a'] = true;
            pos++;
        }
        text_len = pos;

        pos = 0;
        while(pattern[pos]) {
            if(pattern[pos] != '?')
                in_pattern[pattern[pos] - 'a'] = true;
            pos++;
        }
        pattern_len = pos;

        for(int i = 0; i < pattern_len; i++) {
            if(pattern[i] == '?') {
                question_pos = i;
                break;
            }
        }

        if(question_pos == -1) {
            strcpy(patterns[0], pattern);
            matches = count_matches(text, 1);
        } else {
            int cnt = 0;
            for(int i = 0; i < 26; i++) {
                if(!in_text[i])
                    continue;

                strcpy(patterns[cnt], pattern);
                patterns[cnt][question_pos] = 'a' + i;

                cnt++;
            }

            matches += count_matches(text, cnt);
        }

        printf("%d\n", matches);
    }


    return 0;
}

vector<int> compute_pi(char* pattern, int len) {
    vector<int> result;
    result.resize(len);

    int k = 0;
    for(int i = 1; i < len; i++) {
        while(k > 0 && pattern[i] != pattern[k])
            k = result[k - 1];

        if(pattern[i] == pattern[k])
            k++;

        result[i] = k;
    }

    return result;
}

int count_matches(char* text, int patterns_no) {
    vector<vector<int> > pis;
    vector<int> ks;
    for(int i = 0; i < patterns_no; i++) {
        pis.push_back(compute_pi(patterns[i], pattern_len));
        ks.push_back(0);
    }

    int matches = 0;
    for(int i = 0; i < text_len; i++) {
        for(int j = 0; j < patterns_no; j++) {
            if(ks[j] == pattern_len) {
                matches++;
                ks[j] = pis[j][ks[j] - 1];
            }

            while(ks[j] > 0 && text[i] != patterns[j][ks[j]])
                ks[j] = pis[j][ks[j] - 1];

            if(text[i] == patterns[j][ks[j]])
                ks[j]++;
        }
    }

    for(int i = 0; i < patterns_no; i++)
        if(ks[i] == pattern_len)
            matches++;

    return matches;
}


