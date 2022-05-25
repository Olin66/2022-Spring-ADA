#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long

int n, m;
const int maxn = 1050000;
const ll modulo = (ll) (1e9 + 7);

vector<int> graph[25];
ll result[maxn];

int main() {
    scanf("%d %d", &n, &m);
    int cnt = (1 << n);
    for (int i = 0; i < cnt; i++) {
        result[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[v].push_back(u);
    }
    result[0] = 1;
    int num[n];
    for (int i = 0; i < cnt - 1; ++i) {
        memset(num, 0, sizeof(num));
        for (int j = 0; j < n; ++j) {
            if (((i >> j) & 1) == 1) {
                for (int v: graph[j + 1]) {
                    num[v - 1]++;
                }
            }
        }
        for (int j = 0; j < n; ++j) {
            int index = i | (1 << j);
            if (index != i)
                result[index] = (result[index] + (1 << num[j]) * result[i] % modulo) % modulo;
        }
    }
    printf("%lld\n", result[cnt - 1]);
}
