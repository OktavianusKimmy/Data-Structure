#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Med{
	char name[100];
	float price;
	int quantity;
	int height;
	Med *left;
	Med *right;
};

int check(Med *root, char name[]){
	if(root == NULL) return -1;
	else if(strcmp(root->name, name) > 0) int left = check(root->left, name);
	else if(strcmp(root->name, name) < 0) int right = check(root->right, name);
	else return 1;
}

bool validMed(Med *root, char name[]){
	if(strlen(name) == 0){
		puts("Name must not empty");
		return false;
	}
	// buat code kalo dia gaboleh sama kaya yg ud ada
	
	int ada = check(root, name);
	
	if(ada == 1){
		puts("Name already exist!");
		return false;
	}
	
	return true;
}

int max(int a, int b){
	return a > b ? a : b;
}

int height(Med *root){
	if(root == NULL) return 0;
	return root->height;
}

int getBalanceFactor(Med *root){
	return height(root->left) - height(root->right);
}

Med* leftRotate(Med *x){
	Med *y = x->right;
	Med *z = y->left;
	
	y->left = x;
	x->right = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Med* rightRotate(Med *x){
	Med *y = x->left;
	Med *z = y->right;
	
	y->right = x;
	x->left = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

Med* insertAVL(Med *root, Med *newNode){
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
		if(getBalanceFactor(root->right) >= 0) return leftRotate(root);
		else{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	
	return root;
}

Med* insert(Med *root){
	char name[100];
	float price;
	int quantity;
	
	do{
		printf("Input Medicine name: ");
		scanf("%[^\n]", name); getchar();
	} while(!validMed(root, name));
	
	do{
		printf("Input Medicine price: ");
		scanf("%f", &price); getchar();
		if(price <= 0) puts("Invalid price!");
	} while(price <= 0);
	
	do{
		printf("Input Medicine qty: ");
		scanf("%d", &quantity); getchar();
		if(quantity < 0) puts("Invalid Quantity");
	} while(quantity < 0);
	
	Med *newNode = (Med*)malloc(sizeof(Med));
	strcpy(newNode->name, name);
	newNode->price = price;
	newNode->quantity = quantity;
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	
	root = insertAVL(root, newNode);
	printf("[%s] added (Price: $%.2f, Qty: %d)\n", name, price, quantity);
	return root;
}

void pre(Med *root){
	if(root != NULL){
		printf("[%s] $%.2f (Qty: %d)\n", root->name, root->price, root->quantity);
		pre(root->left);
		pre(root->right);
	}
}

void view(Med *root){
	if(root == NULL){
		puts("No medicines in inventory");
		return;
	}
	puts("Medicines:");
	pre(root);
}

Med* deleteAVL(Med *root, char target[]){
	if(root == NULL) return NULL;
	else if(strcmp(root->name, target) > 0) root->left = deleteAVL(root->left, target);
	else if(strcmp(root->name, target) < 0) root->right = deleteAVL(root->right, target);
	else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		}
		else if(root->left == NULL || root->right == NULL){
			Med *temp = root->left ? root->left : root->right;
			free(root);
			return temp;
		}
		else{
			Med *temp = root->left;
			while(temp->right){
				temp = temp->right;
			}
			
			strcpy(root->name, temp->name);
			root->price = temp->price;
			root->quantity = temp->quantity;
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

Med* del(Med *root){
	char target[100];
	printf("Input Medicine name to delete: ");
	scanf("%[^\n]", target); getchar();
	
	int ada = check(root, target);
	if(ada == -1){
		puts("Medicine not found!");
		return root;
	}
	printf("[%s] deleted\n", target);
	root = deleteAVL(root, target);
	return root;
}

int main(){
	Med *root = NULL;
	int choice = -1;
	do{
		do{
			puts("1. Insert medicine");
			puts("2. View medicines");
			puts("3. Delete medicine");
			puts("4. Exit");
			printf(">> ");
			scanf("%d", &choice); getchar();
		} while(choice < 1 || choice > 4);
		
		switch(choice){
			case 1:
				root = insert(root);
				break;
			case 2:
				view(root);
				break;
			case 3:
				root = del(root);
				break;
			case 4:
				return 0;
		}
		
	}while(1);
}
