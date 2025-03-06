#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc & free

struct Node{
	int id;
	char nama[50];
	struct Node* next;	
	struct Node* prev;
}*head, *tail;

struct Node* CreateNewNode(int id, char nama[]){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->id = id;
	strcpy(newNode->nama, nama);
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
};

void pushHead(int id, char nama[]){
	struct Node* newNode = CreateNewNode(id, nama);
	if(!head){
		head = tail = newNode;
	}
	else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pushTail(int id, char nama[]){
	struct Node* newNode = CreateNewNode(id, nama);
	if(!head){
		head = tail = newNode;
	}
	else{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

void pushMid(int id, char nama[]){
	if(head == NULL){
		struct Node* newNode = CreateNewNode(id, nama);
		head = tail = newNode;
	}
	else if(id < head->id){
		pushHead(id, nama);
	}
	else if(id >= tail->id){
		pushTail(id, nama);
	}
	else{
		struct Node* newNode = CreateNewNode(id, nama);
		struct Node* curr = head;
		while(curr != NULL && curr->id <= newNode->id){
			curr = curr->next;
		}
		newNode->prev = curr->prev;
		newNode->next = curr;
		
		newNode->prev->next = newNode;
		curr->prev = newNode;
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

struct Node* popTail(){
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
		struct Node* temp = tail;
		tail = tail->prev;
		tail->next = NULL;
		return temp;
	}
}

struct Node* popMid(int id){
	// Kondisi 1 : belum ada node
	if(head == NULL){
		return NULL;
	}
	// Kondisi 2 : id == head->id
	else if(id == head->id){
		return popHead();
	}
	// Kondisi 3 : id == tail->id
	else if(id == tail->id){
		return popTail();
	}
	// Kondisi 4 : data yang mau dihapus ada ditengah
	else{
		struct Node *temp = head;
		while(temp != NULL && temp->id != id){
			temp = temp->next;
		}
		if(temp != NULL){
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			return temp;
		}
		else{
			return NULL;
		}
	}
}

void forwardPrint(){
	struct Node* current = head;
	while(current != NULL){
		printf("%d %s <-> ", current->id, current->nama);
		current = current->next;
	}
	printf("NULL\n");
}

void backwardPrint(){
	struct Node* current = tail;
	while(current != NULL){
		printf("%d %s <-> ", current->id, current->nama);
		current = current->prev;
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
	
	struct Node* temp = popMid(8);
	if(temp != NULL){
		printf("Deleted %d %s\n", temp->id, temp->nama);
		free(temp);
	}
	else{
		puts("No data!");
	}
	puts("Setelah Delete: ");
	
	forwardPrint();
//	backwardPrint();
	return 0;
}
