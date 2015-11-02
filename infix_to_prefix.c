#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  Max_String_length 1024
#define  Max_Stack_Size    100

typedef enum {rightparenthesis,leftparenthesis,times,divide,plus,minus,mod,operand}precedence;
typedef struct
{
        precedence data;
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
           
           if((symbol >= 48 && symbol <= 57) || (symbol >= 97 && symbol <= 122)) return operand;
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
void put_token(char *expr,element temp,int *position)
{
     switch(temp.data)
     {
                      case times:
                           expr[(*position)++] = '*';
                           break;
                      case divide:
                           expr[(*position)++] = '/';
                           break;
                      case plus:
                           expr[(*position)++] = '+';
                           break;
                      case minus:
                           expr[(*position)++] = '-';
                           break;
                      case mod:
                           expr[(*position)++] = '%';
                           break;
                      default :
                              printf("invalid symbol in the expression\n");
                              system("pause");
                              exit(EXIT_FAILURE);
     }
     return;
}
void infix_to_prefix(char *expr,char *prefix_expr,int length)
{
     int icp[7] = {17,17,12,12,11,11,12};     //{rightparenthesis,leftparenthesis,times,divide,plus,minus,mod,operand}
     int isp[7] = {0,17,12,12,11,11,12};
     int i,count = 0;
     char ctemp;
     precedence token;
     element temp;
     
     while(length != -1)
     {
                  token = get_token(expr,&length);
                  if(token == operand) prefix_expr[count++] = expr[length+1];
                  else
                  {
                      temp.data = token;
                      if(token == leftparenthesis)
                      {
                               while(stack[top].data != rightparenthesis) put_token(prefix_expr,pop(),&count);
                               pop();
                      }
                      else if(top == -1 || icp[token] >= isp[stack[top].data]) push(temp);
                      else
                      {
                          while(icp[token] < isp[stack[top].data]) put_token(prefix_expr,pop(),&count);
                          push(temp);
                      }
                  }
     }
     while(top != -1) put_token(prefix_expr,pop(),&count);
     for(i = 0 ; i < (count-1)/2 ; i++)
     {
           ctemp = prefix_expr[i];
           prefix_expr[i] = prefix_expr[count-1-i];
           prefix_expr[count-1-i] = ctemp;
     }
}
int main()
{
    char expr[Max_String_length] = {},prefix_expr[Max_String_length]={};
    int i;
    
    printf("please enter a infix expression:\n");
    scanf("%s",expr);
    
    infix_to_prefix(expr,prefix_expr,strlen(expr)-1);
    printf("%s\n",prefix_expr);
    
    system("pause");
    return 0;
}
