#include <cstdio>
#include <vector>

using namespace std;

bool can_divide(const vector<int>& arcs, int sum);
int best_polygon(const vector<int>& arcs);

int main() {
    vector<int> arcs;

    while(true) {
        int n;
        scanf("%d", &n);
        if(n == 0)
            break;

        arcs.resize(0);
        for(int i = 0; i < n; i++) {
            int k;
            scanf("%d", &k);
            arcs.push_back(k);
        }

        int max_vertices = best_polygon(arcs);
        printf("%d\n", arcs.size() - max_vertices);
    }

    return 0;
}

bool can_divide(const vector<int>& arcs, int sum) {
    static vector<int> valid_start;
    valid_start.resize(arcs.size());

    int segments = arcs.size() / sum;

    int current = 0;
    int stop_at = 0;
    int current_sum = 0;

    while(current < arcs.size()) {
        while(current_sum < sum) {
            current_sum += arcs[stop_at];
            stop_at++;
            
            if(stop_at >= arcs.size())
                stop_at -= arcs.size();
        }

        if(current_sum > sum) {
            valid_start[current] = -1;
        } else {
            valid_start[current] = stop_at;
        }

        current_sum -= arcs[current];
        current++;

        if(current_sum > sum) {
            stop_at--;
            current_sum -= arcs[stop_at];
        }

        if(stop_at < 0)
            stop_at += arcs.size();
    }

    vector<int> visited;
    visited.resize(arcs.size());

    for(int i = 0; i < arcs.size(); i++) {
        if(visited[i])
            continue;

        int current = valid_start[i];
        while(current != -1 && current != i) {
            visited[current] = true;
            current = valid_start[current];
        }

        if(current != -1)
            return true;
    }

    return false;
}

int best_polygon(const vector<int>& arcs) {
    int sum = 0;
    for(int i = 0; i < arcs.size(); i++)
        sum += arcs[i];

    int best = arcs.size() + 1;
    for(int vertices = arcs.size(); vertices >= 3; vertices--) {
        if(sum % vertices != 0)
            continue;


        if(can_divide(arcs, sum / vertices)) {
            best = vertices;
            break;
        }
    }

    return best;
}

