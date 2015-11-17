#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  Max_String_length 1024
#define  Max_Stack_Size    100

typedef enum {
        rightparenthesis,leftparenthesis,
        logicalnot,
        times,divide,mod,plus,minus,
        lshift,rshift,
        less,greater,lessorequal,greaterorequal,
        equal,notequal,
        bitwiseand,bitwiseor,
        logicaland,logicalor,
        assignment,
        operand,space
}precedence;
int icp[] = {17,17,15,13,13,13,12,12,11,11,10,10,10,10,9,9,8,6,5,4,2};
int isp[] = {0 ,17,15,13,13,13,12,12,11,11,10,10,10,10,9,9,8,6,5,4,2};
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
                         case '!': return logicalnot;
                         case '*': return times;
                         case '/': return divide;
                         case '%': return mod;
                         case '+': return plus;
                         case '-': return minus;
                         case '<':
                              if(expr[(*position)] == '<') {(*position)--; return lshift;}
                              else return less;
                         case '>':
                              if(expr[(*position)] == '>') {(*position)--; return rshift;}
                              else return greater;
                         case '=':
                              if(expr[(*position)] == '=') {(*position)--; return equal;}
                              if(expr[(*position)] == '!') {(*position)--; return notequal;}
                              if(expr[(*position)] == '<') {(*position)--; return lessorequal;}
                              if(expr[(*position)] == '>') {(*position)--; return greaterorequal;}
                              else return assignment;
                         case '&':
                              if(expr[(*position)] == '&') {(*position)--; return logicaland;}
                              else return bitwiseand;
                         case '|':
                              if(expr[(*position)] == '|') {(*position)--; return logicalor;}
                              else return bitwiseor;
                         case ' ': return space;
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
                      case logicalnot:
                           expr[(*position)++] = '!';
                           break;
                      case times:
                           expr[(*position)++] = '*';
                           break;
                      case divide:
                           expr[(*position)++] = '/';
                           break;
                      case mod:
                           expr[(*position)++] = '%';
                           break;
                      case plus:
                           expr[(*position)++] = '+';
                           break;
                      case minus:
                           expr[(*position)++] = '-';
                           break;
                      case lshift:
                           expr[(*position)++] = '<';
                           expr[(*position)++] = '<';
                           break;
                      case rshift:
                           expr[(*position)++] = '>';
                           expr[(*position)++] = '>';
                           break;
                      case less:
                           expr[(*position)++] = '<';
                           break;
                      case greater:
                           expr[(*position)++] = '>';
                           break;
                      case lessorequal:
                           expr[(*position)++] = '=';
                           expr[(*position)++] = '<';
                           break;
                      case greaterorequal:
                           expr[(*position)++] = '=';
                           expr[(*position)++] = '>';
                           break;
                      case equal:
                           expr[(*position)++] = '=';
                           expr[(*position)++] = '=';
                           break;
                      case notequal:
                           expr[(*position)++] = '=';
                           expr[(*position)++] = '!';
                           break;
                      case bitwiseand:
                           expr[(*position)++] = '&';
                           break;
                      case bitwiseor:
                           expr[(*position)++] = '|';
                           break;
                      case logicaland:
                           expr[(*position)++] = '&';
                           expr[(*position)++] = '&';
                           break;
                      case logicalor:
                           expr[(*position)++] = '|';
                           expr[(*position)++] = '|';
                           break;
                      case assignment:
                           expr[(*position)++] = '=';
                           break;
                      default :
                              printf("invalid symbol in the expression\n");
                              system("pause");
                              exit(EXIT_FAILURE);
     }
     return;
}
void infix_to_prefix(char *expr,char *prefix_expr,int length) //prefix_expr儲存轉換後的結果 expr為infix expression 
{
     int i,count = 0; //count:目前prefix_expr的index從0開始 
     char ctemp;
     precedence token;
     element temp;
     
     while(length != -1) //每讀過1個字元length減1，讀完整個expr就跳出(由右往左讀) 
     {
                  token = get_token(expr,&length); //透過get_token讀取目前的字元類別 
                  if(token == space) continue;     //token為空白就跳到下一次讀取 
                  if(token == operand) prefix_expr[count++] = expr[length+1]; //token是數字或未知數就輸出到prefix_expr中 
                  else //token如果是運算子，stack為空(top=-1)或讀到token的優先度>=stack最上面token的優先度，push到stack 
                  {
                      temp.data = token;  //token存到暫存的element中 
                      if(token == leftparenthesis) //如果token為'('，代表')'已經在stack中 
                      {                            //透過put_token輸出stack中的token直到碰到')' 
                               while(stack[top].data != rightparenthesis) put_token(prefix_expr,pop(),&count);
                               pop();              // 移除stack中的')' 
                      }
                      else if(top == -1 || icp[token] >= isp[stack[top].data]) push(temp);
                      else  //讀到token的優先度<stack最上面的token 
                      {     //透過put_token輸出stack中的token直到token的優先度>=stack[top]才push 
                          while(top != -1 && icp[token] < isp[stack[top].data]) put_token(prefix_expr,pop(),&count);
                          push(temp);
                      }
                  }
     }
     while(top != -1) put_token(prefix_expr,pop(),&count);  //字串讀完將剩下的運算子輸出 
     for(i = 0 ; i < (count-(count%2))/2 ; i++) //因為結果是由後往前放(右往左讀)，所以最後反轉prefix_expr 
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
    gets(expr);
    
    infix_to_prefix(expr,prefix_expr,strlen(expr)-1);
    printf("%s\n",prefix_expr);
    
    system("pause");
    return 0;
}
