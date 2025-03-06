#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Stack = pushHead, popHead ATAU pushTail, popTail
Queue = pushHead, popTail ATAU pushTail, popHead
*/

struct Data{
	int key;
	char name[50];
	struct Data *next;
}*head, *tail;

struct Data *createData(int key, char *name){
	struct Data *newData = (struct Data*) malloc(sizeof(struct Data));
	newData->key = key;
	strcpy(newData->name, name);
	newData->next = NULL;
	
	return newData;
}

void pushHead(struct Data* newData){
	if(head == NULL){
		head= tail = newData;
	}
	else{
		newData->next = head;
		head = newData;
	}
}

int main(){
	
	
	return 0;
}
