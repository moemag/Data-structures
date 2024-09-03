#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union {
	float fData;
	char *cpData;
} Item;
/*
 *
 */
typedef struct {
	int top;
	Item arr[255];
	/* TODO: ADD YOUR CODE HERE */
} Stack;
/*
 *
 */
void init(Stack *s) {
	s->top=-1;
	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
int isEmpty(Stack *s) {
    if(s->top == -1)
        return 1;
    else
    return 0;
}
/*
 *
 */
Item top(Stack *s) {
   return (s->arr[s->top]);
}
/*
 *
 */
Item pop(Stack *s) {
    if(!isEmpty(s))
    return (s->arr[s->top--]);
	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void push(Stack *s, Item val) {
           s->top++;
        s->arr[s->top] = val;

	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void destroy(Stack *s) {
   if(!isEmpty(&s))
    free(s->arr);
/* TODO: ADD YOUR CODE HERE */
}
int priority(char x)
{
     switch (x)
    {
    case '+':
    case '-':
     return 0;

    case '*':
    case '/':
     return 1;

    case '^':
     return 2;

    case '(':
     return 3;
}
}


int isOperand(char ch)
{
	if (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-')
	{
		return 1;
	}
	else return 0;
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)*4 --> 23+4*
 */

void infixToPostfix(char* infix, char* postfix)
{
    Stack s;
    init(&s);
    int i=0,j=0;
Item c;
c.cpData=0;
while (infix[i]!='\0')
{c.cpData=infix[i];
    if(isdigit(infix[i]))
    {while(isdigit(infix[i])|| infix[i] == '.')
     {  postfix[j++]=infix[i++];
    }
    postfix[j++] = ' ';
    i--;
    }
  else if (infix[i]=='(')
            { push(&s,c);
            }

    else if(infix[i]==')')
    {
        while (!isEmpty(&s)&&top(&s).cpData!='(')
               {
                   postfix[j++]=pop(&s).cpData;
                   postfix[j++] = ' ';
                    }
            pop(&s);
    }
    else if (isOperand(infix[i]))
    {
     while (!isEmpty(&s)&& priority(infix[i])<= priority(top(&s).cpData)&&top(&s).cpData!='(')
  {
       postfix[j++]= pop(&s).cpData;
        postfix[j++] = ' ';
  }
    push(&s,c);
   }
i++;
}
 while(!isEmpty(&s))
    {postfix[j++]=pop(&s).cpData;
    postfix[j++] = ' ';
    }
    postfix[j--]=NULL;
    destroy(&s); /* TODO: ADD YOUR CODE HERE */
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
  Stack s;
  Item tok,z;

  tok.cpData =strtok(postfix," ");
  float x,y,r;
  z.fData=0.0;
  z.cpData=NULL;
  init(&s);
   while (tok.cpData !=NULL)
   {
       if(isdigit(*tok.cpData))
       {tok.fData=atof(tok.cpData);
          push(&s,tok);
  } else
   { x=pop(&s).fData;
     y=pop(&s).fData;
       if( *tok.cpData == '+')
    z.fData = (x + y);
    else if( *tok.cpData =='*')
        z.fData = (x*y);
    else if( *tok.cpData =='-')
        z.fData = (x-y);
    else if( *tok.cpData =='/')
        z.fData = (x/y);
        else if( *tok.cpData =='^')
        z.fData = (pow(x,y));
   push(&s,z);
   }
   tok.cpData= strtok(NULL," ");
}
r = pop(&s).fData;
	destroy(&s);
	return r;
}
/*
 *
 */
void replaceNewLineBySpace(char *s) {
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv) {
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
