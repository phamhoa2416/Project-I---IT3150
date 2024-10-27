def generateBinarySequence(size, sequence, index):
    if (index == size):
        print(''.join(map(str, sequence)))
        return
    
    sequence[index] = 0
    generateBinarySequence(size, sequence, index + 1)
    
    sequence[index] = 1 
    generateBinarySequence(size, sequence, index + 1)
    
size = int(input())
sequence = [0] * size
generateBinarySequence(size, sequence, 0)
