#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union {
	float fData;
	char* cpData;
} Item;
/*
 *
 */
 typedef struct {
 Item data;
struct node* next;

 }node;

node * newNode()
{
    node* newN = (node*) malloc(sizeof (node));
newN->next=NULL;
}

typedef struct {
   node * top;
	/* TODO: ADD YOUR CODE HERE */
} Stack;
/*
 *
 */
void init(Stack *s) {
    s =(Stack*) malloc(sizeof(Stack));
    node* newN = newNode();
    s->top = newN;
	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
int isEmpty(Stack *s) {
	if(s->top=NULL)
    return 1;

    return 0;
}
/*
 *
 */
Item top(Stack *s) {
    if(isEmpty(s))
        return;
    return s->top->data;
	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
Item pop(Stack *s) {
  Item data;
  data.cpData=NULL;

  if (isEmpty(s)) {return data;}
  else{
   node * temp = newNode();
data = s->top->data;
temp = s->top;
s->top = s->top->next;
free(temp);
return data;
}	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void push(Stack *s, Item val) {
node *newN = newNode();
	newN->data=val;
	if(isEmpty(s)){
        s->top=newN;
        return;
	}
	newN->next = s->top;

	s->top= newN;

	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void destroy(Stack *s) {
	node * current = newNode();
	while(!isEmpty(s))
    {   current = s->top;
        free(current);
        s->top = s->top->next;
    }
	/* TODO: ADD YOUR CODE HERE */
}
int isOperator(char c)
{
	return(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' );
}
int pre(char c)
{
	switch (c)
	{
    case '(': return 0;
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	case ')': return 4;
	}
	return -1;
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
{ Stack s ;
init(&s);
    int i,j=0;
Item data,input; // input from stack, data from infix expression
for(i=0; i<strlen(infix);i++)
{   data.cpData=infix[i];
    if (isdigit(infix[i]))
        { while(isdigit(infix[i]) || infix[i] == '.')
           {postfix[j++]= infix[i++];
           }
        postfix[j++]= ' ';
  i--;}
    else if (infix[i]== '(')
                push(&s,data);
    else if (infix[i]== ')')
       {
           input = pop(&s);

         while (input.cpData!='(')
          {   input=pop(&s);
              postfix[j++]=input.cpData;
              postfix[j++]= ' ';

          }
          pop(&s);
          }
          else if(isOperator(infix[i]))

   {
       while (!isEmpty(&s)&& pre(data.cpData)<= pre(top(&s).cpData)) //pop stack to postfix
      {postfix[j++]=pop(&s).cpData;
      postfix[j++]= ' ';
      }
    push(&s,data);
   }
}
	while(!isEmpty(&s)){
    postfix[j++] = pop(&s).cpData;
        postfix[j++]= ' ';
	}
	postfix[--j]=NULL;
	/* TODO: ADD YOUR CODE HERE */
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
	/* TODO: ADD YOUR CODE HERE */
	return -1;
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
