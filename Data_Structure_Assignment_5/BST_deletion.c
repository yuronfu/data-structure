#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct treenode *TreePointer;
struct treenode
{
       int data;
       TreePointer leftchild;
       TreePointer rightchild;
};

TreePointer TreeNodeSearch(TreePointer node,int value)
{
            TreePointer temp;
            
            while(node != NULL)
            {
                      temp = node;
                      if(value < node->data) node = node->leftchild;
                      else if(value > node->data) node = node->rightchild;
                      else
                      {
                          temp = NULL;
                          break;
                      } 
            }
            return temp;
}
void InsertTreeNode(TreePointer *root,int value)
{
     TreePointer temp,insertpoint = TreeNodeSearch(*root,value);
     
     temp = malloc(sizeof(*temp));
     temp->data = value;
     temp->leftchild = NULL;
     temp->rightchild = NULL;
     
     if(!(*root)) *root =temp;
     else if(insertpoint != NULL)
     {
          if(value < insertpoint->data) insertpoint->leftchild = temp;
          else insertpoint->rightchild = temp;
     }
}
void DeleteProcess(TreePointer *head,TreePointer *delnode)
{
     TreePointer temp,subhead = *head;     //temp 為取代原本delnode位置的節點,subhead 為temp的parent位置  
     
     if( !((*delnode)->leftchild) )        //如果刪除節點的左子樹是空的,delnode的位置直接由右子樹的root取代 
     {
         if(*head == *delnode) (*head) = (*delnode)->rightchild;    //處理delnode為root的情況 
         else                                                       //處理非root的情況 
         {
             if((*head)->data < (*delnode)->data) (*head)->rightchild = (*delnode)->rightchild;    //delnode在其parent右邊的情況 
             else (*head)->leftchild = (*delnode)->rightchild;                                     //delnode在其parent左邊的情況
         }
     }
     else if( !((*delnode)->rightchild) )  //如果刪除節點的右子樹是空的,delnode的位置直接由左子樹的root取代 
     {
         if(*head == *delnode) (*head) = (*delnode)->leftchild;     //處理delnode為root的情況 
         else                                                       //處理非root的情況 
         {
             if((*head)->data < (*delnode)->data) (*head)->rightchild = (*delnode)->leftchild;
             else (*head)->leftchild = (*delnode)->leftchild;
         }
     }
     else                            //左,右子樹都非空 
     {
         temp = (*delnode)->leftchild;    //從左子樹找最大值的節點,並記錄其位置於temp 
         while( temp->rightchild != NULL) //從結束條件知道temp的右子樹root為NULL 
         {
                subhead = temp;           //紀錄temp的parent位置 
                temp = temp->rightchild;
         }
         if(subhead == *head) temp->rightchild = (*delnode)->rightchild; //delnode的左子樹root為最大值,左子樹root的右邊接上delnode的右子樹 
         else
         {
             if(temp->leftchild) subhead->rightchild = temp->leftchild;  //temp的左邊還有東西,接到subhead的右邊 
             else subhead->rightchild = NULL;                            //左邊沒東西了,subhead的右邊直接設為NULL 
             temp->leftchild = (*delnode)->leftchild;                    //temp取代delnode連接上delnode的左,右子樹 
             temp->rightchild = (*delnode)->rightchild;
         }
         if(*head == *delnode) *head = temp;                             //delnode為root則root以temp取代 
         else                                                            //delnode非root則delnode的parent接上temp 
         {
             if((*head)->data < (*delnode)->data) (*head)->rightchild = temp;
             else (*head)->leftchild = temp;
         }
     }
}
void TreeNodeDelete(TreePointer *root,char *input,int *total) //root 樹的根節點 
{
     int i,data;
     TreePointer head,delnode; //head 紀錄要刪除節點的parent位置, delnode 紀錄要刪除節點的位置 
     
     while(1)
     {
         scanf("%s",input);    //讀取要刪除節點的值
         if(input[0] >= 48 && input[0]<= 57)
         {
                     data = 0;
                     (*total)--;
                     for(i = 0 ; i < strlen(input) ; i++) data = data*10 + input[i]-48;
                     if((*root)->data == data) DeleteProcess(root,root);   //如果刪除的節點為root, 將parent視為root傳入DeleteProcess 
                     else    //刪除非root的節點 
                     {
                         delnode = *root;
                         while( delnode->data != data) //往下搜尋要刪除的節點 
                         {
                                head = delnode;        //紀錄下一個節點的parent 
                                if(data < delnode->data) delnode = delnode->leftchild;  //往下一個節點移動,左或右 
                                if(data > delnode->data) delnode = delnode->rightchild;
                         }
                         DeleteProcess(&head,&delnode);  //將要刪除的節點及期parent傳入DeleteProcess 
                     }
                     free(delnode);                      //釋放刪除的節點回記憶體 
         }
         else if(input[0] == 'E') return;                //讀到結束字元'E',結束刪除 
         else
         {
               printf("Error! %s is invalid input.",input);
               exit(EXIT_FAILURE);
         }
     }
}
void TreePrint(TreePointer root,int total)
{
     int i = 0,current = 0,p = 4,number[total];
     TreePointer Queue[total];
     
     Queue[0] = root;
     number[0] = 1;
     while(i < total-1)
     {
                if( Queue[current]->leftchild )
                {
                    Queue[++i] = Queue[current]->leftchild;
                    number[i] = number[current]*2;
                }
                if( Queue[current]->rightchild )
                {
                    Queue[++i] = Queue[current]->rightchild;
                    number[i] = number[current]*2+1;
                }
                current++;
     }

     printf("%d\n",Queue[0]->data);
     for(i = 1 ; i < total ; i++)
     {
           current = number[i-1]+1;
           if(current == p)
           {
                      printf("\n");
                      p*=2;
           }
           while( current < number[i] )
           {
                  printf("X ");
                  current++;
                  if(current == p)
                  {
                             printf("\n");
                             p*=2;
                  }
           }
           printf("%d ",Queue[i]->data);
     }
}
int main()
{
    char input[8];
    int i,data,total = 0;
    TreePointer root = NULL;
    
    printf("Input:\n");
    
    do
    {
           scanf("%s",&input);
           if(input[0] >= 48 && input[0]<= 57)
           {
                       data = 0;
                       for(i = 0 ; i < strlen(input) ; i++) data = data*10 + input[i]-48;
                       InsertTreeNode(&root,data);
                       total++;
           }
           else if(input[0] == 'D') TreeNodeDelete(&root,input,&total);
           else
           {
               printf("Error! %s is invalid input.",input);
               exit(EXIT_FAILURE);
           }
    }while(input[0] != 'E');
    
    printf("Output:\n");
    TreePrint(root,total);
    
    system("pause");
    return 0;
}
