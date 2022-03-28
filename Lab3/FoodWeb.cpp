#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define ll long long
#define max 100005

using namespace std;

const ll modulo = (ll) (1e9+7);

ll* topo(int* degree, const vector<int> graph[max], const int n){
    queue<int> q;
    ll* number = new ll[max];
    for (int i = 1; i <= n; i++)
    {
        if (degree[i] == 0)
        {
            number[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int e = q.front();
        q.pop();
        for (int i = 0; i < graph[e].size(); i++)
        {
            int c = graph[e].at(i);
            degree[c]--;
            number[c] = (number[c] + number[e]) % modulo;
            if (degree[c] == 0)
                q.push(c);
        }
    }
    return number;   
}


int main(){
    vector<int> pos[max];
    vector<int> neg[max];
    int indegree[max];
    int outdegree[max];
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        pos[x].push_back(y);
        neg[y].push_back(x);
        indegree[y]++;
        outdegree[x]++;
    }
    ll* num1 = topo(indegree, pos, n);
    ll* num2 = topo(outdegree, neg, n);
    ll* result = new ll[max];
    for (int i = 1; i <= n; i++)
    {
        result[i] = (num1[i] * num2[i]) % modulo;
        printf("%lld ", result[i]);
    }
    delete[] num1;
    delete[] num2;
    delete[] result;
}