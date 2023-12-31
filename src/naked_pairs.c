#include "naked_pairs.h"
#include <stdio.h>
#include <stdlib.h>

int naked_pairs(SudokuBoard *p_board) {
    pairs_board cell_array[100];
    int num_cell_array, n;
    n = num_pairs_cell(p_board, cell_array, &num_cell_array);
    naked_pair_processing(p_board, cell_array, num_cell_array);  
    return num_cell_array;
}

int pair_two_cells(SudokuBoard *p_board, int row1, int col1, int row2, int col2, int *cell_array1, int *cell_array2) {
    int count = 0;
    int cell_array[2];
    if ((p_board->data[row1][col1].num_candidates == 2) && (p_board->data[row2][col2].num_candidates == 2)) {
        if ((row1 == row2) || (col1 == col2) || (p_board->data[row1][col1].box_index == p_board->data[row2][col2].box_index)) {
            for (int i = 0; i < 9; i++)
                if ((p_board->data[row1][col1].candidates[i] == 1) && (p_board->data[row2][col2].candidates[i] == 1)) {
                    cell_array[count] = i;
                    count++;
                }
        }
    }
    *cell_array1 = cell_array[0];
    *cell_array2 = cell_array[1];
    return count;
}

int num_pairs_cell(SudokuBoard *p_board, pairs_board cell_array[], int *num_cell_array) {
    int cell_array1 = -1;
    int cell_array2 = -1;
    int count = 0;
    for (int i = 0; i < 80; i++)
        for (int j = i + 1; j < 81; j++) {
            int row1 = i / 9;  
            int col1 = i % 9; 
            int row2 = j / 9;  
            int col2 = j % 9;
            if (pair_two_cells(p_board, row1, col1, row2, col2, &cell_array1, &cell_array2) == 2) {
                count++;
                cell_array[count].row1 = row1;
                cell_array[count].col1 = col1;
                cell_array[count].row2 = row2;
                cell_array[count].col2 = col2;
                cell_array[count].cell_array1 = cell_array1;
                cell_array[count].cell_array2 = cell_array2;
            }     
        }
    *num_cell_array = count;
    return count;
}

void naked_pair_processing(SudokuBoard *p_board, pairs_board cell_array[], int num_cell_array)
{
    int row1, col1, row2, col2;
    int cell_array1, cell_array2;
    int row1_begin, col1_begin;
    for (int i = 1; i <= num_cell_array; i++) {
        row1 = cell_array[i].row1;
        col1 = cell_array[i].col1;
        row2 = cell_array[i].row2; 
        col2 = cell_array[i].col2;
        cell_array1 = cell_array[i].cell_array1; 
        cell_array2 = cell_array[i].cell_array2;
        row1_begin = (row1 / 3) * 3; 
        col1_begin = (col1 / 3) * 3;
        if (row1 == row2) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if ((j != col1) && (j != col2)) {
                    if (p_board->data[row1][j].candidates[cell_array1] == 1) {
                        p_board->data[row1][j].candidates[cell_array1] = 0;
                        p_board->data[row1][j].num_candidates--;
                    }
                    if (p_board->data[row1][j].candidates[cell_array2] == 1) {
                        p_board->data[row1][j].candidates[cell_array2] = 0;
                        p_board->data[row1][j].num_candidates--;
                    }
                }
            }
        }
        if (col1 == col2) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if ((j != row1) && (j != row2)) {
                    if (p_board->data[j][col1].candidates[cell_array1] == 1) {
                        p_board->data[j][col1].candidates[cell_array1] = 0;
                        p_board->data[j][col1].num_candidates--;
                    }
                    if (p_board->data[j][col2].candidates[cell_array2] == 1) {
                        p_board->data[j][col2].candidates[cell_array2] = 0;
                        p_board->data[j][col2].num_candidates--;
                    }
                }
            }
        }
        if (p_board->data[row1][col1].box_index == p_board->data[row2][col2].box_index) {
            for (int j = row1_begin; j < row1_begin + 3; j++)
                for (int k = col1_begin; k < col1_begin + 3; k++) {
                    if (((j != row1) || (k != col1)) && ((j != row2) || (k != col2))) {
                        if (p_board->data[j][k].candidates[cell_array1] == 1) {
                            p_board->data[j][k].candidates[cell_array1] = 0;
                            p_board->data[j][k].num_candidates--;
                        }
                        if (p_board->data[j][k].candidates[cell_array2] == 1) {
                            p_board->data[j][k].candidates[cell_array2] = 0;
                            p_board->data[j][k].num_candidates--;
                        }
                    }
                }
        }
    }
}
