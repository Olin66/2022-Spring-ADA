#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define max 500005
#define modulo 998244353
#define ll long long

vector <int> graph[max] ;
bool isVisit[max];
bool inQueue[max];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n-1; i++){
        int x,y;
        scanf("%d%d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    queue <int> q;
    q.push(1);
    ll result = 1;
    while (!q.empty()){
        int e = q.front();
        q.pop();
        isVisit[e] = true;
        ll count = 0;
        for (int i = 0; i < graph[e].size(); i++){
            int child = graph[e].at(i);
            if (!isVisit[child] && !inQueue[child]){
                inQueue[child] = true;
                q.push(child);
                count++;
                result = result * count % modulo;
            }
        }
    }
    printf("%lld\n", result);
}