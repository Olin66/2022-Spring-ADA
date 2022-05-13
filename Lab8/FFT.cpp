#include <cstdio>
#include <cmath>
#include <complex>

#define ll long long
#define ld long double

using namespace std;

ll pow(int n);

complex<ld> *fft(complex<ld> *arr, ll len);

int main() {
    int n;
    scanf("%d", &n);
    ll max = pow(n);
    complex<ld> arr[max];
    for (ll i = 0; i < max; i++) {
        ld x;
        scanf("%Lf", &x);
        arr[i] = x;
    }
    complex<ld> *y = fft(arr, max);
    for (ll i = 0; i < max; i++)
        printf("%Lf\n", abs(y[i]));
}

ll pow(int n) {
    if (n == 0) return 1;
    return 2 * pow(n - 1);
}

complex<ld> *fft(complex<ld> *arr, ll len) {
    if (len == 1)
        return arr;
    complex<ld> wn(cos(2 * M_PI / len), sin(2 * M_PI / len));
    complex<ld> w = 1;
    auto *a0 = new complex<ld>[len / 2];
    auto *a1 = new complex<ld>[len / 2];
    for (ll i = 0; i < len / 2; i++) {
        a0[i] = arr[2 * i];
        a1[i] = arr[2 * i + 1];
    }
    complex<ld> *y0 = fft(a0, len / 2);
    complex<ld> *y1 = fft(a1, len / 2);
    auto *y = new complex<ld>[len];
    for (ll i = 0; i < len / 2; i++) {
        y[i] = y0[i] + w * y1[i];
        y[i + len / 2] = y0[i] - w * y1[i];
        w = w * wn;
    }
    delete[] a0;
    delete[] a1;
    return y;
}