#include <cstdio>
#include <vector>

using namespace std;
#define MIN(A, B) ( (A) > (B) ? (B) : (A) )

int arr[1000];
vector<vector<int>> mat(1005, vector<int>(1005));

int opt(int, int);

int main() {
    int n;
    scanf("%d", &n);
    int temp;
    int cur = 1;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x != temp) {
            arr[cur++] = x;
            temp = x;
        }
    }
    printf("%d\n", opt(1, --cur));
}

int opt(int i, int j) {
    if (mat[i][j] != 0) return mat[i][j];
    if (i == j) return 0;
    if (arr[i] == arr[j]) mat[i][j] = opt(i + 1, j - 1) + 1;
    else mat[i][j] = MIN(opt(i + 1, j) + 1, opt(i, j - 1) + 1);
    return mat[i][j];
}