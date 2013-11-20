#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <map>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

struct course_cmp {
    bool operator()(const string& a, const string& b) {
        int matches_to = 0;

        while(matches_to < min(a.length(), b.length()) && a[matches_to] == b[matches_to])
            matches_to++;

        if(matches_to < min(a.length(), b.length()))
            return a[matches_to] < b[matches_to];

        return a.length() < b.length();
    }
};

typedef set<string, course_cmp> courses_set;
map<string, courses_set> requests;

int main() {
    int n;

    cin >> n;
    for(int i = 0; i < n; i++) {
        string first, last, course;
        cin >> first >> last >> course;

        requests[course].insert(first + last);
    }

    for(map<string, courses_set>::iterator it = requests.begin(); it != requests.end(); it++) {
        cout << it->first << " " << it->second.size() << endl;
    }

    return 0;
}

