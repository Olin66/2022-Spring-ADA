#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long
#define MIN(A, B) ( (A) > (B) ? (B) : (A) )

const int maxn = 105;
const ll inf = (ll) 1e12;

int n, m, s, t;

struct Edge {
    int from, to;
    ll flow;

    Edge(int u, int v, ll f) : from(u), to(v), flow(f) {}
};

vector<Edge> edges;
vector<int> graph[maxn];

bool vis[maxn];
int dis[maxn];
int cur[maxn];

void addEdge(int, int, ll);

bool bfs();

ll dfs(int, ll);

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 0; i < m; i++) {
        int x, y;
        ll cap;
        scanf("%d %d %lld", &x, &y, &cap);
        addEdge(x, y, cap);
    }
    ll flow = 0;
    memset(cur, 0, sizeof(cur));
    while (bfs()) flow += dfs(s, inf);
    printf("%lld\n", flow);
}

void addEdge(int u, int v, ll cap) {
    edges.push_back(Edge(u, v, cap));
    edges.push_back(Edge(v, u, 0));
    int m = edges.size();
    graph[u].push_back(m - 2);
    graph[v].push_back(m - 1);
}

bool bfs() {
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    vis[s] = true;
    cur[s] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = cur[x]; i < graph[x].size(); i++) {
            Edge &e = edges[graph[x][i]];
            if (!vis[e.to] && e.flow > 0) {
                vis[e.to] = true;
                dis[e.to] = dis[x] + 1;
                cur[e.to] = 0;
                if (e.to == t) return true;
                q.push(e.to);
            }
        }
    }
    return vis[t];
}

ll dfs(int x, ll limit) {
    if (x == t || limit == 0) return limit;
    ll flow = 0;
    for (int i = cur[x]; i < graph[x].size(); i++) {
        cur[x] = i;
        Edge &e = edges[graph[x][i]];
        if (dis[x] + 1 == dis[e.to] && e.flow) {
            int minf = dfs(e.to, MIN(e.flow, limit - flow));
            e.flow -= minf;
            edges[graph[x][i] ^ 1].flow += minf;
            flow += minf;
            if (flow == limit) return flow;
        }
    }
    return flow;
}