#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int ll;
int n, q, k;

struct Node {
    vector<ll> mini;
    vector<ll> maxi;

    Node(ll a = -1) {
        if(a != -1) {
            mini.push_back(a);
            maxi.push_back(a);
        }
    }

    Node(const Node& a, const Node& b) {
        mini.resize(a.mini.size() + b.mini.size());
        merge(a.mini.begin(), a.mini.end(),
              b.mini.begin(), b.mini.end(), mini.begin());

        maxi.resize(a.maxi.size() + b.maxi.size());
        merge(a.maxi.rbegin(), a.maxi.rend(),
              b.maxi.rbegin(), b.maxi.rend(), maxi.begin());

        reverse(maxi.begin(), maxi.end());

        if(mini.size() > k)
            mini.resize(k);

        if(maxi.size() > k)
            maxi.resize(k);
    }

    ll diff() const {
        ll suma = 0;
        for(int i = 0; i < maxi.size(); i++)
            suma += maxi[i];

        for(int i = 0; i < mini.size(); i++)
            suma -= mini[i];

        return suma;
    }
};

const int DUZO = (1 << 19);
Node tree[2 * DUZO];

ll query(int a, int b) {
    int left = DUZO + a;
    int right = DUZO + b;

    Node result;
    while(left < right) {
        if(left % 2 == 1) {
            result = Node(result, tree[left]);
            left /= 2;
            left++;
        } else {
            left /= 2;
        }

        if(right % 2 == 0) {
            result = Node(result, tree[right]);
            right /= 2;
            right--;
        } else {
            right /= 2;
        }
    }

    if(left == right) {
        result = Node(result, tree[left]);
    }

    return result.diff();
}

int main() {
    scanf("%d %d %d", &n, &k, &q);

    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        tree[DUZO + i] = Node(x);
    }

    for(int i = DUZO - 1; i >= 1; i--) {
        tree[i] = Node(tree[2*i], tree[2*i+1]);
    }

    for(int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%lld\n", query(a - 1, b - 1));
    }

    return 0;
}

