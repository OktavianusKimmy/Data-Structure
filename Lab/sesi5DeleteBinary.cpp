#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
	int id;
	char name[101];
	struct Student *left;
	struct Student *right;
};

Student *createStudent(int id, char *name){
	Student *newStudent = (Student*)malloc(sizeof(Student));
	newStudent->id = id;
	strcpy(newStudent->name, name);
	newStudent->left = NULL;
	newStudent->right = NULL;
	return newStudent;
}

Student *insert(Student *root, int id, char *name){
//	Case 1: kalo tree belom kebuat, kita bikin root nodenya saja
	if(root == NULL){
		return createStudent(id, name);
	}
//	Case 2 : ID yang kita mau inser > current node punya ID
	else if(id > root->id){
		root->right = insert(root->right, id, name);
	}
//	Case 3 : ID yang kita mau insert < current node punya ID
	else if(id < root->id){
		root->left = insert(root->left, id, name);
	}
//	Case 4 : Kalo valuenya udah ada (duplicate), kita return nodenya saja
	return root;
}

void inorder(Student *root){
	if(root == NULL) return;
	inorder(root->left);
	printf("Student ID : %d, Name: %s\n", root->id, root->name);
	inorder(root->right);
}

Student *search(Student *curr, int id){
	// Case 1 : Kalo Search ga ketemu
	if(curr == NULL){
		puts("Not Found!");
		return NULL;
	}
	
	// Case 2 : Kalo Search KETEMU
	if(curr->id == id){
		puts("Found!");
		return curr;
	}
	
	// Case 3 : kalo id yang mau di search itu lbh gede dr current id
	if(id > curr->id){
		return search(curr->right, id);
	}
	// Case 4 : kalo id yang mau di search itu lbh kecil dr current id
	else{
		return search(curr->left, id);
	}
}

Student *update(Student *curr, int id, char *newName){
	// Case 1 : Kalo Search ga ketemu
	if(curr == NULL){
		puts("Not Found!");
		return NULL;
	}
	
	// Case 2 : Kalo Search KETEMU
	if(curr->id == id){
		puts("Found!");
		strcpy(curr->name, newName);
		return curr;
	}
	
	// Case 3 : kalo id yang mau di search itu lbh gede dr current id
	if(id > curr->id){
		return update(curr->right, id, newName);
	}
	// Case 4 : kalo id yang mau di search itu lbh kecil dr current id
	else{
		return update(curr->left, id, newName);
	}
}

Student *findSuccessor(Student *curr){
	while(curr->left){
		curr = curr->left;
	}
	return curr;
}

Student *del(Student *curr, int id){
	if(curr == NULL){
		puts("Not Found!");
		return NULL;
	}
	else if(id < curr->id){
		curr->left = del(curr->left, id);
	}
	else if(id > curr->id){
		curr->right = del(curr->right, id);
	}
	
	else{
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			return NULL;
		}
		else if(curr->right != NULL && curr->left == NULL){
			Student *temp = curr->right;
			free(curr);
			return temp;
		}
		else if(curr->left != NULL && curr->right == NULL){
			Student *temp = curr->left;
			free(curr);
			return temp;
		}
		else{
			Student *successor = findSuccessor(curr->right);
			
			curr->id = successor->id;
			strcpy(curr->name, successor->name);
			
			curr->right = del(curr->right, successor->id);
			
			return curr;
		}
	}
	
	return curr;
}

Student *deleteAll(Student *root){
	while(root){
		root = del(root, root->id);
	}
	return root;
}

int main(){
	
	Student *root = NULL;
	
	// Insertion
	puts("Inserting: ");
	
	root = insert(root, 100, "Louis");
	root = insert(root, 101, "Brandon");
	root = insert(root, 90, "Angeline");
	root = insert(root, 103, "Bryant");
	root = insert(root, 77, "Calvin");
	root = insert(root, 95, "Giselle");
	root = insert(root, 94, "Nathan");
	root = insert(root, 93, "Marchelle");
	puts("Insert Sucessfull!");
	
	/*
	Inorder :
	1. Left
	2. Print
	3. Right
	
	Preorder:
	1. Print
	2. Left
	3. Right
	
	Postorder:
	1. Left
	2. Right
	3. Print
	*/
	
	// Traversal
	puts("\nInorder Traversal:");
	inorder(root);
	
	// Searching
	puts("\nSearching");
	Student *searchedStudent = search(root, 3);
	if(searchedStudent != NULL){
		printf("Found Student with id %d and name %s\n", searchedStudent->id, searchedStudent->name);
	}
	
	// Updating
	puts("\nUpdating");
	Student *updatedStudent = update(root, 3, "tommy");
	if(updatedStudent != NULL){
		printf("Updated Student with id %d, new Name is %s\n", updatedStudent->id, updatedStudent->name);
	}
	
	
	// Deleting
	root = del(root, 100);
	root = del(root, 95);
	
	root = deleteAll(root);

	
	// Traversal
	puts("\nInorder Traversal:");
	inorder(root);
	
	return 0;
}
