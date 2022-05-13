#include <cstdio>

using namespace std;

#define ll long long
#define MIN(A, B) ( (A) > (B) ? (B) : (A) )
#define MAX(A, B) ( (A) > (B) ? (A) : (B) )

const ll modulo = (ll) (1e9 + 7);
const int maxn = 2005;

ll val[maxn][maxn];
ll sum[maxn][maxn];
ll pro[maxn][maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int mmax = MAX(n, m);
    int mmin = MIN(n, m);
    int nest = (mmin + 1) / 2;
    for (int i = 1; i <= mmax; i++) {
        val[1][i] = 1;
        sum[1][i] = i;
        pro[1][i] = i + pro[1][i - 1];
    }
    for (int i = 2; i <= mmax; i++) {
        for (int j = 3; j <= mmax; j++) {
            val[i][j] = ((j - 1) * sum[i - 1][j - 2] % modulo - pro[i - 1][j - 2]  + modulo) % modulo;
            sum[i][j] = (val[i][j] + sum[i][j - 1]) % modulo;
            pro[i][j] = (val[i][j] * j % modulo + pro[i][j - 1]) % modulo;
        }
    }
    ll cnt = 0;
    for (int i = 1; i <= nest; i++)
        cnt = (cnt + val[i][n] * val[i][m] % modulo) % modulo;
    printf("%lld\n", cnt);
}