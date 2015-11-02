#include <stdio.h>
#include <stdlib.h>

#define MAX_TERM 1024
typedef struct
{
        int row;
        int column;
        int value;
}term;
term a[MAX_TERM];

void MatrixInput(int mrow, int mcol, term *M)
{
     int i,j,total = 1,temp;
     for(i = 0 ; i < mrow ; i++)
     {
           for(j = 0 ; j < mcol ; j++)
           {
                 scanf("%d",&temp);
                 if(temp)
                 {
                         M[total].row = i;
                         M[total].column = j;
                         M[total].value = temp;
                         total++;
                 }
           }
     }
     M[0].value = --total;
}
void MatrixPrint(term *M)
{
     int i,j,currentPos = 1;
     for(i = 0 ; i < M[0].row ; i++)
     {
           for(j = 0 ; j < M[0].column ; j++)
           {
                 if(i == M[currentPos].row && j == M[currentPos].column)
                 {
                      printf("%d\t",M[currentPos].value);
                      currentPos++;
                 }
                 else printf("0\t");
           }
           printf("\n");
     }
}
void fastTranspose(term *a,term *b)
{
     int i,j,startingPos[a[0].column];
     
     b[0].row = a[0].column;
     b[0].column = a[0].row;
     b[0].value = a[0].value;
     
     if(a[0].value > 0)
     {
                   for(i = 0 ; i < a[0].column ; i++) startingPos[i] = 0;
                   for(i = 1 ; i <= a[0].value ; i++) startingPos[a[i].column]++;
                   for(i = 1 ; i < a[0].column ; i++) startingPos[i] = startingPos[i] + startingPos[i-1];
                   for(i = a[0].value ; i >= 1 ; i--)
                   {
                         j = startingPos[a[i].column]--;
                         b[j].row = a[i].column;
                         b[j].column = a[i].row;
                         b[j].value = a[i].value;
                   }
     }
}
int main()
{
    int mrow,mcol;
    term b[MAX_TERM];
    
    printf("enter row and column of matrix:\n");
    scanf("%d %d",&mrow,&mcol);
    //printf("row=%d , col=%d",mrow,mcol);
    
    a[0].row = mrow;
    a[0].column = mcol;
    MatrixInput(mrow,mcol,a);
    //MatrixPrint(a);
    
    fastTranspose(a,b);
    printf("Output:\n");
    MatrixPrint(b);
    
    system("pause");
    return 0;
}
