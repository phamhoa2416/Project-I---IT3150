def generateSequence(size, sequence):
    length = len(sequence)
    
    if length == size:
        print(sequence)
        return
    
    if length == 0 or sequence[length - 1] == '0':
        generateSequence(size, sequence + '0')
        generateSequence(size, sequence + '1')
    else:
        generateSequence(size, sequence + '0')

size = int(input())
generateSequence(size, '')
