#include <stdio.h>

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Check if it's safe to place num in grid[row][col]
int isSafe(int grid[N][N], int row, int col, int num) {
    for(int x = 0; x < N; x++) {
        if(grid[row][x] == num || grid[x][col] == num)
            return 0;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(grid[startRow + i][startCol + j] == num)
                return 0;

    return 1;
}

// Solve Sudoku using backtracking
int solveSudoku(int grid[N][N]) {
    int row, col;
    int emptyFound = 0;

    // Find an empty cell
    for(row = 0; row < N; row++) {
        for(col = 0; col < N; col++) {
            if(grid[row][col] == 0) {
                emptyFound = 1;
                goto found;
            }
        }
    }

found:
    if(!emptyFound)
        return 1; // solved

    for(int num = 1; num <= 9; num++) {
        if(isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if(solveSudoku(grid))
                return 1;

            grid[row][col] = 0; // backtrack
        }
    }

    return 0; // trigger backtracking
}

// Main function with dynamic input
int main() {
    int grid[N][N];

    printf("Enter Sudoku Puzzle (use 0 for empty cells):\n");

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(scanf("%d", &grid[i][j]) != 1) {
                printf("Invalid input! Please enter numbers 0-9.\n");
                return 1;
            }
        }
    }

    if(solveSudoku(grid)) {
        printf("\nSolved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("\nNo solution exists.\n");
    }

    printf("\nPress Enter to exit...");
    getchar(); // consume newline
    getchar(); // wait for Enter
    return 0;
}