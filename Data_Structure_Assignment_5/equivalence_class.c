#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_Set_Size 1024

typedef struct{
        int value;
        int parent;
}Treenode;
Treenode set[Max_Set_Size];
int total = 0;

void Union(int i,int j)
{
     int temp = set[i].parent + set[j].parent;
     
     if(set[i].value < set[j].value)
     {
                     set[j].parent = i;
                     set[i].parent = temp;
     }
     else
     {
         set[i].parent = j;
         set[j].parent = temp;
     }
}
int Find(int i)
{
    int j;
    
    for(j = 0; set[j].value != i ; j++) ;
    for(i = j ; set[i].parent >= 0 ; i = set[i].parent) ;
    
    return i;
}
void equivalence_construct(char *input)
{
     int i,data1,data2;
     
     while(1)
     {
             scanf("%s",input);                         //Ū�������������� 
             if(input[0] >= 48 && input[0]<= 57)
             {
                        data1 = data2 = 0;
                        for(i = 0 ; input[i] != '=' ; i++) data1 = data1*10 + input[i]-48;      //Ū���������䪺�ƭ� 
                        for(i = i+1 ; i < strlen(input) ; i++) data2 = data2*10 + input[i]-48;  //Ū�������k�䪺�ƭ� 
                        Union( Find(data1), Find(data2) );     //��쵥�����䪺�����Ҧb���X�M��Union 
             }
             else if(input[0] == 'E') return;                  //Ū�쵲���r��'E',���� 
             else
             {
                 printf("Error! %s is invalid input.",input);
                 exit(EXIT_FAILURE);
             }
     }
}
void TreePrint()
{
     int i,j,rootnumber = 0,count,currentlayer,roots[total],layer[total];       //roots���������Ҧb���X��root, layer�����b�𤤪�level 
     int *r = malloc((rootnumber+1)*sizeof(int));
     
     for(i = 0 ; i < total ; i++) if(set[i].parent < 0) //�����`�@������root�br[]�� 
     {
           r[rootnumber] = i;
           r = realloc(r,((++rootnumber)+1)*sizeof(int));
     }
     
     for(i = 0 ; i < total ; i++) //��C�Ӥ����b�𤤪�root�Player,�L�{�PFind���� 
     {
           layer[i] = 1;
           for(j = i ; set[j].parent >= 0 ; j = set[j].parent) layer[i]++;
           roots[i] = j;
     }
     
     for(i = 0 ; i < rootnumber ; i++)  //�L�Xr[]����i��roots�����X 
     {
           currentlayer = 1;
           count = 0;
           printf("(");
           while(count + set[r[i]].parent < 0) //�L��r[i]���X���Ҧ������h���� 
           {
                       printf("(");
                       for(j = 0 ; j < total ; j++) if(layer[j] == currentlayer && roots[j] == r[i])
                       {                            //print element in current layer & counting printed element
                             printf("%d,",set[j].value);
                             count++;
                       }
                       currentlayer++;
                       printf("\b)");
           }
           printf(")\n");
     }
}
int main()
{
    char input[8];
    int i,data;
    
    printf("Input:\n");
    
    do
    {
           scanf("%s",&input);
           if(input[0] >= 48 && input[0]<= 57)
           {
                       data = 0;
                       for(i = 0 ; i < strlen(input) ; i++) data = data*10 + input[i]-48;
                       set[total].parent = -1;
                       set[total].value = data;
                       total++;
           }
           else if(input[0] == 'S') equivalence_construct(input);
           else
           {
               printf("Error! %s is invalid input.",input);
               exit(EXIT_FAILURE);
           }
    }while(input[0] != 'E');
    
    printf("Output:\n");
    //for(i = 0 ; i < total ; i++) printf("%d: %d, %d\n",i,set[i].parent,set[i].value);
    TreePrint();
    
    system("pause");
    return 0;
}
