#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_table 10

struct Node{
	char name[40];
	Node *next;
}*head[max_table];

Node *createNewNode(const char *name){
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->next = NULL;
	return newNode;
}

int hash(const char *name){
	int key = 0;
	for(int i = 0; i<strlen(name); i++){
		key += name[i];
	}
	return key%max_table;
}

void push(const char *name){
	Node *newNode = createNewNode(name);
	//Calculate hash key
	int pos = hash(name);
	//Push
	if(head[pos] == NULL){
		head[pos] = newNode;
		return;
	}
	// ketika headnya ada (pushTail)
	Node *temp = head[pos];
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newNode;
	return;
}

void print(){
	for(int i = 0; i<max_table; i++){
		Node *temp = head[i];
		printf("%d: ", i);
		while(temp){
			printf("%s -> ", temp->name);
			temp = temp->next;
		}
		puts("NULL!");
	}
}

void pop(const char *name){
	int pos = hash(name);
	// Gaada head[pos]nya
	if(!head){
		puts("Gaada bos di hash table!");
		return;
	}
	// 
	else if(strcmp(head[pos]->name, name) == 0){
		Node *temp = head[pos];
		head[pos] = head[pos]->next;
		free(temp);
	}
	else{
		Node *temp = head[pos];
		while(temp->next != NULL && strcmp(temp->next->name, name) != 0){
			temp = temp->next;
		}
		if(temp->next != NULL){
			Node *temp2 = temp->next;
			temp->next = temp2->next;
			free(temp2);
		}
		else{
			puts("Gaada di hash tablenya!");
		}
	}
}

int main(){
	push("budi");
	push("lala");
	push("andi");
	push("agus");
	push("neo");
	push("ziva");
	push("jaden");
	push("nana");
	push("webe");
	print();
	pop("jaden");
	print();
	return 0;
}
