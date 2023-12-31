#include "hidden_triples.h"
#include <stdio.h>
#include <stdlib.h>

int hidden_triples(SudokuBoard *p_board) {
    triples_board cell_array[100];
    int num_cell_array, n;
    n = num_three_cells(p_board, cell_array, &num_cell_array);
    hidden_triples_processing(p_board, cell_array, &num_cell_array); 
    return num_cell_array;
}

int pair_three_cell(SudokuBoard *p_board, int row1, int col1, int row2, int col2, int row3, int col3, int *cell_array1, int *cell_array2, int *cell_array3) {
    int count = 0; 
    int count1 = 0;
    int num_cell_array = 0;
    int cell_array[4];
    int num_cell_array1 = p_board->data[row1][col1].num_candidates;
    int num_cell_array2 = p_board->data[row2][col2].num_candidates;
    int num_cell_array3 = p_board->data[row3][col3].num_candidates;
    bool ins, outs;
    int rd1 = (row1 / 3) * 3;
    int cd1 = (col1 / 3) * 3;
    int rd2 = (row2 / 3) * 3;
    int cd2 = (col2 / 3) * 3; 
    int rd3 = (row3 / 3) * 3;
    int cd3 = (col3 / 3) * 3;

    if ((num_cell_array1 == 1) || (num_cell_array2 == 1) || (num_cell_array3 == 1))
        return 0;

    if ((row1 == row2) && (row2 == row3)) {    
        for (int i = 0; i < 9; i++) {
            ins = false;
            outs = false;
            for (int j = 0; j < 9; j++) {
                num_cell_array= p_board->data[row1][j].num_candidates;
                if ((j != col1) && (j != col2) && (j != col3)) {
                    if (p_board->data[row1][j].candidates[i] == 1)
                        outs=true;
                }
                if ((j == col1) || (j == col2) || (j == col3)) {
                    if (p_board->data[row1][j].candidates[i]==1)
                        ins=true;
                }
            }
            if ((ins) && (!outs)) {
                cell_array[count]=i;
                count++;        
            }
            if ((ins) && (outs)) {
                count1++;
            }
        }
    }

    if ((count == 3) && (count1 > 0)) {
        *cell_array1 = cell_array[0];
        *cell_array2 = cell_array[1];
        *cell_array3 = cell_array[2];
        return count;
    }

    count = 0; 
    count1 = 0;
    if ((col1 == col2) && (col2 == col3)) {
        for (int i = 0; i < 9; i++) {
            ins = false;
            outs = false;
            for (int j = 0; j < 9; j++) {
                num_cell_array = p_board->data[j][col1].num_candidates;    
                if ((j != row1) && (j != row2) && (j != row3)) {
                    if (p_board->data[j][col1].candidates[i] == 1)
                        outs=true;
                }
                if ((j == row1) || (j == row2) || (j == row3)) {
                    if (p_board->data[j][col1].candidates[i] == 1)
                        ins = true;
                }
            }
            if ((ins) && (!outs)) {
                cell_array[count] = i;
                count++;
            }
            if ((ins) && (outs)) {
                count1++;
            }
        }
    }

    if (count == 3 && count1 > 0) {
        *cell_array1 = cell_array[0];
        *cell_array2 = cell_array[1];
        *cell_array3 = cell_array[2];
        return count;
    }

    count = 0;
    count1 = 0;
    if ((rd1 == rd2) && (rd2 == rd3) && (cd1 == cd2) && (cd2 == cd3)) {
        for (int i = 0; i < 9; i++) {
            ins = false;
            outs = false;
            for (int j = rd1; j < rd1 + 3; j++)
                for (int k = cd1; k < cd1 + 3; k++) {
                    num_cell_array = p_board->data[j][k].num_candidates;
                    if (((j == row1) && (k == col1)) || ((j == row2) && (k == col2)) || ((j == row3) && (k == col3))) {
                        if (p_board->data[j][k].candidates[i] == 1)
                            ins=true;
                    } else {
                        if (p_board->data[j][k].candidates[i]==1)
                            outs=true;
                    }
                }
            if ((ins) && (!outs)) {
                cell_array[count]=i;
                count++;
            }
            if ((ins) && (outs)) {
                count1++;
            }
        }
    }

    if (count == 3 && count1 > 0) {
        *cell_array1 = cell_array[0];
        *cell_array2 = cell_array[1];
        *cell_array3 = cell_array[2];
        return count;
    }
    return 0;
}

int num_three_cells(SudokuBoard *p_board, triples_board cell_array[], int *num_cell_array) {
    int cell_array1 = -1;
    int cell_array2 = -1;
    int cell_array3 = -1;
    int r1, c1, r2, c2, r3, c3;
    int count = 0;
    for (int i = 0; i < 79; i++)
        for (int j = i + 1; j < 80; j++)
            for (int k = j + 1; k < 81; k++) {
                r1 = i / 9; 
                c1 = i % 9; 
                r2 = j / 9;  
                c2 = j % 9; 
                r3 = k / 9; 
                c3 = k % 9;
                if (pair_three_cell(p_board, r1, c1, r2, c2, r3, c3, &cell_array1, &cell_array2, &cell_array3) == 3) {
                    count++;
                    cell_array[count].row1 = r1;
                    cell_array[count].col1 = c1;
                    cell_array[count].row2 = r2;
                    cell_array[count].col2 = c2;
                    cell_array[count].row3 = r3;
                    cell_array[count].col3 = c3;
                    cell_array[count].cell_array1 = cell_array1;
                    cell_array[count].cell_array2 = cell_array2;
                    cell_array[count].cell_array3 = cell_array3;
                } 
            }
    *num_cell_array = count;
    return count;
}

void hidden_triples_processing(SudokuBoard *p_board, triples_board cell_array[], int *num_cell_array) {
    int r1, c1, r2, c2, r3, c3;
    int cell_array1, cell_array2, cell_array3;
    bool process;
    int num_process = 0;
    for (int i = 1; i <= *num_cell_array; i++) {
        r1 = cell_array[i].row1;
        c1 = cell_array[i].col1;
        r2 = cell_array[i].row2; 
        c2 = cell_array[i].col2;
        r3 = cell_array[i].row3; c3= cell_array[i].col3;
        cell_array1 = cell_array[i].cell_array1; 
        cell_array2 = cell_array[i].cell_array2;
        cell_array3 = cell_array[i].cell_array3;
        process = false;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((j != cell_array1) && (j != cell_array2) && (j != cell_array3)) {
                if (p_board->data[r1][c1].candidates[j] == 1) {
                    p_board->data[r1][c1].candidates[j] = 0;
                    p_board->data[r1][c1].num_candidates--;
                    process = true;
                }
                if (p_board->data[r2][c2].candidates[j] == 1) {
                    p_board->data[r2][c2].candidates[j] = 0;
                    p_board->data[r2][c2].num_candidates--;
                    process = true;
                }                   
                if (p_board->data[r3][c3].candidates[j] == 1) {
                    p_board->data[r3][c3].candidates[j] = 0;
                    p_board->data[r3][c3].num_candidates--;
                    process = true;
                }                                       
            }
        }
    if (process) 
        num_process++;
    }
    *num_cell_array = num_process;
}