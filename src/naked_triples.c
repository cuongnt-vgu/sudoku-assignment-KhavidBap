#include "naked_triples.h"

#include <stdio.h>
#include <stdlib.h>

int naked_triples(SudokuBoard *p_board) {
    triples_board cell_array[100];
    int num_cell_array, n;
    n = num_triples_cell(p_board, cell_array, &num_cell_array);
    naked_triples_processing(p_board, cell_array, num_cell_array); 
    return num_cell_array;
}

int three_cell_naked(SudokuBoard *p_board, int row1, int col1, int row2, int col2, int row3, int col3, int *cell_array1, int *cell_array2, int *cell_array3) {
    int cell_array[10];
    int num_cell_array1 = p_board->data[row1][col1].num_candidates;
    int num_cell_array2 = p_board->data[row2][col2].num_candidates;
    int num_cell_array3 = p_board->data[row3][col3].num_candidates;
    
    if ((num_cell_array1 == 1) || (num_cell_array2 == 1) || (num_cell_array3 == 1))
        return 0;
    if ((num_cell_array1 > 3) || (num_cell_array2 > 3) || (num_cell_array3 > 3))
        return 0;

    int num_cell_array = 0;
    for (int i = 0; i < 9; i++) {
        if ((p_board->data[row1][col1].candidates[i] == 1) || (p_board->data[row2][col2].candidates[i] == 1) || (p_board->data[row3][col3].candidates[i] == 1)) {
            num_cell_array++;
            cell_array[num_cell_array] = i;
            if (num_cell_array > 3) 
                return 0;
        }
    }

    *cell_array1 = cell_array[1];
    *cell_array2 = cell_array[2];
    *cell_array3 = cell_array[3];

    if (((row1 == row2) && (row2 == row3)) || ((col1 == col2) && (col2 == col3)) || ((p_board->data[row1][col1].box_index == p_board->data[row2][col2].box_index) && (p_board->data[row2][col2].box_index == p_board->data[row3][col3].box_index))) {
        return 1;
    }
    return 0;
}

int num_triples_cell(SudokuBoard *p_board, triples_board cell_array[], int *num_cell_array) {
    int cell_array1 = -1;
    int cell_array2 = -1;
    int cell_array3 = -1;
    int r1, c1, r2, c2, r3, c3;
    int count = 0;
    for (int i=0; i < 79; i++)
        for (int j = i + 1; j < 80; j++)
            for (int k = j + 1; k < 81; k++) {
            r1 = i / 9;  
            c1 = i % 9; 
            r2 = j / 9;  
            c2 = j % 9; 
            r3 = k / 9; 
            c3 = k % 9;
            if (three_cell_naked(p_board, r1, c1, r2, c2, r3, c3, &cell_array1, &cell_array2, &cell_array3) == 1) {
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

void naked_triples_processing(SudokuBoard *p_board, triples_board cell_array[], int num_cell_array) {
    int r1, c1, r2, c2, r3, c3;
    int cell_array1, cell_array2, cell_array3;
    for (int i = 1; i <= num_cell_array; i++) {
        r1 = cell_array[i].row1;
        c1 = cell_array[i].col1;
        r2 = cell_array[i].row2; 
        c2 = cell_array[i].col2;
        r3 = cell_array[i].row3; 
        c3 = cell_array[i].col3;
        cell_array1 = cell_array[i].cell_array1; 
        cell_array2 = cell_array[i].cell_array2;
        cell_array3 = cell_array[i].cell_array3;

        if ((r1 == r2) && (r2 == r3)) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if ((j != c1) && (j != c2) && (j != c3)) {
                    if (p_board->data[r1][j].candidates[cell_array1] != 0) {
                        p_board->data[r1][j].candidates[cell_array1] = 0;
                        p_board->data[r1][j].num_candidates--;
                    }
                    if (p_board->data[r1][j].candidates[cell_array2] != 0) {
                        p_board->data[r1][j].candidates[cell_array2] = 0;
                        p_board->data[r1][j].num_candidates--;
                    }
                    if (p_board->data[r1][j].candidates[cell_array3] != 0) {
                        p_board->data[r1][j].candidates[cell_array3] = 0;
                        p_board->data[r1][j].num_candidates--;
                    }
                }
            }
        }
        
        if ((c1 == c2) && (c2 == c3)) {
            for (int j=0;j<BOARD_SIZE;j++) {
                if ((j != r1) && (j != r2) && (j != r3)) {
                    if (p_board->data[j][c1].candidates[cell_array1] != 0) {
                        p_board->data[j][c1].candidates[cell_array1] = 0;
                        p_board->data[j][c1].num_candidates--;
                    }
                    if (p_board->data[j][c1].candidates[cell_array2] != 0) {
                        p_board->data[j][c1].candidates[cell_array2] = 0;
                        p_board->data[j][c1].num_candidates--;
                    }
                    if (p_board->data[j][c1].candidates[cell_array3]!=0) {
                        p_board->data[j][c1].candidates[cell_array3] = 0;
                        p_board->data[j][c1].num_candidates--;
                    }
                }
            }
        }

        int box1, box2, box3;
        box1 = p_board->data[r1][c1].box_index;
        box2 = p_board->data[r2][c2].box_index;
        box3 = p_board->data[r3][c3].box_index;
        if ((box1==box2) && (box2==box3)) {
            for (int j = (r1 / 3) * 3; j < (r1 / 3) * 3 + 3; j++)
                for (int k = (c1 / 3) * 3; k < (c1 / 3) * 3 + 3; k++) {
                    if (((j != r1) || (k != c1)) && ((j != r2) || (k != c2)) && ((j != r3) || (k != c3))) {
                        if (p_board->data[j][k].candidates[cell_array1] != 0) {
                            p_board->data[j][k].candidates[cell_array1] = 0;
                            p_board->data[j][k].num_candidates--;
                        }
                        if (p_board->data[j][k].candidates[cell_array2] != 0) {
                            p_board->data[j][k].candidates[cell_array2] = 0;
                            p_board->data[j][k].num_candidates--;
                        }
                        if (p_board->data[j][k].candidates[cell_array3] != 0) {
                            p_board->data[j][k].candidates[cell_array3] = 0;
                            p_board->data[j][k].num_candidates--;
                        }
                }
            }
        }  
    }   
}