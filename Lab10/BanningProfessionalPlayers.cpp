#include <cstdio>

using namespace std;
#define ll long long

const int maxn = 5005;
const ll modulo = (ll) (1e9 + 7);

int cnt[maxn];

int main() {
    int n, l, r, sum = 0, max = 0;
    scanf("%d %d %d", &n, &l, &r);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        max = max > x ? max : x;
        cnt[x]++;
        sum += x;
    }
    int down = (sum - r) > l ? sum - r : l;
    int top = (sum - l) > r ? r : sum - l;
    ll opt[top + 1];
    ll temp[top + 1];
    temp[0] = 1;
    for (int i = 1; i <= top; ++i) temp[i] = 0;
    int num = 1;
    while (num <= max) {
        for (int i = 0; i <= top; i++) {
            opt[i] = temp[i];
            if (num <= i) {
                for (int j = 1; j <= cnt[num]; j++)
                    if (i - j * num >= 0)
                        opt[i] = (opt[i] + temp[i - j * num]) % modulo;
            }
        }
        num++;
        for (int i = 0; i <= top; i++) temp[i] = opt[i];
    }
    ll ans = 0;
    for (int i = down; i <= top; i++)
        ans = (ans + temp[i]) % modulo;
    printf("%lld\n", ans);
}