n, k = map(int, input().split())
sequence = list(map(int, input().split()))

prefix_sum = [0] * (n + 1)
count = 0

for i in range(n):
    prefix_sum[i + 1] = prefix_sum[i] + sequence[i]
    
for i in range(0, n - k + 1):
    if ((prefix_sum[i + k] - prefix_sum[i]) % 2 == 0):
        count += 1

print(count)
