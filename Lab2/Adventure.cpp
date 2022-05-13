#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define max 500005
#define ll long long

vector<int> graph[max];
bool isVisit[max];
bool inQueue[max];
int dist[max];

int main() {
    int n;
    scanf("%d", &n);
    memset(dist, max, sizeof(dist));
    for (int i = 1; i <= n; i++) {
        if (i != 1)
            graph[i].push_back(i - 1);
        if (i != n)
            graph[i].push_back(i + 1);
        int ai;
        scanf("%d", &ai);
        graph[i].push_back(ai);
    }
    queue<int> q;
    q.push(1);
    ll result = 1;
    inQueue[1] = true;
    dist[1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u].at(i);
            if (!isVisit[v] && !inQueue[v]) {
                inQueue[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        isVisit[u] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (i != n)
            printf("%d ", dist[i]);
        else
            printf("%d\n", dist[i]);
    }
}