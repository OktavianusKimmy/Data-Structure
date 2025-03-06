#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

struct Node{
	char plate[10];
	char name[20];
	char id[7];
	Node *next;
}*head[MAX_SIZE];

void push(char plate[], char name[], char id[], int index){
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->plate, plate);
	strcpy(newNode->name, name);
	strcpy(newNode->id, id);
	newNode->next = NULL;
	
	if(!head[index]){
		head[index] = newNode;
	}
	else{
		Node *temp = head[index];
		while(temp->next){
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

void pop(char plate[]){
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i] != NULL){
			Node *temp = head[i];
			if(strcmp(head[i]->plate, plate) == 0){
				printf("..\n");
				head[i] = head[i]->next;
				printf("Vehicle %s has exited.\n", temp->plate);
				free(temp);
				return;
			}
			else{
				while(temp){
					if(strcmp(temp->next->plate, plate) == 0){
						Node *temp2 = temp->next;
						temp->next = temp2->next;
						printf("Vehicle %s has exited.\n", temp2->plate);
						free(temp2);
						return;
					}
					temp = temp->next;
				}
			}
		}
	}
	printf("Error: No parking record found for vehicle %s\n", plate);
}

void regis();
void verify();
void view();
void remove();
void exit();

int main(){
	srand(time(NULL));
	do{
		int choice = -1;
		puts("Smart Parking Lot Management System");
		puts("1. Register Vehicle");
		puts("2. Verify Parking");
		puts("3. View All Parked Vehicles");
		puts("4. Remove Vehicle");
		puts("5. Exit");
		do{
			printf("Enter your choice: ");
			scanf("%d", &choice); getchar();
			switch (choice){
				case 1:
					regis();
					break;
				case 2:
					verify();
					break;
				case 3:
					view();
					break;
				case 4:
					remove();
					break;
				case 5:
					exit();
					return 0;
			}
		}while(choice < 1 || choice > 5);
		
	}while(1);
}

void regis(){
	char plate[10];
	char name[20];
	char id[7];
	int index;
	
	printf("Enter license plate number: ");
	scanf("%[^\n]", plate); getchar();
	
	printf("Enter owner name: ");
	scanf("%[^\n]", name); getchar();
	
	for(int i = 0; i<5; i++){
		int random = rand()%3;
		if(random == 0){
			id[i] = (rand() % 26) + 'a';
		}
		else if(random == 1){
			id[i] = (rand() % 26) + 'A';
		}
		else{
			id[i] = (rand() % 10) + '0';
		}
	}
	id[6] = '\0';
	
	int len = strlen(plate);
	int key = 0;
	for(int i = 0; i<len; i++){
		key += plate[i];
	}
	key *= key;
	char keyString[20];
	sprintf(keyString, "%d", key);
	int x = strlen(keyString);
	if(x % 2 == 0){
		// Genap ambil 2 tengah
		printf("%s\n", keyString);
		index = (keyString[(x/2)-1] - '0') * 10 + (keyString[(x/2)] - '0');
		printf("%d\n", index);
	}
	else{
		// Ganjil ambil 3 tengah
		printf("%s\n", keyString);
		index = (keyString[(x/2)-1] - '0') * 100 + (keyString[x/2] - '0') * 10 + (keyString[(x/2)+1] - '0');
		printf("%d\n", index);
	}
	
	push(plate, name, id, index%MAX_SIZE);
	printf("Parking successful!\n");
	printf("Your parking code: %s (Keep this for reference)\n", id);
}

void verify(){
	char id[10];
	printf("Enter parking CODE: ");
	scanf("%s", id); getchar();
	int found = 0;
	for(int i = 0; i<MAX_SIZE; i++){
		Node *temp = head[i];
		while(temp){
			if(strcmp(id, temp->id) == 0){
				found = 1;
				printf("Vehicle: %s\n", temp->plate);
				printf("Owner: %s\n", temp->name);
				return;
			}
			temp = temp->next;
		}
	}
	if(found == 0){
		printf("Error: No parking record found for CODE %s\n", id);
	}
}

void view(){
	printf("License Plate\tOwner\tCode\n");
	for(int i = 0; i<MAX_SIZE; i++){
		Node *temp = head[i];
		while(temp){
			printf("%s\t%s\t%s\n", temp->plate, temp->name, temp->id);
			temp = temp->next;
		}
	}
}

void remove(){
	char plate[10];
	printf("Enter license plate number to remove: ");
	scanf("%s", plate); getchar();
	
	pop(plate);
}

void exit(){
	puts("Exiting program...");
}
