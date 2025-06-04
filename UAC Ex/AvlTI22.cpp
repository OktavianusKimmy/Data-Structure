#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	int date;
	char name[100];
	int height;
	int num;
	Node *left;
	Node *right;
};

int max(int a, int b){
	return a > b ? a : b;
}

int height(Node *root){
	if(root == NULL) return 0;
	return root->height;
}

int getBalanceFactor(Node *root){
	if(root == NULL) return 0;
	return height(root->left) - height(root->right);
}

Node* leftRotate(Node *x){
	Node *y = x->right;
	Node *z = y->left;
	
	y->left = x;
	x->right = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Node* rightRotate(Node *x){
	Node *y = x->left;
	Node *z = y->right;
	
	y->right = x;
	x->left = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Node* insert(Node *root, Node *newNode){
	if(root == NULL) return newNode;
	else if(root->date > newNode->date) root->left = insert(root->left, newNode);
	else if(root->date < newNode->date) root->right = insert(root->right, newNode);
	else if(root->date == newNode->date){
		if(strcmp(root->name, newNode->name) > 0) root->left = insert(root->left, newNode);
		else root->right = insert(root->right, newNode);
	}
	else return root;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root);
		else{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if(balance < -1){
		if(getBalanceFactor(root->left) <= 0) return leftRotate(root);
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}

void in(Node *root){
	if(root != NULL){
		in(root->left);
		printf("%d %s %d\n", root->date, root->name, root->num);
		in(root->right);
	}
}

int num;

void inFix(Node *root){
	if(root != NULL){
		inFix(root->left);
		root->num = num++;
		inFix(root->right);
	}
}

Node* delAVL(Node *root, int target){
	if(root == NULL) return root;
	else if(root->num > target) root->left = delAVL(root->left, target);
	else if(root->num < target) root->right = delAVL(root->right, target);
	else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		}
		else if(root->left == NULL || root->right == NULL){
			Node *temp = root->left ? root->left : root->right;
			free(root);
			return temp;
		}
		else{
			Node *temp = root->left;
			while(temp->right){
				temp = temp->right;
			}
			
			root->date = temp->date;
			strcpy(root->name, temp->name);
			
			root = delAVL(root->left, temp->num);
		}
	}
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root);
		else{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if(balance < -1){
		if(getBalanceFactor(root->left) <= 0) return leftRotate(root);
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}

int main(){
	Node *root = NULL;
	
	int P, Q;
	scanf("%d %d", &P, &Q); getchar();
	for(int i = 0; i<P; i++){
		int date;
		char name[100];
		scanf("%d %s", &date, name); getchar();
		Node *newNode = (Node*)malloc(sizeof(Node));
		newNode->date = date;
		strcpy(newNode->name, name);
		newNode->height = 1;
		newNode->left = NULL;
		newNode->right = NULL;
		root = insert(root, newNode);
	}
	
	for(int i = 0; i<Q; i++){
		num = 1;
		inFix(root);
		int target;
		scanf("%d", &target);
		root = delAVL(root, target);
	}
	puts("Inorder:");
	in(root);
}
