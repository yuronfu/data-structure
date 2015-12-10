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
     TreePointer temp,subhead = *head;     //temp �����N�쥻delnode��m���`�I,subhead ��temp��parent��m  
     
     if( !((*delnode)->leftchild) )        //�p�G�R���`�I�����l��O�Ū�,delnode����m�����ѥk�l��root���N 
     {
         if(*head == *delnode) (*head) = (*delnode)->rightchild;    //�B�zdelnode��root�����p 
         else                                                       //�B�z�Droot�����p 
         {
             if((*head)->data < (*delnode)->data) (*head)->rightchild = (*delnode)->rightchild;    //delnode�b��parent�k�䪺���p 
             else (*head)->leftchild = (*delnode)->rightchild;                                     //delnode�b��parent���䪺���p
         }
     }
     else if( !((*delnode)->rightchild) )  //�p�G�R���`�I���k�l��O�Ū�,delnode����m�����ѥ��l��root���N 
     {
         if(*head == *delnode) (*head) = (*delnode)->leftchild;     //�B�zdelnode��root�����p 
         else                                                       //�B�z�Droot�����p 
         {
             if((*head)->data < (*delnode)->data) (*head)->rightchild = (*delnode)->leftchild;
             else (*head)->leftchild = (*delnode)->leftchild;
         }
     }
     else                            //��,�k�l�𳣫D�� 
     {
         temp = (*delnode)->leftchild;    //�q���l���̤j�Ȫ��`�I,�ðO�����m��temp 
         while( temp->rightchild != NULL) //�q�������󪾹Dtemp���k�l��root��NULL 
         {
                subhead = temp;           //����temp��parent��m 
                temp = temp->rightchild;
         }
         if(subhead == *head) temp->rightchild = (*delnode)->rightchild; //delnode�����l��root���̤j��,���l��root���k�䱵�Wdelnode���k�l�� 
         else
         {
             if(temp->leftchild) subhead->rightchild = temp->leftchild;  //temp�������٦��F��,����subhead���k�� 
             else subhead->rightchild = NULL;                            //����S�F��F,subhead���k�䪽���]��NULL 
             temp->leftchild = (*delnode)->leftchild;                    //temp���Ndelnode�s���Wdelnode����,�k�l�� 
             temp->rightchild = (*delnode)->rightchild;
         }
         if(*head == *delnode) *head = temp;                             //delnode��root�hroot�Htemp���N 
         else                                                            //delnode�Droot�hdelnode��parent���Wtemp 
         {
             if((*head)->data < (*delnode)->data) (*head)->rightchild = temp;
             else (*head)->leftchild = temp;
         }
     }
}
void TreeNodeDelete(TreePointer *root,char *input,int *total) //root �𪺮ڸ`�I 
{
     int i,data;
     TreePointer head,delnode; //head �����n�R���`�I��parent��m, delnode �����n�R���`�I����m 
     
     while(1)
     {
         scanf("%s",input);    //Ū���n�R���`�I����
         if(input[0] >= 48 && input[0]<= 57)
         {
                     data = 0;
                     (*total)--;
                     for(i = 0 ; i < strlen(input) ; i++) data = data*10 + input[i]-48;
                     if((*root)->data == data) DeleteProcess(root,root);   //�p�G�R�����`�I��root, �Nparent����root�ǤJDeleteProcess 
                     else    //�R���Droot���`�I 
                     {
                         delnode = *root;
                         while( delnode->data != data) //���U�j�M�n�R�����`�I 
                         {
                                head = delnode;        //�����U�@�Ӹ`�I��parent 
                                if(data < delnode->data) delnode = delnode->leftchild;  //���U�@�Ӹ`�I����,���Υk 
                                if(data > delnode->data) delnode = delnode->rightchild;
                         }
                         DeleteProcess(&head,&delnode);  //�N�n�R�����`�I�δ�parent�ǤJDeleteProcess 
                     }
                     free(delnode);                      //����R�����`�I�^�O���� 
         }
         else if(input[0] == 'E') return;                //Ū�쵲���r��'E',�����R�� 
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
