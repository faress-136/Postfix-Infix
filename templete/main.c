#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
/*
 * Item: An item that is being pushed to or popped from the stack
 * It may be float (to be used while evaluating the postfix)
 * It may be char (to be used while converting infix to postfix)
 */
typedef union
{
    float fData;
    char  cData;
} Item;
/*
 *
 */
typedef struct
{

    Item items[MAXSIZE];
    int top;
} Stack;
/*
 *
 */
Stack * initialize()
{
    Stack *s=malloc(sizeof(Stack));
    s->top=0;
    return s;
}
/*
 *
 */
int isEmpty(Stack *s)
{
    if (s->top==0) {
        return 1;
    }
    else
        return 0;
}
/*
 *
 */
Item top(Stack *s)
{
    return s->items[s->top-1];
}
/*
 *
 */
Item pop(Stack *s)
{
    Item value;
    s->top--;
    value=s->items[s->top];
    return value;
}
/*
 *
 */
void push(Stack *s, Item value)
{
    s->items[s->top]=value;
    s->top++;
}
/*
 * infixToPostfix: converts an expression in infix notation to
 * to a postfix notation (Reverse-Polish Notation)
 * ASSUME single-digit operands
 * ASSUME ^*+-/ operators
 * e.g., 22+31 --> 22 31 +
 * e.g., (2+3)*4 --> 2 3 + 4 *
 */

int priority(char c)
{
    switch (c)
    {
        case '*':
        case '/':
        case '%':
            return 2;
            
        case '+':
        case '-':
            return 1;
            
//        case '(':
//            return 3;
    }
    return -1;
}
int isNum(char *fares)
{
    int i;
    for (i=0; i<strlen(fares); i++)
    {
        if (isdigit(fares[i]))
            return 1;
    }
    return 0;
}
void infixToPostfix(char* infix, char* postfix)
{
    Stack *s=initialize();
    Item f;
    char m[2];
    char *fares=strtok(infix," ");
    while(fares!=NULL) {
        if (isNum(fares)) {
            strcat(postfix,fares);
            strcat(postfix, " ");
        }
        else {
            f.cData=fares[0];
            if (isEmpty(s))
                push(s, f);
           else if (fares[0]=='(')
            push(s, f);
            else if (top(s).cData=='(')
                push(s, f);
        else if (fares[0]==')')
        {
            while (!isEmpty(s)&&top(s).cData!='(')
            {
                m[0]=pop(s).cData;
                m[1]='\0';
                strcat(postfix,m);
                strcat(postfix, " ");
            }
          pop(s);
        }
        else
        {
            while (!isEmpty(s)&&priority(top(s).cData)>=priority(fares[0])&&top(s).cData!='(')
            {
                m[0]=pop(s).cData;
               m[1]='\0';
               // postfix[strlen(postfix)]=pop(s).cData;
                //postfix[strlen(postfix)+1]=' ';
                
               strcat(postfix,m);
                strcat(postfix, " ");
            }
            push(s, f);
        }
        }
        fares=strtok(NULL , " ");
    }
    while (!isEmpty(s))
    {
        m[0]=pop(s).cData;
        m[1]='\0';
        strcat(postfix,m);
        strcat(postfix, " ");
    }
/* TODO: ADD YOUR CODE HERE */
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 * (Reverse-Polish Notation)
 * ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
    /* TODO: ADD YOUR CODE HERE */
    return -1;
}
/*
 *
 */
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}

