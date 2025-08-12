#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int dfs(int i, int j, int prev, int** matrix, int m, int n, int memo[m][n]) {
    if (i < 0 || i >= m || j < 0 || j >= n || matrix[i][j] <= prev) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    int len = 1;

    len = fmax(len, 1 + dfs(i + 1, j, matrix[i][j], matrix, m, n, memo));
    len = fmax(len, 1 + dfs(i - 1, j, matrix[i][j], matrix, m, n, memo));
    len = fmax(len, 1 + dfs(i, j + 1, matrix[i][j], matrix, m, n, memo));
    len = fmax(len, 1 + dfs(i, j - 1, matrix[i][j], matrix, m, n, memo));

    memo[i][j] = len;

    return len;
}

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    if (!matrixSize || !matrixColSize[0]) return 0;

    int m = matrixSize, n = matrixColSize[0];
    int maxLen = 0;
    int memo[m][n];

    memset(memo, -1, sizeof(memo));
    
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) maxLen = fmax(maxLen, dfs(i, j, INT_MIN, matrix, m, n, memo));
    
    return maxLen;
}

const int main(void) {
    int m, n;
    scanf("%d %d", &m, &n);

    int** matrix = (int**)malloc(m * sizeof(int*));
    int* matrixColSize = (int*)malloc(sizeof(int));

    matrixColSize[0] = n;
    
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) scanf("%d", &matrix[i][j]);
    }
    
    int result = longestIncreasingPath(matrix, m, matrixColSize);
    printf("%d\n", result);
    
    for (int i = 0; i < m; i++) free(matrix[i]);
    
    free(matrix);
    free(matrixColSize);

    return 0;

}
