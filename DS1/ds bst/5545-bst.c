#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
char* data;
struct Node *left;
struct Node *right;
}Node;

Node* newNode(char* word)
{
    Node*p= (Node*)malloc(sizeof(Node));
   p->data= malloc(25*sizeof(char));
    strcpy(p->data,word);
    p->left=NULL;
    p->right=NULL;
    return p;
}
Node* bstSearch(Node*root,char*sent);

int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}
int isEmpty(Node *root)
{
if(root==NULL)
    return 1;
else return 0;
}
void insert(Node**node, char* fileName)
{
    FILE *fp;
char* fw= malloc(25*sizeof(char));
fp = fopen(fileName,"r");
   while( fscanf( fp, " %[^\n]",fw) !=EOF )
        {

       if (*node==NULL)
        (*node)=newNode(fw);
       else{
        Node* parent = NULL;
        Node* p = (*node);
        while(p!=NULL){
            parent=p;
        if (strcmp(fw,p->data)==0)
        { p=NULL;
         continue;}
       else if (strcmp(fw,p->data)<0)
            p = p->left;
          else
        p = p->right;
        }
     if (strcmp(fw,parent->data)<0)
        parent->left = newNode(fw);
     else
        parent->right=newNode(fw);

   }
strcpy(fw,"\0");
}

fclose(fp);

}
int size(Node * root)
{ if(isEmpty(root))
    return 0;
    else
        return 1+size(root->left)+size(root->right);
}

int height(Node *root) {
if(isEmpty(root))
    return -1;
else
    return 1+max(height(root->left), height(root->right));
}
void clearT(Node*root)
{
    if(root!=NULL)
    { clearT( root->left);
    clearT( root->right);
        free(root);
        root= NULL;

    }
}

Node *minValue(Node* node) {
  Node* current = node;
   while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

Node *maxValue(Node* node) {
  Node* current = node;
   while (current->right != NULL) {
    current = current->right;
  }
  return current;
}

/*Node * inOrderSucc(Node *root, char *data)
{ Node*succ = NULL;

while(root!=NULL)
       {
    if (strcmp(data,root->data)<0)
		{   succ = root;
			root = root->left;
		}
    else if(strcmp(data,root->data)>0)
    {
        root = root->right;
    }
    else{
            if (root->right!=NULL)
	    	succ = minValue(root->right);
		break;
		}
		}
   return succ;

}


Node * inOrderPred(Node *root, char *data)
{
    Node*Pred = NULL;
while(root!=NULL)
       {
    if (strcmp(data,root->data)<0)
		{
			root = root->left;
		}
    else if(strcmp(data,root->data)>0)
    {   Pred = root;
        root = root->right;
    }
    else{
         if (root->left!=NULL)
	    	Pred = maxValue(root->left);
       break;
       }
		}
   return Pred;

}*/

 Node* bstSearch(Node*root,char*sent)
{
     Node*current=NULL;
     while(root!=NULL){
            current=root;
            if (strcmp(sent,root->data)==0)
            return root;
            else if (strcmp(sent,root->data)<0)
            root = root->left;
            else if (strcmp(sent,root->data)>0)
            root = root->right;
          }
     return current;
 }




main(int argc, char**argv) {
	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

    char sent[100];
    Node* root=NULL;

    insert(&root,argv[1]);
   int sze=size(root);
    int ht=height(root);
    printf("Height of BST: %d \n",ht);
    printf("Size of BST: %d \n",sze);
printf("Input sentance: ");
gets(sent);
    char*t=" ";
    char*temp= strtok(sent,t);
    while(temp!=NULL)
    { Node*word=bstSearch(root,temp);
     if(strcmp(word->data,temp)==0)
        printf("%s is correct\n",temp);
        else
            printf("%s isn't correct, Did you mean %s, %s, %s ?\n",temp,word->data,inOrderSucc(root,word->data)->data,inOrderPred(root,word->data)->data);

    temp=strtok(NULL,t);

    }
free(sent);
clearT(root);

    return 0;
}
