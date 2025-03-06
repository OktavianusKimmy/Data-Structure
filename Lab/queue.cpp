#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// enqueue (push tail)
// dequeue (pop head)
// front (data paling awal)
// rear (data paling akhir)

struct Node{
	int priority;
	char nama[50];
	struct Node* next;	
	struct Node* prev;
}*head, *tail;

struct Node* CreateNewNode(int priority, char nama[]){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->priority = priority;
	strcpy(newNode->nama, nama);
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
};

void pushHead(int priority, char nama[]){
	struct Node* newNode = CreateNewNode(priority, nama);
	if(!head){
		head = tail = newNode;
	}
	else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pushTail(int priority, char nama[]){
	struct Node* newNode = CreateNewNode(priority, nama);
	if(!head){
		head = tail = newNode;
	}
	else{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

struct Node* popHead(){
	// Kondisi 1 : belum ada node
	if(head == NULL){
		return NULL;
	}
	// Kondisi 2 : ada 1 node
	else if(head == tail){
		struct Node* temp = head;
		head = tail = NULL;
		return temp;
	}
	// Kondisi 3 : ketika sudah ada > 1 node
	else{
		struct Node* temp = head;
		head = head->next;
		head->prev = NULL;
		return temp;
	}
}

void pushMid(int priority, char nama[]){
	if(head == NULL){
		struct Node* newNode = CreateNewNode(priority, nama);
		head = tail = newNode;
	}
	else if(priority < head->priority){
		pushHead(priority, nama);
	}
	else if(priority >= tail->priority){
		pushTail(priority, nama);
	}
	else{
		struct Node* newNode = CreateNewNode(priority, nama);
		struct Node* curr = head;
		while(curr != NULL && curr->priority <= newNode->priority){
			curr = curr->next;
		}
		newNode->prev = curr->prev;
		newNode->next = curr;
		
		newNode->prev->next = newNode;
		curr->prev = newNode;
	}
}

void getFront(){
	printf("%d %s\n", head->priority, head->nama);
}

void getRear(){
	printf("%d %s\n", tail->priority, tail->nama);
}

void forwardPrint(){
	struct Node* current = head;
	while(current != NULL){
		printf("%d %s <-> ", current->priority, current->nama);
		current = current->next;
	}
	printf("NULL\n");
}

int main(){
	pushMid(3, "Caca");
	pushMid(1, "Andi");
	pushMid(10, "Ong");
	pushMid(2, "Budi");
	pushMid(8, "Jag");
	pushMid(1, "Test");
//	popHead();
	forwardPrint();
	getFront();
//	getRear();
	return 0;
}
