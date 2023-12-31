#include "naked_pairs.h"
#include <stdio.h>
#include <stdlib.h>

int naked_pairs(SudokuBoard *p_board) {
   pairs_board cell_array[100];
   int num_cell_array,n;
   n=num_pairs_cell(p_board, cell_array , &num_cell_array);
    xuly_naked_pair(p_board, cell_array,num_cell_array);  
    return num_cell_array;
}
int pair_2cell(SudokuBoard *p_board,int row1, int col1,int row2, int col2,int *cell_array1, int *cell_array2)
{
    int count=0;
    int cell_array[2];
    
    if((p_board->data[row1][col1].num_candidates==2) && (p_board->data[row2][col2].num_candidates==2) )
    {
       if ((row1==row2)||(col1==col2) || 
            (p_board->data[row1][col1].box_index==p_board->data[row2][col2].box_index)   )
        {
           for (int i=0;i<9;i++)
                  if ((p_board->data[row1][col1].candidates[i]==1) && (p_board->data[row2][col2].candidates[i]==1))
                  {
                    cell_array[count] = i;
                    count++;
                  }
        }
    }
    *cell_array1 = cell_array[0];
    *cell_array2 = cell_array[1];
    
    return count;
}

int num_pairs_cell(SudokuBoard *p_board, pairs_board cell_array[],int *num_cell_array)
{
    int cell_array1=-1,cell_array2=-1;
    int r1,c1,r2,c2;
    int count=0;
      
    for (int i=0;i<80;i++)
        for(int j=i+1;j<81;j++)
        {
            r1 = i/9;  c1 = i%9; r2=j/9;  c2 = j%9;
          
            if (pair_2cell(p_board,r1,c1,r2,c2,&cell_array1, &cell_array2 )==2)
               {
                count++;
                cell_array[count].row1 = r1;
                cell_array[count].col1 = c1;
                cell_array[count].row2 = r2;
                cell_array[count].col2 = c2;
                cell_array[count].cell_array1 = cell_array1;
                cell_array[count].cell_array2 = cell_array2;
                }
              
        }
    *num_cell_array = count;
    return count;
}

void xuly_naked_pair(SudokuBoard *p_board, pairs_board cell_array[],int num_cell_array)
{
    int r1,c1,r2,c2,cell_array1,cell_array2;
    int r1_dau,c1_dau,r2_dau,c2_dau;
    int i,j,k;
    for (i=1; i<=num_cell_array;i++)
    {
        r1 = cell_array[i].row1;c1=cell_array[i].col1;
        r2=cell_array[i].row2; c2= cell_array[i].col2;
        cell_array1=cell_array[i].cell_array1; cell_array2 = cell_array[i].cell_array2;
        r1_dau=(r1/3)*3; c1_dau = (c1/3)*3;
        r2_dau = (r2/3)*3; c2_dau = (c2/3)*3;
        // xu ly dongcot
        if(r1==r2)
        {
            for(j=0;j<BOARD_SIZE;j++)
            {
                
                if((j!=c1) && (j!=c2))
                {
                    if(p_board->data[r1][j].candidates[cell_array1]==1)
                    {
                        p_board->data[r1][j].candidates[cell_array1]=0;
                        p_board->data[r1][j].num_candidates--;
                    }
                    if(p_board->data[r1][j].candidates[cell_array2]==1)
                    {
                        p_board->data[r1][j].candidates[cell_array2]=0;
                        p_board->data[r1][j].num_candidates--;
                    }
                }
            }
        }
    
        if(c1==c2) // xu ly dong
        {
            for(j=0;j<BOARD_SIZE;j++)
            {
                if((j!=r1) && (j!=r2))
                {
                    if(p_board->data[j][c1].candidates[cell_array1]==1)
                    {
                        p_board->data[j][c1].candidates[cell_array1]=0;
                        p_board->data[j][c1].num_candidates--;
                    }
                    if(p_board->data[j][c2].candidates[cell_array2]==1)
                    {
                        p_board->data[j][c2].candidates[cell_array2]=0;
                        p_board->data[j][c2].num_candidates--;
                    }
                }
            }
        }
         if(p_board->data[r1][c1].box_index==p_board->data[r2][c2].box_index) // xu ly kho
        {
            for(j=r1_dau;j<r1_dau+3;j++)
                for(k=c1_dau;k<c1_dau+3;k++)
                {
                    if(  ((j!=r1) || (k!=c1))   && ((j!=r2) || (k!=c2)))
                    {
                        if(p_board->data[j][k].candidates[cell_array1]==1)
                        {
                            p_board->data[j][k].candidates[cell_array1]=0;
                            p_board->data[j][k].num_candidates--;
                        }
                        if(p_board->data[j][k].candidates[cell_array2]==1)
                        {
                            p_board->data[j][k].candidates[cell_array2]=0;
                            p_board->data[j][k].num_candidates--;
                        }
                    }
                }
        }
    }
}
