#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  Max_String_length 1024
#define  Max_Stack_Size    100

typedef enum {rightparenthesis,leftparenthesis,times,divide,plus,minus,mod,operand,space}precedence;
typedef struct
{
        int data;
}element;
element stack[Max_Stack_Size];
int top = -1;

void push(element item)
{
     if(top + 1 == Max_Stack_Size) printf("Stack is full.");
     else stack[++top] = item;
     
     return;
}
element pop()
{
    if(top > -1) return stack[top--];
    else printf("Stack is empty\n");
}
precedence get_token(char *expr,int *position)
{
           char symbol = expr[(*position)--];
           
           if(symbol >= 48 && symbol <= 57) return operand;
           switch(symbol)
           {
                         case ')': return rightparenthesis;
                         case '(': return leftparenthesis;
                         case '*': return times;
                         case '/': return divide;
                         case '+': return plus;
                         case '-': return minus;
                         case '%': return mod;
                         case ' ': return space;
                         default :
                                 printf("invalid symbol in the expression\n");
                                 system("pause");
                                 exit(EXIT_FAILURE);
                         
           }
}
int eval(char *expr,int length) //�z�L����ƭp�⵲�G�æ^�� expr�O�@��prefix expression�Alength�O�̫�@�Ӧr����index 
{
    precedence token;
    element temp;
    int op1,op2,digit;
    
    while(length != -1) //�CŪ�L�@�Ӧr��length��1�AŪ����Ӧr��length=-1�ɸ��X�q�ѥk����Ū�r
    {
                 token = get_token(expr,&length); //�z�L get_tokenŪ���ثeindex�r�������O�A�Ѧҽҥ��d�� 
                 
                 if(token == space) continue; //�ѩ�B�⤸�M�B��l�Ѫťչj�}�AŪ��ťժ�������U�@����Ū�� 
                 if(token == operand) //Ū��B�⤸�ɡA�~��Ū������Ū��ť� 
                 {
                          digit = 1;
                          temp.data = expr[length+1]-48; //�ѩ�k����Ū�A��Ū�쪺�O�Ӧ�ơA���U��Ū�쪺���Q��B�ʦ� 
                          while(get_token(expr,&length) != space) temp.data = temp.data + (expr[length+1]-48)*(digit*=10);
                          push(temp); //Ū��ťի�A�N�֭p���ƭȵ��Gpush��stack 
                 }
                 else     //���O�Ʀr�N����stack�̤W�������element�s��op1,op2�� 
                 {
                     op1 = pop().data;
                     op2 = pop().data;
                     switch(token)    //�ˬdtoken�O���@�ӤG���B��l�A�p�⵲�G��push��stack�� 
                     {
                                  case times:
                                       temp.data = op1 * op2;
                                       break;
                                  case divide:
                                       temp.data = op1 / op2;
                                       break;
                                  case plus:
                                       temp.data = op1 + op2;
                                       break;
                                  case minus:
                                       temp.data = op1 - op2;
                                       break;
                                  case mod:
                                       temp.data = op1 % op2;
                                       break;
                     }
                     push(temp);
                 }
    }
    return pop().data; //�ѩ�C���B��ᵲ�G��push�istack�A�ҥH�̲׵��G�]�bstack���A����pop�X���רæ^�� 
}
int main()
{
    char expr[Max_String_length] = {};
    int result;
    
    printf("Please enter a prefix expression with space between operator and operand:\n");
    gets(expr);
    
    result = eval(expr,strlen(expr)-1);
    
    printf("Output:\n%d\n",result);
    
    system("pause");
    return 0;
}
