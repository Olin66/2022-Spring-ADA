#include <cstdio>
#include <vector>

using namespace std;

#define ll long long
#define MAX(A, B) ( (A) > (B) ? (A) : (B) )

int n;
const int maxn = 300005;

vector<int> graph[maxn];
vector<int> tempgraph[maxn];
vector<ll> weight[maxn];
vector<ll> tempweight[maxn];
bool flags[maxn];
ll opt0[maxn];
ll opt1[maxn];

void dfs(int u);

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        ll w;
        scanf("%d %d %lld", &x, &y, &w);
        graph[x].push_back(y);
        graph[y].push_back(x);
        weight[x].push_back(w);
        weight[y].push_back(w);
    }
    for (int i = 1; i <= n; i++)
        flags[i] = true;
    ll temp = 0;
    for (int i = 1; i <= n; i++) {
        if (flags[i]) {
            dfs(i);
            temp += opt1[i];
        }
    }
    printf("%lld", temp);
}

void dfs(int u) {
    ll sum = 0;
    flags[u] = false;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u].at(i);
        if (flags[v]) {
            dfs(v);
            sum += opt1[v];
            tempgraph[u].push_back(v);
            ll w = weight[u].at(i);
            tempweight[u].push_back(w);
        }
    }
    opt0[u] = sum;
    ll mmax = sum;
    for (int i = 0; i < tempgraph[u].size(); i++) {
        int v = tempgraph[u].at(i);
        ll w = tempweight[u].at(i);
        ll maxtemp = w + sum - opt1[v] + opt0[v];
        mmax = MAX(mmax, maxtemp);
    }
    opt1[u] = mmax;
}