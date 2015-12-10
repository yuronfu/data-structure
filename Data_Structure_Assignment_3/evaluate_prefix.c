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
int eval(char *expr,int length) //透過此函數計算結果並回傳 expr是一個prefix expression，length是最後一個字元的index 
{
    precedence token;
    element temp;
    int op1,op2,digit;
    
    while(length != -1) //每讀過一個字元length減1，讀完整個字串length=-1時跳出〈由右往左讀〉
    {
                 token = get_token(expr,&length); //透過 get_token讀取目前index字元的類別，參考課本範例 
                 
                 if(token == space) continue; //由於運算元和運算子由空白隔開，讀到空白直接跳到下一次的讀取 
                 if(token == operand) //讀到運算元時，繼續讀取直到讀到空白 
                 {
                          digit = 1;
                          temp.data = expr[length+1]-48; //由於右往所讀，先讀到的是個位數，接下來讀到的為十位、百位 
                          while(get_token(expr,&length) != space) temp.data = temp.data + (expr[length+1]-48)*(digit*=10);
                          push(temp); //讀到空白後，將累計的數值結果push到stack 
                 }
                 else     //不是數字就移除stack最上面的兩個element存到op1,op2中 
                 {
                     op1 = pop().data;
                     op2 = pop().data;
                     switch(token)    //檢查token是哪一個二元運算子，計算結果並push到stack中 
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
    return pop().data; //由於每次運算後結果都push進stack，所以最終結果也在stack中，直接pop出答案並回傳 
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
