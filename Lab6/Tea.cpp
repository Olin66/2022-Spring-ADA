#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    if (n > 12) return 0;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) {
        printf("1 %d\n", i);
        printf("%d ", (n - 1));
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            else
                printf("%d ", j);
        }
        printf("\n");
    }
    return 0;
}

// 50 points WA