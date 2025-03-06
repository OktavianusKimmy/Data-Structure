#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define MAX_SIZE 100

struct Node{
	char name[35];
	char LibId[10];
	char title[55];
	int duration;
	char id[10];
	Node *next;
}*head[MAX_SIZE];

void print(){
	puts("==================================");
	puts("BookHaven Library Management");
	puts("==================================");
	puts("1. Borrow a Book\n2. View Borrowed Books\n3. Return a Book\n4. Exit\n");
	puts("==================================");
}

void enter(){
	printf("Press ENTER to Continue...");
	getchar();
}

void borrow();
void view();
void retur();

int main(){
	srand(time(NULL));
	do{
		system("cls");
		int choice = -1;
		print();
		do{
			printf("Enter your choice: ");
			scanf("%d", &choice); getchar();
			switch(choice){
				case 1:
					borrow();
					enter();
					break;
				case 2:
					view();
					enter();
					break;
				case 3:
					retur();
					enter();
					break;
				case 4:
					return 0;
			} 
		} while(choice < 1 || choice > 4);
	} while(1);
}

bool validID(char LibId[]){
	if(strncmp(LibId, "LIB-", 4) != 0){
		return false;
	}
	
	for(int i = 4; i<9; i++){
		if(LibId[i] < '0' || LibId[i] > '9') return false;
	}
	return true;
}

void borrow(){
	char name[35];
	char LibId[10];
	char title[55];
	int duration;
	char id[10];
	do{
		printf("Enter your full name: ");
		scanf("%[^\n]", name); getchar();
		if(!(strlen(name) >= 3 && strlen(name) <= 50)){
			puts("Input must be between 3 and 30 characters");
		}
	} while(!(strlen(name) >= 3 && strlen(name) <= 50));
	
	do{
		printf("Enter your library ID (format: LIB-xxxxx): ");
		scanf("%s", LibId); getchar();
		if(!validID(LibId)){
			puts("Input must start with \"LIB-\" followed by exactly 5 digits");
		}
	} while(!validID(LibId));
	
	do{
		printf("Enter the book title: ");
		scanf("%[^\n]", title); getchar();
		if(strlen(title) < 3 || strlen(title) > 30){
			puts("Book Title must be between 3 and 30 characters");
		}
	} while(strlen(title) < 3 || strlen(title) > 30);
	
	do{
		printf("Enter borrowing duration (1-30 days): ");
		scanf("%d", &duration); getchar();
		if(duration < 1 || duration > 30){
			puts("Borrowing duration must be between 1 and 30 days");
		}
	} while(duration < 1 || duration > 30);
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	strcpy(newNode->LibId, LibId);
	strcpy(newNode->title, title);
	newNode->duration = duration;
	newNode->next = NULL;
	
	sprintf(id, "%c%c%c%c%c", toupper(title[0]), 
							toupper(title[1]),
							rand() % 10 + '0',
							rand() % 10 + '0',
							rand() % 10 + '0');
	
	strcpy(newNode->id, id);
	//HASHING
	long long int key = 0;
	key += (id[2] - '0') * 100;
	key += (id[3] - '0') * 10;
	key += (id[4] - '0');
	
	key *= key;
	
	char keyString[100];
	sprintf(keyString, "%d", key);
	int len = strlen(keyString);
	if(len % 2 == 0){
		// Genap
		key = (keyString[(len/2) - 1] - '0') * 10;
		key += (keyString[(len/2)] - '0');
	}
	else{
		key += (keyString[(len/2)] - '0');
	}
	key %= MAX_SIZE;
	
	// Pushing
	
	if(!head[key]){
		head[key] = newNode;
	}
	else{
		Node *temp = head[key];
		while(temp->next){
			temp = temp->next;
		}
		temp->next = newNode;
	}
	
	puts("Book Borrowed Successfully!");
	printf("Borrowing ID\t: %s\n", id);
	printf("Borrower Name\t: %s\n", name);
	printf("Library ID\t: %s\n", LibId);
	printf("Book Title\t: %s\n", title);
	printf("Duration\t: %d %s\n", duration, duration == 1 ? "day\n" : "days\n");
}

bool cekView(){
	for(int i = 0; i<MAX_SIZE; i++){
		Node *temp = head[i];
		while(temp){
			return true;
		}
	}
	return false;
}

void view(){
	if(cekView()){
		puts("==================================");
		puts("Boorowed Books List");
		puts("==================================");
		for(int i = 0; i<MAX_SIZE; i++){
			Node *temp = head[i];
			while(temp){
				printf("Borrowing ID\t: %s\n", temp->id);
				printf("Borrower Name\t: %s\n", temp->name);
				printf("Library ID\t: %s\n", temp->LibId);
				printf("Book Title\t: %s\n", temp->title);
				printf("Duration\t: %d %s\n", temp->duration, temp->duration == 1 ? "day\n" : "days\n");
				puts("----------------------------------");
				temp = temp->next;
			}
		}
	}
	else{
		puts("========================================");
		puts("No books borrowed yet.");
		puts("========================================");
	}
}

void retur(){
	if(!cekView()){
		puts("No books found.");
	}
	else{
		view();
		char target[10];
		printf("Enter Borrowing ID to return: ");
		scanf("%s", target); getchar();
		
		int found = 0;
		for(int i = 0; i<MAX_SIZE; i++){
			if(head[i] != NULL){
				if(strcmp(head[i]->id, target) == 0){
					Node *temp = head[i];
					head[i] = head[i]->next;
					printf("Borrowing ID : %s has been removed.\n", temp->id);
					free(temp);
					found = 1;
					break;
				}
				else{
					Node *temp = head[i];
					// Cek sebelum target
					while(temp->next != NULL){
						if(strcmp(temp->next->id, target) == 0){
							Node *temp2 = temp->next;
							temp->next = temp2->next;
							printf("Borrowing ID : %s has been removed.\n", temp2->id);
							temp2->next = NULL;
							free(temp2);
							found = 1;
							break;
						}
						temp = temp->next;
					}
				}
			}
		}
		if(found == 0){
			puts("Error : ID not found!");
		}
	}
}
