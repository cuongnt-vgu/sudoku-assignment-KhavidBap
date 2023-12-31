#include "hidden_pairs.h"
#include <stdio.h>
#include <stdlib.h>

int hidden_pairs(SudokuBoard *p_board) {
    int num_hidden_pairs = 0;   
    pairs_board cell_array[100];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            one_cell(p_board, i, j, &num_hidden_pairs, cell_array);
    hidden_pairs_process(p_board, cell_array, num_hidden_pairs);
    return num_hidden_pairs;
}

void one_cell(SudokuBoard *p_board, int row, int col, int *num_hidden_pairs, pairs_board cell_array[]) {
    if (p_board->data[row][col].num_candidates > 1) {
        int n = -1;
        for (int i = 0; i < 8; i++)
            for (int j = i + 1; j < 9; j++)
                if ((p_board->data[row][col].candidates[i] != 0) && (p_board->data[row][col].candidates[j] != 0)) {
                    n = one_cell_row(p_board, row, col, i, j);
                    if ((n > -1) && (n > col)) {
                        *num_hidden_pairs = *num_hidden_pairs + 1;
                        cell_array[*num_hidden_pairs].row1 = row; 
                        cell_array[*num_hidden_pairs].col1 = col;
                        cell_array[*num_hidden_pairs].row2 = row; 
                        cell_array[*num_hidden_pairs].col2 = n;
                        cell_array[*num_hidden_pairs].cell_array1 = i; 
                        cell_array[*num_hidden_pairs].cell_array2 = j;
                    }
                    if (n == -1)
                        n = one_cell_col(p_board, row, col, i, j);
                    if ((n > -1) && (n > row)) {
                        *num_hidden_pairs = *num_hidden_pairs + 1;
                        cell_array[*num_hidden_pairs].row1 = row; 
                        cell_array[*num_hidden_pairs].col1 = col;
                        cell_array[*num_hidden_pairs].row2 = n; 
                        cell_array[*num_hidden_pairs].col2 = col;
                        cell_array[*num_hidden_pairs].cell_array1 = i; 
                        cell_array[*num_hidden_pairs].cell_array2 = j;
                    }
                    if (n == -1)    
                        n = one_cell_box(p_board, row, col, i, j);
                    if ((n > -1) && (n > (row * 9 + col))) {
                        *num_hidden_pairs = *num_hidden_pairs + 1;
                        cell_array[*num_hidden_pairs].row1 = row; 
                        cell_array[*num_hidden_pairs].col1 = col;
                        cell_array[*num_hidden_pairs].row2 = n / 9; 
                        cell_array[*num_hidden_pairs].col2 = n % 9;
                        cell_array[*num_hidden_pairs].cell_array1 = i; 
                        cell_array[*num_hidden_pairs].cell_array2 = j;
                    }
                }
    }
}

int one_cell_row(SudokuBoard *p_board, int row, int col, int i, int j) {
    int num_hidden_pairs = 0;
    int num_col = -1;
    for (int n = 0; n < 9; n++)
        if (n != col) {
            if ((p_board->data[row][n].num_candidates > 2) || (p_board->data[row][col].num_candidates > 2)) {
                if ((p_board->data[row][n].candidates[i] != 0) && (p_board->data[row][n].candidates[j] != 0)) {
                    num_hidden_pairs++;
                    num_col = n;
                    if (num_hidden_pairs == 2)
                        return -1;
                } else if ((p_board->data[row][n].candidates[i] != 0) || (p_board->data[row][n].candidates[j] != 0))
                    return -1;
            }
        }
    return num_col;
}

int  one_cell_col(SudokuBoard *p_board, int row, int col, int i, int j) {
    int num_hidden_pairs = 0;
    int num_row = -1;
    for (int n = 0; n < 9; n++)
        if (n != row) {
            if ((p_board->data[n][col].num_candidates > 2) || (p_board->data[row][col].num_candidates > 2)) {
                if ((p_board->data[n][col].candidates[i] != 0) && (p_board->data[n][col].candidates[j] != 0)) {
                    num_hidden_pairs++;
                    num_row = n;
                    if (num_hidden_pairs == 2)
                        return -1;
                } else if ((p_board->data[n][col].candidates[i] != 0) || (p_board->data[n][col].candidates[j] != 0))
                    return -1;
            }
        }
    return num_row;
}

int  one_cell_box(SudokuBoard *p_board, int row, int col, int i, int j) {
    int row_box = (row / 3) * 3;
    int col_box = (col / 3) * 3;
    int num_hidden_pairs = 0;
    int n = -1;
    for (int num_row = row_box; num_row < row_box + 3; num_row++)
        for(int num_col = col_box; num_col < col_box + 3; num_col++)
            if ((num_row != row) || (num_col !=col)) { 
                if ((p_board->data[num_row][num_col].num_candidates > 2) || (p_board->data[row][col].num_candidates > 2)) {
                    if ((p_board->data[num_row][num_col].candidates[i] != 0) && (p_board->data[num_row][num_col].candidates[j] != 0)) {
                        num_hidden_pairs++;
                        n = num_row * 9 + num_col;
                        if (num_hidden_pairs == 2)
                            return -1;
                    } else if ((p_board->data[num_row][num_col].candidates[i] != 0) || (p_board->data[num_row][num_col].candidates[j] != 0)) 
                        return -1;
                }
            }
    return n;
}

void hidden_pairs_process(SudokuBoard *p_board, pairs_board cell_array[], int num_cell_array) {
    for (int i = 1; i <= num_cell_array; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((j != cell_array[i].cell_array1) && (j != cell_array[i].cell_array2)) {
                if (p_board->data[cell_array[i].row1][cell_array[i].col1].candidates[j] == 1) {
                    p_board->data[cell_array[i].row1][cell_array[i].col1].candidates[j] = 0;
                    p_board->data[cell_array[i].row1][cell_array[i].col1].num_candidates--;
                }
                if (p_board->data[cell_array[i].row2][cell_array[i].col2].candidates[j] == 1) {
                    p_board->data[cell_array[i].row2][cell_array[i].col2].candidates[j] = 0;
                    p_board->data[cell_array[i].row2][cell_array[i].col2].num_candidates--;
                }
            }
        }
    }
}