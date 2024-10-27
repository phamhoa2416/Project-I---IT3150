N = 9

def findEmptyCell(grid):
    for i in range(N):
        for j in range(N):
            if grid[i][j] == 0:
                return (i, j)
                
    return None
    
def is_valid(grid, row, col, num):
    for i in range(N):
        if grid[row][i] == num:
            return False
            
        if grid[i][col] == num:
            return False
            
        startRow, startCol = row - row % 3, col - col % 3
        for i in range(3):
            for j in range(3):
                if (grid[i + startRow][j + startCol] == num):
                    return False
                    
    return True
    
def count_sudoku_solution(grid):
    empty_cell = findEmptyCell(grid)
    
    if not empty_cell:
        return 1
        
    row, col = empty_cell
    count = 0
    
    for num in range(1, 10):
        if is_valid(grid, row, col, num):
            grid[row][col] = num
            count += count_sudoku_solution(grid)
            grid[row][col] = 0 
    
    return count 
    
board = []
for _ in range(N):
    row = list(map(int, input(). split()))
    board.append(row)
    
print(count_sudoku_solution(board))
    
                    
