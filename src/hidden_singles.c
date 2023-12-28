#include "hidden_singles.h"
#include <stdlib.h>
int hidden_singles(SudokuBoard *p_board)
{
    
    int count = 0;
    int l=0;
    int i,j,candidate;
    bool found;
    for ( i = 0; i < 9; i++) 
    {
        for (j = 0; j < 9; j++) 
        {
            if (p_board->data[i][j].num_candidates > 1) 
            {
                for (int k = 0; k < 9; k++) 
                {
                     candidate = p_board->data[i][j].candidates[k];
                    
                    found = true;
                    if (candidate !=0)
                    {
                     
                    found = false;
                    
                    for (l = 0; l < 9; l++) 
                        if ((l != j) &&
                            (p_board->data[i][l].candidates[k]>0)) 
                        {
                            found = true;
                         
                            break;

                        }
                    if (found)
                    {
                    found = false;
                    for (l = 0; l < 9; l++) 
                        if ((l != i) &&
                            (p_board->data[l][j].candidates[k]>0)) 
                        {
                            found = true;
                             break;
                        }
                    if (found)
                    {
                    found = false;                            
                    int box = (i / 3) * 3 + j / 3;
                    int box_cell = (i % 3) * 3 + j % 3;
                    for (l = 0; l < 9; l++) 
                    {
                        Cell cell=*p_board->p_boxes[box][l] ;
                        
                        if ((l != box_cell) &&
                            (cell.candidates[k]>0)) 
                        {
                            found = true;
                            break;
                        }
                    }
                    }
                    }
                   // int m;                   
                    if (!found) 
                    {
                       

                        p_board->data[i][j].candidates[k] = 1;
                        p_board->data[i][j].value = k+1;
                        p_board->data[i][j].num_candidates = 1;
                    
                        count++;
                        break;
                    }
                } //for (int k = 0; k < 9; k++) 
            }
        }
        }
    }
    for ( i = 0; i < BOARD_SIZE; i++) 
    {
        for (j = 0; j < BOARD_SIZE; j++) 
        {
            if (p_board->data[i][j].num_candidates==1) 
            {
                for (int k = 0; k < BOARD_SIZE; k++) 
                {
                    if (k!= p_board->data[i][j].value-1)
                      p_board->data[i][j].candidates[k]=0;
                }
            }
        }
    }
    

    return count;
}
    



/*-----------------

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values) {
    int numHiddenValue = 0;
    for (int i = 1; i <= BOARD_SIZE; i++) {
        int counter = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (p_cells[j]->fixed || p_cells[j]->num_candidates == 1) continue;
            counter += is_candidate(p_cells[j], i);
        }
        if (counter == 1) hidden_single_values[numHiddenValue++] = i;
    }
    return numHiddenValue;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter) {
    int *hidden_single_values = (int*) malloc(BOARD_SIZE * sizeof(int));
    int numHiddenValue;
    numHiddenValue = find_hidden_single_values(p_cells, hidden_single_values);
    for (int i = 0; i < numHiddenValue; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (p_cells[j]->fixed) continue;
            bool check = true;
            for (int k = 0; k < *p_counter; k++) 
                if (p_cells[j] == p_hidden_singles[k].p_cell) {
                    check = false;
                    break;
                }
            if (!check) continue;
            if (is_candidate(p_cells[j], hidden_single_values[i])) {
                p_hidden_singles[*p_counter].p_cell = p_cells[j];
                p_hidden_singles[*p_counter].value = hidden_single_values[i];
                (*p_counter)++;
            }
        }
    }
    free(hidden_single_values);
}

int hidden_singles(SudokuBoard *p_board) {
    int num_hidden_single = 0;
    HiddenSingle *hidden_singles = (HiddenSingle*) malloc(BOARD_SIZE * BOARD_SIZE * sizeof(HiddenSingle));
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &num_hidden_single);
        find_hidden_single(p_board->p_cols[i], hidden_singles, &num_hidden_single);
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &num_hidden_single);
    }
    for (int i = 0; i < num_hidden_single; i++) {
        for (int j = 1; j <= BOARD_SIZE; j++) 
            if (is_candidate(hidden_singles[i].p_cell, j)) unset_candidate(hidden_singles[i].p_cell, j);
        set_candidate(hidden_singles[i].p_cell, hidden_singles[i].value);
    }
    free(hidden_singles);
    return num_hidden_single;
}
*/
