def generate_permutation(permutation, elements, positions):
    if (len(permutation) == len(elements)):
        for it in permutation:
            print(it, end = ' ')
        print()
    else:
        for i in range(len(elements)):
            if (positions[i]):
                continue
            
            positions[i] = True
            permutation.append(elements[i])
            
            generate_permutation(permutation, elements, positions)
            permutation.pop()
            positions[i] = False
            
elements = []
permutation = []
size = int(input())

for i in range(0, size):
    elements.append(i + 1)
    
positions = [False] * int(size)
generate_permutation(permutation, elements, positions)
