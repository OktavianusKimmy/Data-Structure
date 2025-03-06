#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char nama[100];
	int prior;
	Node *next;
	Node *prev;
}*head, *tail;

// FASTTRACK = 1
// REGULER = 2

Node *createNode(char nama[], int prior){
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->nama, nama);
	newNode->prior = prior;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void push(char nama[], int prior){
	Node *newNode = createNode(nama, prior);
	if(!head){
		head = tail = newNode;
	}
	else if(head->prior == 2 && prior == 1){
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	else if(prior == 2){
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	else if(head->prior == 1 && prior == 1){
		Node *temp = head;
		while(temp->next->prior != 2){
			temp = temp->next;
		}
		newNode->next = temp->next;
		newNode->prev = temp;
		temp->next = newNode;
		temp = newNode->next;
		temp->prev = newNode;
	}
}

void regis();
void call();
void remove();

int main(){
	printf("Istana Boneka\n");
	printf("REGISTER || CALL || REMOVE\n");
	char input[10];
	int jumlah;
	while(1){
		do{
			printf(">> ");
			scanf("%s", input); getchar(); 
			if(strcmp(input, "REGISTER") == 0){
				regis();
			}
			else if(strcmp(input, "CALL") == 0){
				call();
			}
			else if(strcmp(input, "REMOVE") == 0){
				remove();
			}
		} while(!(strcmp(input, "REGISTER") == 0 || 
				strcmp(input, "CALL") == 0 || 
				strcmp(input, "REMOVE") == 0));
	}
}

void regis(){
	int jumlah;
	scanf("%d", &jumlah); getchar();
	for(int i = 0; i<jumlah; i++){
		char nama[100];
		char prio[20];
		int prior = -1;
		do{
			scanf("%s %s", nama, prio); getchar();
			if(!(strcmp(prio, "REGULER") == 0 || strcmp(prio, "FAST_TRACK") == 0)){
				puts("Insert between [REGULER | FAST_TRACK]");
			}
		} while(!(strcmp(prio, "REGULER") == 0 || strcmp(prio, "FAST_TRACK") == 0));
		
		if(strcmp(prio, "REGULER") == 0){
			prior = 2;
		}
		else{
			prior = 1;
		}
		push(nama, prior);
	}
	Node *temp = head;
	puts("No Name\tTicket");
	int i = 1;
	while(temp != NULL){
		printf("%d %s\t%s\n", i, temp->nama, (temp->prior == 1) ? "FAST_TRACK" : "REGULER");
		i++;
		temp = temp->next;
	}
}

void call(){
	for(int i = 0; i<4; i++){
		if(!head) break;
		Node *temp = head;
		head = head->next;
		printf("%s ", temp->nama);
		free(temp);
	}
	puts("got into the boat.");
	Node *temp = head;
	int i = 0;
	while(temp != NULL){
		i++;
		temp = temp->next;
	}
	printf("%d queues remaining.\n", i);
}

void remove(){
	int jumlah;
	scanf("%d", &jumlah); getchar();
	for(int i = 0; i<jumlah; i++){
		char nama[100];
		int flag = 0;
		scanf("%s", nama); getchar();
		Node *temp = head;
		do{
			if(strcmp(temp->nama, nama) == 0){
				flag = 1;
				Node *temp2 = temp->prev;
				temp2->next = temp->next;
				temp->next->prev = temp2;
				free(temp);
			}
			else{
				temp = temp->next;
			}
		}
		while(temp != NULL && flag == 0);
	}
	Node *temp = head;
	puts("No Name\tTicket");
	int i = 1;
	while(temp != NULL){
		printf("%d %s\t%s\n", i, temp->nama, (temp->prior == 1) ? "FAST_TRACK" : "REGULER");
		i++;
		temp = temp->next;
	}
}
