#include "hidden_singles.h"
#include <stdlib.h>

int hidden_singles(SudokuBoard *p_board) {
    int num_hidden_singles = 0;
    bool found;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (p_board->data[i][j].num_candidates > 1) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    found = true;
                    if (p_board->data[i][j].candidates[k] != 0) {
                        found = false;
                        for (int l = 0; l < BOARD_SIZE; l++)  
                            if ((l != j) && (p_board->data[i][l].candidates[k] > 0)) {
                                found = true;
                                break;
                            }
                        if (found == true) {
                            found = false;
                            for (int l = 0; l < BOARD_SIZE; l++) 
                                if ((l != i) && (p_board->data[l][j].candidates[k] > 0)) {
                                    found = true;
                                    break;
                                }
                            if (found == true) {
                                found = false;                            
                                int box_size = (i / 3) * 3 + j / 3;
                                int box_cell = (i % 3) * 3 + j % 3;
                                for (int l = 0; l < BOARD_SIZE; l++) {
                                    Cell cell = *p_board->p_boxes[box_size][l] ;
                                    if ((l != box_cell) && (cell.candidates[k] > 0)) {
                                        found = true;
                                        break;
                                    }
                                }
                            }
                        }                 
                        if (found == false) {
                            p_board->data[i][j].candidates[k] = 1;
                            p_board->data[i][j].value = k + 1;
                            p_board->data[i][j].num_candidates = 1;
                            num_hidden_singles++;
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (p_board->data[i][j].num_candidates == 1) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (k != p_board->data[i][j].value - 1)
                        p_board->data[i][j].candidates[k] = 0;
                }
            }
        }
    }
    return num_hidden_singles;
}