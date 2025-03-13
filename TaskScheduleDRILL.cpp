#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct Node{
	char taskName[100];
	int priority;
	Node *next;
}*head[MAX_SIZE];

struct Prior{
	char taskName[100];
	int priority;
	Prior *next;
}*queue;

bool validChoice(char choice[]){
	if(
	strcmp(choice, "ADD") == 0 || 
	strcmp(choice, "EXECUTE") == 0 ||
	strcmp(choice, "PRINT_HASH_TABLE") == 0
	) return true;
	else return false;
}

void add();
void execute();
void print();

int main(){
	do{
		printf("ADD | EXECUTE | PRINT_HASH_TABLE\n");
		char choice[20];
		do{
			scanf("%s", choice); getchar();
			if(strcmp(choice, "ADD") == 0){
				add();
				break;
			}
			else if(strcmp(choice, "EXECUTE") == 0){
				execute();
				break;
			}
			else if(strcmp(choice, "PRINT_HASH_TABLE") == 0){
				print();
				break;
			}
			else{
				puts("Invalid Input!");
			}
		}while(!validChoice(choice));
	} while(1);
}


void add(){
	char taskName[100];
	int priority;
	
	scanf("%s %d", taskName, &priority); getchar();
	
	Prior *newPrior = (Prior*)malloc(sizeof(Prior));
	strcpy(newPrior->taskName, taskName);
	newPrior->priority = priority;
	
	if(!queue){
		queue = newPrior;
	}
	else if(queue->priority > priority){
		newPrior->next = queue;
		queue = newPrior;
	}
	else{
		Prior *temp = queue;
		while(temp->next != NULL && temp->next->priority <= priority){
			temp = temp->next;
		}
		if(temp->next == NULL){
			temp->next = newPrior;
		}
		else{
			newPrior->next = temp->next;
			temp->next = newPrior;
		}
	}
}

int getKey(char taskName[]){
	int key = 0;
	int len = strlen(taskName);
	for(int i = 0; i<len; i++){
		key += taskName[i];
	}
	char keyString[20];
	sprintf(keyString, "%d", key);
	int len2 = strlen(keyString);
	key = (keyString[len2-2] * 10) + (keyString[len2-1]);
	
	printf("%d\n", key);
	return key % MAX_SIZE;
}

void execute(){
	char taskName[100];
	int priority;
	
	strcpy(taskName, queue->taskName);
	priority = queue->priority;
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->taskName, taskName);
	newNode->priority = priority;
	newNode->next = NULL;
	
	int index = getKey(taskName);
	
	printf("Executed: %s (Stored in Hash Table at index %d)\n", taskName, index);
	
	queue = queue->next;
	
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

void print(){
	puts("Hash Table State:");
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			printf("Index %d -> ", i);
			Node *temp = head[i];
			while(temp){
				printf("%s -> ", temp->taskName);
				temp = temp->next;
			}
			printf("NULL\n");
		}
	}
}
