#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define MAX_SIZE 50

struct Node{
	char name[50];
	char type[20];
	int duration;
	Node *next;
}*head[MAX_SIZE];

void insert();
void view();
void update();

int getHashKey(char name[]){
	int len = strlen(name);
	int key = 0;
	for(int i = 0; i<len; i++){
		key += name[i];
	}
	
	return key%MAX_SIZE;
}

void push(Node *newNode){
	int key = getHashKey(newNode->name);
	if(!head[key]){
		head[key] = newNode;
	}
	else{
		Node *temp = head[key];
		while(temp->next){
			if(strcmp(temp->next->name, newNode->name) < 0){
				temp = temp->next;
			} else break;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

int main(){
	do{
		puts("NeLson Garage");
		puts("1. Insert New Vehicle");
		puts("2. View All Vehicles");
		puts("3. Update Storage Duration");
		puts("4. Exit");
		int choice = -1;
		do{
			printf("Enter your choice: ");
			scanf("%d", &choice); getchar();
			switch (choice){
				case 1:
					insert();
					break;
				case 2:
					view();
					break;
				case 3:
					update();
					break;
				case 4:
					return 0;
			}
		}while(choice < 1 || choice > 4);
	}while(1);
}

bool valid2Word(char name[]){
	int len = strlen(name);
	int countSpace = 0;
	for(int i = 0; i<len; i++){
		if(name[i] == ' ') countSpace++;
	}
	
	if(countSpace == 1) return true;
	else return false;
}

bool validUnique(char name[]){
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			Node *temp = head[i];
			while(temp){
				if(strcmp(temp->name, name) == 0){
					return false;
				}
				temp = temp->next;
			}
		}
	}
	return true;
}

bool validInput(char name[]){
	int len = strlen(name);
	int idxSpace = -1;
	for(int i = 0; i<len; i++){
		if(name[i] == ' '){
			idxSpace = i;
			break;
		}
	}
	
	char kata1[20];
	char kata2[20];
	// Mindahin kata pertama
	int i;
	for(i = 0; i<idxSpace; i++){
		kata1[i] = name[i];
	}
	kata1[i] = '\0';
	
	// Mindahin kata kedua
	int j = 0;
	for(int i = idxSpace + 1; i<len; i++){
		kata2[j] = name[i];
		j++;
	}
	kata2[j] = '\0';
	
	if(strcmp(kata1, kata2) == 0) return false;
	else return true;
	
}

void insert(){
	char name[50];
	char type[20];
	int duration;
	
	do{
		printf("Insert new vehicle name: ");
		scanf("%[^\n]", name); getchar();
		if(!(valid2Word(name) && validUnique(name) && validInput(name))){
			puts("Input must consist of 2 words and unique");
		}
	} while(!(valid2Word(name) && validUnique(name) && validInput(name)));
	
	do{
		printf("Insert vehicle type [SUV | Sedan | Hatchback]: ");
		scanf("%[^\n]", type); getchar();
		if(!(strcmp(type, "SUV") == 0 || 
				strcmp(type, "Sedan") == 0 || 
				strcmp(type, "Hatchback") == 0)){
					puts("Input must be between [SUV | Sedan | Hatchback] (Case Sensitive)");
				}
	} while(!(strcmp(type, "SUV") == 0 || 
				strcmp(type, "Sedan") == 0 || 
				strcmp(type, "Hatchback") == 0));
				
	do{
		printf("Input duration: ");
		scanf("%d", &duration); getchar();
		if(duration < 1){
			puts("Duration must be greater than 0");
		}
	} while(duration < 1);
	
	printf("Vehicle Name\t : %s\n", name);
	printf("Vehicle Type\t : %s\n", type);
	printf("Duration\t: %d\n", duration);
	puts("--------------------------------------");
	char confirmation;
	do{
		printf("Are you sure want to insert this vehicle? [Y | N]: ");
		scanf("%c", &confirmation); getchar();
		if(!(confirmation == 'Y' || confirmation == 'N')){
			puts("Input must be between Y or N");
		}
	} while(!(confirmation == 'Y' || confirmation == 'N'));

	if(confirmation == 'Y'){
		Node *newNode = (Node*)malloc(sizeof(Node));
		strcpy(newNode->name, name);
		strcpy(newNode->type, type);
		newNode->duration = duration;
		newNode->next = NULL;
		push(newNode);
	}
	return;
}

void view(){
	int flag = 0;
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			flag = 1;
			Node *temp = head[i];
			while(temp){
				printf("Vehicle Name\t : %s\n", temp->name);
				printf("Vehicle Type\t : %s\n", temp->type);
				printf("Duration\t: %d\n", temp->duration);
				temp = temp->next;
			}
		}
	}
	if(flag == 0){
		puts("There is currently no vehicle");
	}
}

int validTarget(char target[]){
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			Node *temp = head[i];
			while(temp){
				if(strcmp(temp->name, target) == 0){
					
					return 1;
				}
				temp = temp->next;
			}
		}
	}
	return 0;
}

void update(){
	int flag = 0;
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			flag = 1;
			Node *temp = head[i];
			while(temp){
				printf("Vehicle Name\t : %s\n", temp->name);
				printf("Vehicle Type\t : %s\n", temp->type);
				printf("Duration\t: %d\n", temp->duration);
				temp = temp->next;
			}
		}
	}
	if(flag == 0){
		puts("There is currently no vehicle");
		return;
	}
	
	char target[50];
	do{
		printf("Input vehicle name to update: ");
		scanf("%[^\n]", target); getchar();
		if(validTarget(target) == 0){
			puts("There is no such vehicle!");
		}
	} while(validTarget(target) == 0);
	
	Node *ketemu;
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			Node *temp = head[i];
			while(temp){
				if(strcmp(temp->name, target) == 0) ketemu = temp;
				temp = temp->next;
			}
		}
	}
	
	int newDur;
	do{
		printf("Input new duration: ");
		scanf("%d", &newDur); getchar();
		if(newDur <= 0){
			puts("Duration must be greater than 0");
		}
	} while(newDur <= 0);
	ketemu->duration = newDur;
}
