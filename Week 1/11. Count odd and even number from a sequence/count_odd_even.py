number = int(input())
sequence = list(map(int, input().split()));

odd_count = 0;
even_count = 0;

for num in sequence:
    if num % 2 == 0:
        even_count += 1
    else:
        odd_count += 1
        
print(odd_count, even_count)
