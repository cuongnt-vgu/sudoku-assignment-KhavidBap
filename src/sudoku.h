#pragma once
#include <stdbool.h>

#define BOARD_SIZE 9

struct Cell_impl {
    int row_index;
    int col_index;
    int box_index;
    int num_candidates;
    int candidates[BOARD_SIZE];
    int value; // solved or 0
    bool fixed;
};
typedef struct Cell_impl Cell;

struct SudokuBoard_impl {
    int solved_counter;
    Cell **data;                                 // 9x9 cell board
    Cell **p_rows[BOARD_SIZE];                   // rows pointers
    Cell **p_cols[BOARD_SIZE];                   // cols pointers
    Cell **p_boxes[BOARD_SIZE];                  // boxes pointers
    Cell *solved_cells[BOARD_SIZE * BOARD_SIZE]; // solved cell pointers (maximum)
};
typedef struct SudokuBoard_impl SudokuBoard;

struct pairs_board_impl {
    int row1, row2, col1, col2;
    int cell_array1, cell_array2;
};
typedef struct pairs_board_impl pairs_board;

struct triples_board_impl {
    int row1, col1, row2, col2, row3, col3;
    int cell_array1, cell_array2, cell_array3;
    
};
typedef struct triples_board_impl triples_board;

void init_sudoku(SudokuBoard *p_board);
void load_sudoku(SudokuBoard *p_board, char *input_text);
bool apply_constraint(Cell **p_cells, int value);
bool is_in_list(Cell **p_array, int size, Cell *p);
void print_candidate_num(SudokuBoard *p_board);
void print_solution(SudokuBoard *p_board);
bool is_candidate(Cell *cell, int value);

void set_candidate(Cell *cell, int value);
void unset_candidate(Cell *cell, int value);
void set_candidates(Cell *cell, int *candidates, int size);
int *get_candidates(Cell *cell);

int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells);
bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter);
void free_sudoku(SudokuBoard *p_board);

// hidden pairs
void one_cell(SudokuBoard *p_board,int row, int col, int *count, pairs_board cell_array[]);
void hidden_pairs_process(SudokuBoard *p_board, pairs_board cell_array[], int num_cell_array);
int  one_cell_row(SudokuBoard *p_board, int row, int col, int i, int j);
int  one_cell_col(SudokuBoard *p_board, int row, int col, int i, int j);
int  one_cell_box(SudokuBoard *p_board, int row, int col, int i, int j);

// hidden triples
int  num_three_cells(SudokuBoard *p_board, triples_board cell_array[],int *num_cell_array);
void hidden_triples_processing(SudokuBoard *p_board, triples_board cell_array[],int *num_cell_array);
int  pair_three_cell(SudokuBoard *p_board,int row1, int col1,int row2, int col2,int row3,int col3,int *cell_array1, int *cell_array2,int *cell_array3);

// naked pairs
int  num_pairs_cell(SudokuBoard *p_board, pairs_board cell_array[],int *num_cell_array);
void naked_pair_processing(SudokuBoard *p_board, pairs_board cell_array[],int num_cell_array);
int  pair_two_cells(SudokuBoard *p_board,int row1, int col1,int row2, int col2,int *cell_array1, int *cell_array2);


int  num_cas3(SudokuBoard *p_board, triples_board cell_array[],int *num_cell_array);
void xuly_naked_triples(SudokuBoard *p_board, triples_board cell_array[],int num_cell_array);

int  Threecellnaker(SudokuBoard *p_board,int row1, int col1,int row2, int col2,int row3,int col3,int *cell_array1, int *cell_array2,int *cell_array3);