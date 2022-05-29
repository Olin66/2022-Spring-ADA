#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 100005;
vector<int> graph[maxn];
int dis1[maxn];
bool vis1[maxn];
int dis2[maxn];
bool vis2[maxn];

void bfs(int, int);

int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    scanf("%d", &q);
    int ans[q];
    memset(ans, 0, sizeof ans);
    for (int j = 0; j < q; j++) {
        int x, y;
        scanf("%d %d", &x, &y);
        bfs(x, y);
        for (int i = 1; i <= n; i++) {
            if (dis1[i] == dis2[i])
                ans[j]++;
        }
    }
    for (int j = 0; j < q; j++)
        printf("%d\n", ans[j]);
}

void bfs(int x, int y) {
    memset(vis1, false, sizeof(vis1));
    memset(vis2, false, sizeof(vis2));
    queue<int> q;
    q.push(x);
    dis1[x] = 0;
    vis1[x] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (!vis1[v]) {
                vis1[v] = true;
                dis1[v] = dis1[u] + 1;
                q.push(v);
            }
        }
    }
    q.push(y);
    dis2[y] = 0;
    vis2[y] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (!vis2[v]) {
                vis2[v] = true;
                dis2[v] = dis2[u] + 1;
                q.push(v);
            }
        }
    }
}

// 50 points TLE