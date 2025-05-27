#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char name[100];
	int price;
	char category[30];
	char avail[20];
	int height;
	Node *left;
	Node *right;
};

void pre(Node *root){
	if(root != NULL){
		printf("|| %-20s || %-20s || %d\t || %20s ||\n", root->name, root->category, root->price, root->avail);
		pre(root->left);
		pre(root->right);
	}
}

void in(Node *root){
	if(root != NULL){
		in(root->left);
		printf("|| %-20s || %-20s || %d\t || %20s ||\n", root->name, root->category, root->price, root->avail);
		in(root->right);
	}
}

void post(Node *root){
	if(root != NULL){
		post(root->left);
		post(root->right);
		printf("|| %-20s || %-20s || %d\t || %20s ||\n", root->name, root->category, root->price, root->avail);
	}
}

Node* view(Node* node){
	if(node == NULL){
		printf("no data\n");
		return NULL;
	}
	
	char input[10];
	do{
		printf("input view order [pre | in | post]: ");
		scanf("%s", input); getchar();
	} while(!(strcmp(input, "pre") == 0 || strcmp(input, "in") == 0 || strcmp(input, "post") == 0));
	
	printf("|| %-20s || %-20s || %-10s\t || %20s ||\n", "Treatment", "Category", "Price", "Home Service");
	if(strcmp(input, "pre") == 0){
		pre(node);
	}
	else if(strcmp(input, "in") == 0){
		in(node);
	}
	else{
		post(node);
	}
	
}

int height(Node* root){
	if(root == NULL) return 0;
	return root->height;
}

int max(int a, int b){
	return a > b ? a : b;
}

int getBalanceFactor(Node* root){
	if(root == NULL) return 0;
	return height(root->left) - height(root->right);
}

Node* leftRotate(Node* x){
	Node *y = x->right;
	Node *z = y->left;
	
	y->left = x;
	x->right = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Node* rightRotate(Node* x){
	Node *y = x->left;
	Node *z = y->right;
	
	y->right = x;
	x->left = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Node* insertAVL(Node *root, Node *newNode){
	if(root == NULL) return newNode;
	else if(strcmp(root->name, newNode->name) > 0) root->left = insertAVL(root->left, newNode);
	else if(strcmp(root->name, newNode->name) < 0) root->right = insertAVL(root->right, newNode);
	else return root;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root); // left left
		else{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if(balance < -1){
		if(getBalanceFactor(root->right) >= 0) return leftRotate(root); // right right
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	
	return root;
}

int validateName(char name[]){
	if(strncmp(name, "Sally ", 6) != 0) return 0;
	if(strlen(name) - 6 < 5 || strlen(name) - 6 > 20) return 0;
	if(name[6] == ' ') return 0;
	else return 1;
}

Node* insert(Node *root){
	char name[100];
	int price;
	char category[30];
	char avail[20];
	
	do{
		printf("input new treatment name: ");
		scanf("%[^\n]", name); getchar();
	} while(validateName(name) == 0);
	
	do{
		printf("input treatment price [50000 - 1000000]: ");
		scanf("%d", &price); getchar();
	} while(price < 50000 || price > 1000000);
	
	do{
		printf("input treatment category [Hair Care | Nail Care | Body Care]: ");
		scanf("%[^\n]", category); getchar();
	} while(!(strcmp(category, "Hair Care") == 0 || strcmp(category, "Nail Care") == 0 || strcmp(category, "Body Care") == 0));
	
	do{
		printf("input treatment availibility for home service [Available | Unavailable]: ");
		scanf("%[^\n]", avail); getchar();
	} while(!(strcmp(avail, "Available") == 0 || strcmp(avail, "Unavailable") == 0));
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	strcpy(newNode->category, category);
	strcpy(newNode->avail, avail);
	newNode->price = price;
	newNode->left = NULL;
	newNode->right = NULL;
	
	root = insertAVL(root, newNode);
	return root;
}

Node* validTarget(Node* root, char target[]){
	if(root == NULL) return NULL;
	else if(strcmp(root->name, target) > 0) root->left = validTarget(root->left, target);
	else if(strcmp(root->name, target) < 0) root->right = validTarget(root->right, target);
	else return root;
}

Node* deleteAVL(Node* root, char target[]){
	if(strcmp(root->name, target) == 0){
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
			
			//copas nilai predecessor
			strcpy(root->name, temp->name);
			strcpy(root->category, temp->category);
			strcpy(root->avail, root->avail);
			root->price = temp->price;
			
			root->left = deleteAVL(root->left, temp->name);
		}
	}
	else if(strcmp(root->name, target) > 0) root->left = validTarget(root->left, target);
	else if(strcmp(root->name, target) < 0) root->right = validTarget(root->right, target);
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalanceFactor(root);
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0) return rightRotate(root); // left left
		else{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if(balance < -1){
		if(getBalanceFactor(root->right) >= 0) return leftRotate(root); // right right
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	
	return root;
}

Node* del(Node* root){
	if(root == NULL){
		printf("no data\n");
		return root;
	}
	
	char target[100];
	printf("DELETE TREATMENT\n");
	printf("input treatment name to be deleted: ");
	scanf("%[^\n]", target); getchar();
	
	if(validTarget(root, target) != NULL){
		root = deleteAVL(root, target);
		printf("\n[Delete successfully]\n");
	}
	else{
		printf("\nData not found\n");
	}
	return root;
}

int main(){
	Node* node = NULL;
	do{
		int choice = -1;
		do{
			puts("===================");
			puts("|   Sally Salon   |");
			puts("===================");
			puts("Menu:");
			puts("1. View Available Treatment");
			puts("2. Insert New Treatment");
			puts("3. Delete Treatment");
			puts("4. Exit");
			puts("[1-4]");
			printf(">> ");
			scanf("%d", &choice); getchar();
		} while(choice < 1 || choice > 4);
		
		switch (choice){
			case 1:
				node = view(node);
				break;
			case 2:
				node = insert(node);
				break;
			case 3:
				node = del(node);
				break;
			case 4:
				return 0;
		}
	} while(1);
	
	return 0;
}
