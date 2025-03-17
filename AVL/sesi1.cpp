#include <stdio.h>
#include <stdlib.h>

struct Node{
	int val;
	int height;
	Node *left;
	Node *right;
}*node;

Node* createNode(int val){
	Node *c = (Node*)malloc(sizeof(Node));
	c->val = val;
	c->height = 1;
	c->left = NULL;
	c->right = NULL;
	return c;
}

int height(Node *root){
	if(root == NULL){
		return 0;
	}
	else{
		return root->height;
	}
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int getBalance(Node *root){
	if(root == NULL){
		return 0;
	}
	else{
		return height(root->left) - height(root->right);
	}
}

Node* leftRotate(Node *x){
	Node *y = x->right;
	Node *T2 = y->left;
	
	x->right = T2;
	y->left = x;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
	
}

Node *rightRotate(Node *y){
	Node *x = y->left;
	Node *T2 = x->right;
	
	x->right = y;
	y->left = T2;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return x;
	
}

Node* insert(Node *root, int val){
	if(root == NULL){
		return createNode(val);
	}
	else if(val < root->val){
		root->left = insert(root->left, val);
	}
	else if(val > root->val){
		root->right = insert(root->right, val);
	}
	else{
		return root;
	}
	
	root->height = max(height(root->left), height(root->right)) + 1;
	
	int balance = getBalance(root);
	
	if(balance < -1 && val > root->right->val){
		return leftRotate(root);
	}
	
	if(balance > 1 && val < root->left->val){
		return rightRotate(root);
	}
	
	if(balance < -1 && val < root->right->val){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	if(balance > 1 && val > root->left->val){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	return root;
}

void InOrder(Node *root){
	if(root != NULL){
		InOrder(root->left);
		printf("%d ", root->val);
		InOrder(root->right);
	}
}

int main(){
	Node *root = NULL;
	
	root = insert(root, 10);
	root = insert(root, 15);
	root = insert(root, 20);
	
	InOrder(root);
	
	return 0;
}
