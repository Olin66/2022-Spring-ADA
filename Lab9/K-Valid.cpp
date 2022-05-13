#include <cstdio>
#include <vector>

using namespace std;

#define ll long long

const ll modulo = (ll) (1e9 + 7);

vector<vector<ll>> matrix(50, vector<ll>(50));

vector<vector<ll>> multiplication(int, vector<vector<ll>>, vector<vector<ll>>);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m - 1; i++) {
        matrix[i][0] = 1;
        matrix[i][i + 1] = 1;
    }
    matrix[m - 1][0] = 1;
    vector<vector<ll>> ans(m, vector<ll>(m));
    for (int i = 0; i < m; i++)
        ans[i][i] = 1;
    vector<vector<ll>> fac = matrix;
    while (n != 0) {
        if ((n & 1) == 1) ans = multiplication(m, ans, fac);
        fac = multiplication(m, fac, fac);
        n >>= 1;
    }
    ll cnt = 0;
    for (int i = 0; i < m; i++)
        cnt = (cnt + ans[0][i]) % modulo;
    printf("%lld\n", cnt);
}

vector<vector<ll>> multiplication(int m, vector<vector<ll>> mat1, vector<vector<ll>> mat2) {
    vector<vector<ll>> res(m, vector<ll>(m));
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < m; k++) {
            ll s = mat1[i][k];
            for (int j = 0; j < m; j++)
                res[i][j] = (res[i][j] + (s * mat2[k][j] % modulo)) % modulo;
        }
    }
    return res;
}