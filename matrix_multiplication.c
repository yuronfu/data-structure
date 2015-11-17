#include <stdio.h>
#include <stdlib.h>

typedef struct matrixnode *MatrixPointer;
typedef struct
{
        int row;
        int col;
        int value;
}matrixentry;
struct matrixnode
{
       MatrixPointer down;
       MatrixPointer right;
       union{
             matrixentry entry;
             MatrixPointer next;
       }u;
};

MatrixPointer MatrixInput(int mrow,int mcol,MatrixPointer *headnode,int headnodenum)
{
              int total = 0,i,j,cellvalue;
              MatrixPointer head,temp,last;
              
              head = malloc(sizeof(*head));
              head->u.entry.row = mrow;
              head->u.entry.col = mcol;
              
              for(i = 0 ; i < headnodenum ; i++)
              {
                    temp = malloc(sizeof(*temp));
                    headnode[i] = temp;
                    headnode[i]->right = temp;
                    headnode[i]->u.next = temp;
              }
              head->right = headnode[0];
              
              for(i = 0 ; i < mrow ; i++) //Input matrix entries
              {
                    last = headnode[i];
                    for(j = 0 ; j < mcol ; j++)
                    {
                          scanf("%d",&cellvalue);
                          if(cellvalue)
                          {
                                       temp = malloc(sizeof(*temp));
                                       temp->u.entry.row = i;
                                       temp->u.entry.col = j;
                                       temp->u.entry.value = cellvalue;
                                       last->right = temp;
                                       last = temp;
                                       headnode[j]->u.next->down = temp;
                                       headnode[j]->u.next = temp;
                                       total++;
                          }
                    }
                    last->right = headnode[i]; //close row list
              }
              head->u.entry.value = total;
              
              for(i = 0 ; i < headnodenum ; i++) headnode[i]->u.next->down = headnode[i]; //close column list
              for(i = 0 ; i < headnodenum-1 ; i++) headnode[i]->u.next = headnode[i+1];   //link head nodes
              headnode[headnodenum-1]->u.next = head; //last headnode requires to point to head
              
              return head;
}
void MatrixPrint(MatrixPointer M,MatrixPointer *headnode)
{
     int i,j;
     MatrixPointer currententry;
     
     for(i = 0 ; i < M->u.entry.row ; i++)
     {
           currententry = headnode[i]->right;
           for(j = 0 ; j < M->u.entry.col ; j++)
           {
                 if(i == currententry->u.entry.row && j == currententry->u.entry.col)
                 {
                      printf("%d\t",currententry->u.entry.value);
                      currententry = currententry->right;
                 }
                 else printf("0\t");
           }
           printf("\n");
     }
}
MatrixPointer multiplication(MatrixPointer A,MatrixPointer B,MatrixPointer *headnode,int headnodenum)
{
              int total = 0,i,cellvalue = 0;
              MatrixPointer head,temp,last,headA,headB,entryA,entryB;
              
              head = malloc(sizeof(*head));
              head->u.entry.row = A->u.entry.row;
              head->u.entry.col = B->u.entry.col;
              
              for(i = 0 ; i < headnodenum ; i++)
              {
                    temp = malloc(sizeof(*temp));
                    headnode[i] = temp;
                    headnode[i]->right = temp;
                    headnode[i]->u.next = temp;
              }
              head->right = headnode[0];
              
              headA = A->right;
              for(i = 0 ; i < A->u.entry.row ; i++)
              {
                    last = headnode[i];
                    entryA = headA->right;
                    entryB = B->right->down;
                    for(headB = B->right ; headB != B ;)
                    {
                              if(entryA == headA || entryB == headB) //scanned over the current row, go back to first entry
                              {                                 //or scanned over the current column, go to the entry of next column
                                        if(cellvalue)   // has value store it, similar to the part in MatrixInput
                                        {
                                                     temp = malloc(sizeof(*temp));
                                                     temp->u.entry.row = i;
                                                     temp->u.entry.col = headB->down->u.entry.col;
                                                     temp->u.entry.value = cellvalue;
                                                     last->right = temp;
                                                     last = temp;
                                                     headnode[headB->down->u.entry.col]->u.next->down = temp;
                                                     headnode[headB->down->u.entry.col]->u.next = temp;
                                                     total++;
                                        }
                                        cellvalue = 0;
                                        entryA = headA->right;             //back to first entry
                                        headB = headB->u.next;               //go to next column
                                        entryB = headB->down;              //first entry of next column
                              }
                              else switch((entryA->u.entry.col == entryB->u.entry.row)? 0:(entryA->u.entry.col < entryB->u.entry.row)? -1:1)
                              {    //compare column of A and row of B
                                   case -1:  //row of B is ahead of column of A
                                        entryA = entryA->right;
                                        break;
                                   case 0:   //do multiplication and store result
                                        cellvalue = cellvalue + entryA->u.entry.value*entryB->u.entry.value;
                                        entryA = entryA->right;
                                        entryB = entryB->down;
                                        break;
                                   case 1:   //column of A is ahead of row of B
                                        entryB = entryB->down;
                              }
                    }
                    last->right = headnode[i]; //close row list
                    headA = headA->u.next;
              }
              head->u.entry.value = total;
              
              for(i = 0 ; i < headnodenum ; i++) headnode[i]->u.next->down = headnode[i]; //close column list
              for(i = 0 ; i < headnodenum-1 ; i++) headnode[i]->u.next = headnode[i+1];   //link head nodes
              headnode[headnodenum-1]->u.next = head; //last headnode requires to point to head
              
              return head;
}
int main()
{
    int mrow,mcol,headnodenum;
    MatrixPointer A,B,C;
    
    printf("calculate A*B for matrix A & B:\n");
    
    printf("please enter row and column and value of the first matrix(A):\n");
    scanf("%d %d",&mrow,&mcol);
    headnodenum = (mrow > mcol)? mrow:mcol;
    MatrixPointer headnodeA[headnodenum];
    A = MatrixInput(mrow,mcol,headnodeA,headnodenum);
    
    printf("please enter row and column and value of the second matrix(B):\n");
    scanf("%d %d",&mrow,&mcol);
    headnodenum = (mrow > mcol)? mrow:mcol;
    MatrixPointer headnodeB[headnodenum];
    B = MatrixInput(mrow,mcol,headnodeB,headnodenum);
    
    //MatrixPrint(A,headnodeA);
    //MatrixPrint(B,headnodeB);
    
    if(A->u.entry.col == B->u.entry.row)
    {
                      headnodenum = (A->u.entry.row > B->u.entry.col)? A->u.entry.row:B->u.entry.col;
                      MatrixPointer headnodeC[headnodenum];
                      C = multiplication(A,B,headnodeC,headnodenum); //C = A*B
                      printf("\nthe result of A*B:\n");
                      MatrixPrint(C,headnodeC);
    }
    else printf("Error! number of columns of A  is not equal to number of rows of B");
    
    system("pause");
    return 0;
}
