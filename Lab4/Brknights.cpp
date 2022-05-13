#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>

#define ll long long
#define ld long double
#define maxn 100005

using namespace std;

const ll modulo = (ll) (1e9 + 7);
const ll top = (ll) 1e9;

struct Node {
    ll ce = 0;
    ll modce = 0;
    ld logce = 0;
};

vector<int> graph[maxn];
vector<Node> result;
int degree[maxn];
ll level[maxn];
ll arr1[maxn];
ll arr2[maxn];
ll arr3[maxn];
static Node nodes[maxn];

void topo() {
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        Node e = nodes[i];
        if (e.logce >= logl(level[i])) {
            if (e.logce >= logl(top)) {
                e.logce = e.logce + logl(arr2[i]);
                e.modce = e.modce * arr2[i] % modulo;
            } else {
                ll temp = (e.ce + arr1[i]) > (e.ce * arr2[i]) ? (e.ce + arr1[i]) : (e.ce * arr2[i]);
                temp = temp > arr3[i] ? temp : arr3[i];
                e.ce = temp;
                e.modce = temp % modulo;
                e.logce = logl(temp);
            }
            if (graph[i].empty()) result.push_back(e);
            for (int c: graph[i]) {
                degree[c]--;
                if (e.logce > nodes[c].logce) {
                    nodes[c].ce = e.ce;
                    nodes[c].modce = e.modce;
                    nodes[c].logce = e.logce;
                }
                if (degree[c] == 0) q.push(c);
            }
        } else {
            for (int c: graph[i]) degree[c]--;
        }
    }
}

ll findMax() {
    ll num = -1;
    ld max = -1;
    for (Node node: result) {
        if (node.logce > max) {
            max = node.logce;
            num = node.modce;
        }
    }
    return num;
}

int main() {
    int n, m;
    ll c;
    scanf("%d%d%lld", &n, &m, &c);
    for (int i = 1; i <= n; i++) {
        ll num1, num2, num3, num4;
        scanf("%lld%lld%lld%lld", &num1, &num2, &num3, &num4);
        level[i] = num1;
        arr1[i] = num2;
        arr2[i] = num3;
        arr3[i] = num4;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        graph[x].push_back(y);
        degree[y]++;
    }
    nodes[1].ce = c;
    nodes[1].modce = c;
    nodes[1].logce = logl(c);
    topo();
    printf("%lld\n", findMax());
}