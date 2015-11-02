#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  Max_String_length 1024
#define  Max_Stack_Size    100

typedef enum {rightparenthesis,leftparenthesis,times,divide,plus,minus,mod,operand}precedence;
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
    else printf("Stack is empty");
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
                         default :
                                 printf("invalid symbol in the expression\n");
                                 system("pause");
                                 exit(EXIT_FAILURE);
                         
           }
}
int eval(char *expr,int length)
{
    precedence token;
    element temp;
    int op1,op2;
    
    while(length != -1)
    {
                 token = get_token(expr,&length);
                 
                 if(token == operand)
                 {
                          temp.data = expr[length+1]-48;
                          push(temp);
                 }
                 else
                 {
                     op1 = pop().data;
                     op2 = pop().data;
                     switch(token)
                     {
                                  case times:
                                       temp.data = op1 * op2;
                                       push(temp);
                                       break;
                                  case divide:
                                       temp.data = op1 / op2;
                                       push(temp);
                                       break;
                                  case plus:
                                       temp.data = op1 + op2;
                                       push(temp);
                                       break;
                                  case minus:
                                       temp.data = op1 - op2;
                                       push(temp);
                                       break;
                                  case mod:
                                       temp.data = op1 % op2;
                                       push(temp);
                                       break;
                     }
                 }
    }
    return pop().data;
}
int main()
{
    char expr[Max_String_length] = {};
    int result;
    
    printf("Please enter a prefix expression without no space between each token:\n");
    scanf("%s",expr);
    
    result = eval(expr,strlen(expr)-1);
    
    printf("Output:\n%d\n",result);
    
    system("pause");
    return 0;
}
