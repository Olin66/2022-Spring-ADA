#include <cstdio>
#include <vector>

using namespace std;

#define ll long long

vector<ll> v;

ll pow(int);

int main() {
    pow(62);
    ll n;
    scanf("%lld", &n);
    int len = -1;
    for (int i = 0; i < 63; i++) {
        if (n >= v.at(i))
            len++;
        else break;
    }
    while (len >= 0) {
        if (n >= v.at(len)) {
            printf("1");
            n = v.at(len + 1) - 1 - n;
        } else
            printf("0");
        len--;
    }
    printf("\n");
}

ll pow(int n) {
    if (n == 0) {
        v.push_back(1);
        return 1;
    }
    ll temp = 2 * pow(n - 1);
    v.push_back(temp);
    return temp;
}