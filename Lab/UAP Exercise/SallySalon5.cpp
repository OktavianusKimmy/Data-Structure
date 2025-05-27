#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char name[50];
	int price;
	char category[20];
	char available[20];
	int height;
	Node *left;
	Node *right;
};

void enterToCont(){
	puts("Press enter to continue..");
	getchar();
}

int max(int a, int b){
	return a > b ? a : b;
}

int height(Node *root){
	if(root == NULL) return 0;
	return root->height;
}

int getBalanceFactor(Node *root){
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

Node* insertAVL(Node *root, Node *newNode){
	if(root == NULL) return newNode;
	else if(strcmp(root->name, newNode->name) > 0) root->left = insertAVL(root->left, newNode);
	else if(strcmp(root->name, newNode->name) < 0) root->right = insertAVL(root->right, newNode);
	else return NULL;
	
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
		if(getBalanceFactor(root->right) <= 0) return leftRotate(root);
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}

bool validName(char name[]){
	if(strncmp("Sally ", name, 6) != 0) return false;
	if(strlen(name) < 5 || strlen(name) > 20) return false;
	return true;
}

Node* insert(Node *root){
	char name[50];
	int price;
	char category[20];
	char available[20];
	
	puts("INSERT NEW TREATMENT");
	do{
		printf("input new treatment name: ");
		scanf("%[^\n]", name); getchar();
	} while(!validName(name));
	
	do{
		printf("input treatment price [50.000 - 1.000.000]: ");
		scanf("%d", &price); getchar();
	} while(price < 50000 || price > 1000000);
	
	do{
		printf("input treatment category [Hair Care | Nail Care | Body Care]: ");
		scanf("%[^\n]", category); getchar();
	} while(!(strcmp(category, "Hair Care") == 0 || strcmp(category, "Nail Care") == 0 || strcmp(category, "Body Care") == 0));
	
	do{
		printf("input treatment availability for home service [Available | Unavailable]: ");
		scanf("%s", available); getchar();
	} while(!(strcmp(available, "Available") == 0 || strcmp(available, "Unavailable") == 0));
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->price = price;
	strcpy(newNode->category, category);
	strcpy(newNode->available, available);
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	
	root = insertAVL(root, newNode);
	puts("[New Treatment is successfully inserted]");
	enterToCont();
	return root;
}

void pre(Node *root){
	if(root != NULL){
		printf("|| %-20s || %-10s || %d || %-10s ||\n", root->name, root->category, root->price, root->available);
		pre(root->left);
		pre(root->right);
	}
}

void in(Node *root){
	if(root != NULL){
		in(root->left);
		printf("|| %-20s || %-10s || %d || %-10s ||\n", root->name, root->category, root->price, root->available);
		in(root->right);
	}
}

void post(Node *root){
	if(root != NULL){
		post(root->left);
		post(root->right);
		printf("|| %-20s || %-10s || %d || %-10s ||\n", root->name, root->category, root->price, root->available);
	}
}

void view(Node *root){
	if(root == NULL){
		puts("no data");
		enterToCont();
		return;
	}
	
	char input[10];
	do{
		printf("input view order [pre | in | post]: ");
		scanf("%s", input); getchar();
	} while(!(strcmp(input, "pre") == 0 || strcmp(input, "in") == 0 || strcmp(input, "post") == 0));
	
	puts("=========================================================");
	printf("|| %-20s || %-10s || Price || %-20s ||\n", "Treatment", "Category", "Home Service");
	puts("=========================================================");
	if(strcmp(input, "pre") == 0) pre(root);
	else if(strcmp(input, "in") == 0) in(root);
	else post(root);
	puts("=========================================================");
	enterToCont();
	return;
}

int check(Node *root, char target[]){
	if(root == NULL) return -1;
	else if(strcmp(root->name, target) > 0) int left = check(root->left, target);
	else if(strcmp(root->name, target) < 0) int right = check(root->right, target);
	else return 1;
}

Node* deleteAVL(Node *root, char target[]){
	if(root == NULL) return NULL;
	else if(strcmp(root->name, target) > 0) root->left = deleteAVL(root->left, target);
	else if(strcmp(root->name, target) < 0) root->right = deleteAVL(root->right, target);
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
			
			strcpy(root->name, temp->name);
			root->price = temp->price;
			strcpy(root->category, temp->category);
			strcpy(root->available, temp->available);
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
		if(getBalanceFactor(root->right) >= 0) return leftRotate(root);
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}

Node* del(Node *root){
	if(root == NULL){
		puts("no data");
		enterToCont();
		return NULL;
	}
	
	char target[30];
	puts("DELETE TREATMENT");
	printf("input treatment name to be deleted: ");
	scanf("%[^\n]", target); getchar();
	
	int ada = check(root, target);
	if(ada == -1){
		puts("no data");
		enterToCont();
		return root;
	}
	else{
		root = deleteAVL(root, target);
		puts("[Delete successfully]");
		enterToCont();
		return root;
	}
}

int main(){
	int choice = -1;
	Node *root = NULL;
	do{
		do{
			puts("Sally Salon");
			puts("Menu:");
			puts("1. View Available Treatment");
			puts("2. Insert New Treatment");
			puts("3. Delete Treatment");
			puts("4. Exit");
			puts("[1-4]");
			printf(">> ");
			scanf("%d", &choice); getchar();
		} while(choice < 1 || choice > 4);
		
		switch(choice){
			case 1:
				view(root);
				break;
			case 2:
				root = insert(root);
				break;
			case 3:
				root = del(root);
				break;
			case 4:
				return 0;
		}
	} while(1);
	
	
	return 0;
}
