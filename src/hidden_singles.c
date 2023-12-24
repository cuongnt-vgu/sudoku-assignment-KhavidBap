#include "sudoku.h"
#include <stdlib.h>

int hidden_singles(SudokuBoard *p_board) {
    int num_detected = 0;
    for (int num = 1; num <= BOARD_SIZE; num++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            int row_count = 0, col_count = 0, box_count = 0;
            int row_index = -1, col_index = -1, box_index = -1;
            for (int j = 0; j < BOARD_SIZE; j++) {
                Cell *row_cell = &(p_board->data[i][j]);
                Cell *col_cell = &(p_board->data[j][i]);
                Cell *box_cell = p_board->p_boxes[i][j];
                if (row_cell->num_candidates != 1 && is_candidate(row_cell, num)) {
                    row_count++;
                    row_index = j;
                }
                if (col_cell->num_candidates != 1 && is_candidate(col_cell, num)) {
                    col_count++;
                    col_index = j;
                }
                if (box_cell->num_candidates != 1 && is_candidate(box_cell, num)) {
                    box_count++;
                    box_index = j;
                }
            }
            if (row_count == 1) {
                int *candidates = get_candidates(&(p_board->data[i][row_index]));
                if (candidates[0] == num) {
                    set_candidates(&(p_board->data[i][row_index]), &num, 1);
                    num_detected++;
                }
                free(candidates);
            }
            if (col_count == 1) {
                int *candidates = get_candidates(&(p_board->data[col_index][i]));
                if (candidates[0] == num) {
                    set_candidates(&(p_board->data[col_index][i]), &num, 1);
                    num_detected++;
                }
                free(candidates);
            }
            if (box_count == 1) {
                int box_row = (i / 3) * 3 + box_index / 3;
                int box_col = (i % 3) * 3 + box_index % 3;
                int *candidates = get_candidates(&(p_board->data[box_row][box_col]));
                if (candidates[0] == num) {
                    set_candidates(&(p_board->data[box_row][box_col]), &num, 1);
                    num_detected++;
                }
                free(candidates);
            }
        }
    }
    return num_detected;
}