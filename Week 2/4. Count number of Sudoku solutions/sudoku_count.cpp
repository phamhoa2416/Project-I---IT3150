#include <iostream>

#define N 9
using namespace std;

bool hasEmptyCell(int grid[N][N], int &row, int &col) {  // Pass row and col by reference
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                row = i;  // Update row
                col = j;  // Update col
                return true;
            }
        }
    }
    return false;
}

bool isValid(int grid[N][N], int row, int col, int num) {
    // Check the row
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num) 
            return false;
    }
    
    // Check the col
    for (int i = 0; i < N; ++i) {
        if (grid[i][col] == num) 
            return false;
    }
    
    // Check the 3x3 subgrid
    int startRow = row - row % 3,
        startCol = col - col % 3;
        
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    
    return true;
}

int countSudokuSolutions (int grid[N][N]) {
    int row, col;
    
    if (!hasEmptyCell(grid, row, col)) {
        return 1;  // Solution found
    }
    
    int count = 0;
    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            count += countSudokuSolutions(grid);
            grid[row][col] = 0; // Backtracking
        }
    }
    
    return count;
}

int main() {
    int board[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int num;
            cin >> num;
            board[i][j] = num;
        }
    }
    
    cout << countSudokuSolutions(board);
}
