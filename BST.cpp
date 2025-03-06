#include <stdio.h>
#include <stdlib.h>

typedef struct tnode{
	int value;
	tnode *left;
	tnode *right;
}tnode;

tnode* createNode(int value){
	tnode *c = (tnode*)malloc(sizeof(tnode));
	c->value = value;
	c->left = NULL;
	c->right = NULL;
	return c;
}

tnode* buildBST(tnode* root, int value){
	if(root == NULL){
		return createNode(value);
	}
	
	if(value < root->value){
		root->left = buildBST(root->left, value);
	}
	else{
		root->right = buildBST(root->right, value);
	}
	return root;
}
root->left = delNode(root->left, temp->value);
int search(tnode* root, int value){
	if(root == NULL){
		return -1;
	}
	
	if(root->value == value){
		return root->value;
	}
	else if(value < root->value){
		return search(root->left, value);
	}
	else if(value > root->value){
		return search(root->right, value);
	}
}

void InOrder(tnode* root){
	if(root == NULL) return;
	
	InOrder(root->left);
	printf("%d ", root->value);
	InOrder(root->right);
}

tnode* delNode(tnode* root, int value){
	if(root == NULL){
		return root;
	}
	
	if(value < root->value){
		root->left = delNode(root->left, value);
	}
	else if(value > root->value){
		root->right = delNode(root->right, value);
	}
	else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		else if(root->left != NULL){
			tnode* temp = root->left;
			
			while(temp->right != NULL){
				temp = temp->right;
			}
			root->value = temp->value;
			root->left = delNode(root->left, temp->value);
		}
		else if(root->right != NULL){
			tnode* temp = root->right;
			
			while(temp->left != NULL){
				temp = temp->left;
			}
			root->value = temp->value;
			root->right = delNode(root->right, temp->value);
		}
	}
	
	return root;
}

int main(){
	tnode* root = NULL;
	
	root = buildBST(root, 20);
	root = buildBST(root, 15);
	root = buildBST(root, 19);
	root = buildBST(root, 16);
	root = buildBST(root, 18);
	root = buildBST(root, 17);

	
	printf("%d\n", root->value);
	
//	int val = search(root, 11);
//	printf("%d\n", val);
	
	InOrder(root);
	printf("\n");
	delNode(root, 19);
	printf("\n");
	InOrder(root);
	
	return 0;
}
