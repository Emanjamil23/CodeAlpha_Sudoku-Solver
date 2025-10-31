#include <iostream>
#include <graphics.h>
using namespace std;

int grid[9][9] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

// Function to draw the Sudoku grid
void drawGrid() {
    int left = 100, top = 100, size = 40;
    setcolor(WHITE);
    for (int i = 0; i <= 9; i++) {
        if (i % 3 == 0) setlinestyle(SOLID_LINE, 0, 3);
        else setlinestyle(SOLID_LINE, 0, 1);
        line(left, top + i * size, left + 9 * size, top + i * size);
        line(left + i * size, top, left + i * size, top + 9 * size);
    }
}

// Function to display the numbers in the grid
void displayNumbers() {
    int left = 100, top = 100, size = 40;
    settextstyle(DEFAULT_FONT, 0, 2);
    setcolor(WHITE);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] != 0) {
                char num[2];
                sprintf(num, "%d", grid[i][j]);
                outtextxy(left + j * size + 15, top + i * size + 10, num);
            }
        }
    }
}

// Function to check if placing a number is valid
bool isValid(int row, int col, int num) {
    for (int x = 0; x < 9; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Backtracking Sudoku solver
bool solveSudoku(int row, int col) {
    if (row == 9)
        return true;

    int nextRow = (col == 8) ? row + 1 : row;
    int nextCol = (col + 1) % 9;

    if (grid[row][col] != 0)
        return solveSudoku(nextRow, nextCol);

    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(nextRow, nextCol))
                return true;
            grid[row][col] = 0; // backtrack
        }
    }
    return false;
}

// MAIN FUNCTION
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char*>("")); // ? Fixed conversion warning

    setbkcolor(BLACK);
    cleardevice();

    settextstyle(DEFAULT_FONT, 0, 2);
    setcolor(WHITE);
    outtextxy(180, 50, "Solving Sudoku...");
    drawGrid();
    displayNumbers();

    delay(1000);

    if (solveSudoku(0, 0)) {
        cleardevice();
        drawGrid();
        displayNumbers();
        settextstyle(DEFAULT_FONT, 0, 2);
        setcolor(LIGHTGREEN);
        outtextxy(180, 500, "? Sudoku Solved Successfully!");
    } else {
        setcolor(RED);
        outtextxy(180, 500, "? No solution exists!");
    }

    getch();
    closegraph();
    
}

