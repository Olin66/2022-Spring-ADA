#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long
const int maxn = 50005;
const ll inf = (ll) 5e13;
struct Node {
    int no;
    ll d = inf;

    bool operator<(const Node &o) const {
        return d > o.d;
    }
};

struct Edge {
    int no;
    int to;
    ll w;
};

int n, m, p;
vector<Edge> graph[maxn];
priority_queue<Node> pq;
queue<int> q;
Node nodes[maxn];
bool flags[maxn] = {false};
bool visited[maxn] = {false};
ll dis[maxn] = {0};
int ans[maxn];

void init(int x) {
    for (int i = 1; i <= n; ++i) {
        dis[i] = inf;
        flags[i] = false;
        visited[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        nodes[i].no = i;
        if (i != x)
            nodes[i].d = (ll) inf;
        else
            nodes[i].d = 0;
    }
}

void dijkstra(int x, int y) {
    init(x);
    dis[x] = 0;
    pq.push(nodes[x]);
    while (!pq.empty()) {
        Node u = pq.top();
        pq.pop();
        int no = u.no;
        if (flags[no])
            continue;
        if (u.d == inf)
            break;
        flags[no] = true;
        for (int i = 0; i < graph[no].size(); i++) {
            Edge e = graph[no][i];
            int to = e.to;
            ll w = e.w;
            if (dis[to] > dis[no] + w) {
                dis[to] = dis[no] + w;
                Node node;
                node.no = to;
                node.d = dis[to];
                nodes[to].d = dis[to];
                pq.push(node);
            }
        }
    }
    q.push(y);
    visited[y] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < graph[u].size(); i++) {
            Edge e = graph[u][i];
            int v = e.to;
            if (dis[v] + e.w == dis[u]) {
                ans[e.no]++;
                if(!visited[v]) q.push(v);
                visited[v] = true;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        ll w;
        scanf("%d %d %lld", &x, &y, &w);
        Edge e1 = {i, y, w};
        Edge e2 = {i, x, w};
        graph[x].push_back(e1);
        graph[y].push_back(e2);
    }
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        dijkstra(x, y);
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
}