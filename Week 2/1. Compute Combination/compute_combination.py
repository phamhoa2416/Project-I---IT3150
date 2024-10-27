MOD = 10**9 + 7

def compute_combination(k, n):
    result = [[0 for _ in range(k + 1)] for _ in range(n + 1)]
    for i in range(n + 1):
        for j in range(min(i, k) + 1):
            if j == 0 or j == i:
                result[i][j] = 1 
            else:
                result[i][j] =  (result[i - 1][j - 1] + result[i - 1][j]) % MOD
    return result[n][k]
    
k, n = map(int, input().split())
print(compute_combination(k, n))
