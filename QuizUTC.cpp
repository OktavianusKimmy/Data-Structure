#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 10

struct Node{
	int id;
	int impact;
	int likelihood;
	Node *next;
}*queue;

struct Hash{
	int id;
	int impact;
	int likelihood;
	Hash *next;
}*head[MAX_SIZE];

bool critical(Node *temp){
	return temp->impact == 1 && temp->likelihood == 1;
}

bool high(Node *temp){
	return temp->impact == 1 && temp->likelihood == 0;
}

bool medium(Node *temp){
	return temp->impact == 0 && temp->likelihood == 1;
}

bool low(Node *temp){
	return temp->impact == 0 && temp->likelihood == 0;
}


void insert();
void viewQueue();
void call();
void viewProcess();

void push(int id, int impact, int likelihood){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->id = id;
	newNode->impact = impact;
	newNode->likelihood = likelihood;
	newNode->next = NULL;
	
	if(!queue){
		queue = newNode;
	}
	else if(critical(newNode)){ //critical
		if(!critical(queue)){
			newNode->next = queue;
			queue = newNode;
		}
		else{
			Node *temp = queue;
			while(critical(temp->next)){
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
			return;
		}
	}
	else if(high(newNode)){ //high
		if(medium(queue) || low(queue)){
			//push head
			newNode->next = queue;
			queue = newNode;
		}
		else{
			Node *temp = queue;
			while(high(temp->next) || critical(temp->next)){
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
		}
	}
	else if(medium(newNode)){ //medium
		if(low(queue)){
			newNode->next = queue;
			queue = newNode;
		}
		else{
			Node *temp = queue;
			while(high(temp->next) || critical(temp->next) || medium(temp->next)){
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
		}
	}
	else if(low(newNode)){ //low
		Node *temp = queue;
		while(temp->next){
			temp = temp->next;
		}
		temp->next = newNode;
	}
}



int main(){
	
	push(3001, 0, 0);
	push(3002, 1, 1);
	push(3003, 1, 0);
	push(3004, 0, 1);
	push(3005, 1, 1);
	
	viewQueue();
	puts("");
	
	call();
	call();
	
	viewQueue();
	puts("");
	
	viewProcess();
	
//	do{
//		int choice = -1;
//		do{
//			printf("1. Insert\n");
//			printf("2. View Queue\n");
//			printf("3. Call\n");
//			printf("4. View Processed\n");
//			printf("5. Exit\n");
//			scanf("%d", &choice); getchar();
//			
//			switch(choice){
//				case 1:
//					insert();
//					break;
//				case 2:
//					viewQueue();
//					break;
//				case 3:
//					call();
//					break;
//				case 4:
//					viewProcess();
//					break;
//				case 5:
//					return 0;
//			}
//		} while(choice < 1 || choice > 5);
//	} while(1);
}

void insert(){
	int jumlah;
	printf("How many do you want to insert?: ");
	scanf("%d", &jumlah); getchar();
	
	for(int i = 0; i<jumlah; i++){
		int id;
		int impactTemp;
		int likelihoodTemp;
		scanf("%d, %d, %d", &id, &impactTemp, &likelihoodTemp); getchar();
//		bool impact = (impactTemp == 1) ? true : false;
//		bool likelihood = (likelihoodTemp == 1) ? true : false;
		push(id, impactTemp, likelihoodTemp);
		viewQueue();
	}
}

void viewQueue(){
	puts("Vulnerability Queue");
	Node *temp = queue;
	while(temp){
		char status[10];
		if(critical(temp)) strcpy(status, "Critical");
		else if(high(temp)) strcpy(status, "High");
		else if(medium(temp)) strcpy(status, "Medium");
		else if(low(temp)) strcpy(status, "Low");
		
		printf("ID: %d - %s\n", temp->id, status);
		temp = temp->next;
	}
}

void call(){
	Node *temp = queue;
	
	
	int id = queue->id;
	int impact = queue->impact;
	int likelihood = queue->likelihood;
	queue = queue->next;
	free(temp);
	
	
	int index = 0;
	Hash *hash = (Hash*)malloc(sizeof(Hash));
	hash->id = id;
	hash->impact = impact;
	hash->likelihood = likelihood;
	hash->next = NULL;
	char keyString[10];
	sprintf(keyString, "%d", hash->id);
	int len = strlen(keyString);
	for(int i = 0; i<len; i++){
		index += keyString[i] - '0';
	}
	index = index % MAX_SIZE;
	
	head[index] = hash;
	
//	if(!head[index]){
//		head[index] = hash;
//	}
//	else{
//		Hash *temporary = head[index];
//		while(temporary->next){
//			temporary = temporary->next;
//		}
//		temporary->next = hash;
//	}
}

void viewProcess(){
	puts("Processing vulnerabilities...\n");
	
	puts("Strored Processed Vulnerabilities");
	
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i] == NULL) continue;
		else{
			
			Hash *s = head[i];
			while(s != NULL){
				printf("Index %d -> ID: %d\n", i, s->id);
				s = s->next;
			}
		}
	}
}
