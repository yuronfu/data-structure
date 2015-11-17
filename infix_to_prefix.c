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
void infix_to_prefix(char *expr,char *prefix_expr,int length) //prefix_expr�x�s�ഫ�᪺���G expr��infix expression 
{
     int i,count = 0; //count:�ثeprefix_expr��index�q0�}�l 
     char ctemp;
     precedence token;
     element temp;
     
     while(length != -1) //�CŪ�L1�Ӧr��length��1�AŪ�����expr�N���X(�ѥk����Ū) 
     {
                  token = get_token(expr,&length); //�z�Lget_tokenŪ���ثe���r�����O 
                  if(token == space) continue;     //token���ťմN����U�@��Ū�� 
                  if(token == operand) prefix_expr[count++] = expr[length+1]; //token�O�Ʀr�Υ����ƴN��X��prefix_expr�� 
                  else //token�p�G�O�B��l�Astack����(top=-1)��Ū��token���u����>=stack�̤W��token���u���סApush��stack 
                  {
                      temp.data = token;  //token�s��Ȧs��element�� 
                      if(token == leftparenthesis) //�p�Gtoken��'('�A�N��')'�w�g�bstack�� 
                      {                            //�z�Lput_token��Xstack����token����I��')' 
                               while(stack[top].data != rightparenthesis) put_token(prefix_expr,pop(),&count);
                               pop();              // ����stack����')' 
                      }
                      else if(top == -1 || icp[token] >= isp[stack[top].data]) push(temp);
                      else  //Ū��token���u����<stack�̤W����token 
                      {     //�z�Lput_token��Xstack����token����token���u����>=stack[top]�~push 
                          while(top != -1 && icp[token] < isp[stack[top].data]) put_token(prefix_expr,pop(),&count);
                          push(temp);
                      }
                  }
     }
     while(top != -1) put_token(prefix_expr,pop(),&count);  //�r��Ū���N�ѤU���B��l��X 
     for(i = 0 ; i < (count-(count%2))/2 ; i++) //�]�����G�O�ѫ᩹�e��(�k����Ū)�A�ҥH�̫����prefix_expr 
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
