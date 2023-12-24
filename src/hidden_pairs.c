#include "hidden_pairs.h"

int hidden_pairs(SudokuBoard *p_board) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (p_board->data[i][j].num_candidates == 2) {
                for (int k = j + 1; k < BOARD_SIZE; k++) {
                    if (p_board->data[i][k].num_candidates == 2 &&
                        p_board->data[i][j].candidates[0] == p_board->data[i][k].candidates[0] &&
                        p_board->data[i][j].candidates[1] ==
                            p_board->data[i][k].candidates[1]) {
                        for (int l = 0; l < BOARD_SIZE; l++) {
                            if (l != j && l != k &&
                                p_board->data[i][l].num_candidates > 1 &&
                                p_board->data[i][l].candidates[0] ==
                                    p_board->data[i][j].candidates[0] &&
                                p_board->data[i][l].candidates[1] ==
                                    p_board->data[i][j].candidates[1]) {
                                p_board->data[i][l].candidates[0] = 0;
                                p_board->data[i][l].candidates[1] = 0;
                                p_board->data[i][l].num_candidates = 0;
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}
