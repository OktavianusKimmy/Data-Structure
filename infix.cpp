#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct tnode{
	char value;
	struct tnode *left;
	struct tnode *right;
}tnode;

tnode* createNewNode(char value){
	tnode* newNode = (tnode*)malloc(sizeof(tnode));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int isOperator(char c){
	return(c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void buildPrefTree(tnode** root, char prefeq[], int *pos){
	if(*root == NULL){
		*root = createNewNode(prefeq[*pos]);
	}
		
	if(isOperator(prefeq[*pos])){
		*pos = *pos + 1;
		(*root)->left = createNewNode(prefeq[*pos]);
		buildPrefTree(&(*root)->left, prefeq, pos);
		
		*pos = *pos + 1;
		(*root)->right = createNewNode(prefeq[*pos]);
		buildPrefTree(&(*root)->right, prefeq, pos);
	}

}

tnode* buildPostTree(char postfix[]){
	tnode* stack[100];
	int top = -1;
	int i;
	
	for(i = 0; postfix[i] != '\0'; i++){
		tnode* newNode = createNewNode(postfix[i]);
		
		if(isdigit(postfix[i])){
			stack[++top] = newNode;
		}
		else if(isOperator(postfix[i])){
			newNode->right = stack[top--];
			newNode->left = stack[top--];
			stack[++top] = newNode;
		}
		
	}
	return stack[top];
}

int rank(char op){
	if(op == '+' || op == '-') return 3;
	if(op == '*' || op == '/') return 2;
	if(op == '^') return 1;
}

char stack[100];
int countOp = 0;
tnode* angka[100];
int countAngka = 0;
void buildInTree(char* infeq, int pos, int l){
	for(int i = pos; i<l; i++){
		if(isOperator(infeq[i])){
			stack[countOp] = infeq[i];
			countOp++;
		}
		else{
			tnode *newNode = createNewNode(infeq[i]);
			angka[countAngka] = newNode[i];
			countAngka++;
		}
	}
	
	int min = 4;
	char stackAf[100];
	for(int i = countOp-1; i>0; i--){
		if(rank(stack[i]) < min){
			min = i;
		}
		
	}	
}

void buildPrefTree(tnode** root, char prefeq[], int *pos){
	if(*root == NULL){
		*root = createNewNode(prefeq[*pos]);
	}
		
	if(isOperator(prefeq[*pos])){
		*pos = *pos + 1;
		(*root)->left = createNewNode(prefeq[*pos]);
		buildPrefTree(&(*root)->left, prefeq, pos);
		
		*pos = *pos + 1;
		(*root)->right = createNewNode(prefeq[*pos]);
		buildPrefTree(&(*root)->right, prefeq, pos);
	}

}

int evaluate(tnode* root){
	if(root->value == '+'){
		return evaluate(root->left) + evaluate(root->right);
	}
	else if(root->value == '-'){
		return evaluate(root->left) - evaluate(root->right);
	}
	else if(root->value == '*'){
		return evaluate(root->left) * evaluate(root->right);
	}
	else if(root->value == '/'){
		return evaluate(root->left) / evaluate(root->right);
	}
	else if(root->value == '^'){
		return (int) pow(evaluate(root->left), evaluate(root->right));
	}
	else{
		return root->value - '0';
	}
}

void inOrder(tnode* root){
	if(root != NULL){
		if(isOperator(root->value)) putchar('(');
		inOrder(root->left);
		printf("%c ", root->value);
		inOrder(root->right);
		if(isOperator(root->value)) putchar(')');
	}
}

void preOrder(tnode* root){
	if(root != NULL){
		printf("%c ", root->value);
		inOrder(root->left);
		inOrder(root->right);
	}
}

void postOrder(tnode* root){
	if(root != NULL){
		inOrder(root->left);
		inOrder(root->right);
		printf("%c ", root->value);
	}
}

int main(){
	char prefeq[] = "+^234";
	char posteq[] = "423^+";
	char infeq[] = "(2^3)+4";
	
	// Prefix
	int pos = 0;
	tnode* root = NULL;
	
	buildPrefTree(&root, prefeq, &pos);
	
	inOrder(root);
	puts("");
//	preOrder(root);
//	puts("");
//	postOrder(root);
	
	int res = evaluate(root);
	printf("\n Result : %d\n", res);
	
	
	// Postfix
	tnode* postTree = buildPostTree(posteq);
//	preOrder(postTree);
	puts("");
	inOrder(postTree);
	
	// Infix
	buildInTree(infeq, 0, strlen(infeq));
	
	return 0;
}
