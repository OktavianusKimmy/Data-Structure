#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char name[20];
	int fuel;
	int emergency;
	Node *next;
}*head, *tail;

void push(char name[], char fuel[], char emergency){
	int bensin = ((fuel[0] - '0') * 10) + (fuel[1] - '0');
	int prior = (emergency == '1') ? 1 : 0;
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->emergency = prior;
	newNode->fuel = bensin;
	strcpy(newNode->name, name);
	newNode->next = NULL;
	
	if(!head){
		head = tail = newNode;
	}
	else{
		if(prior == 1){
			if(head->emergency == 0){
				newNode->next = head;
				head = newNode;
			}
			else{
				if(head->fuel > bensin){
					newNode->next = head;
					head = newNode;
				}
				else{
					Node *temp = head;
					while(temp->next->fuel < bensin && temp->next->emergency != 0){
						temp = temp->next;
					}
					newNode->next = temp->next;
					temp->next = newNode;
				}
			}
		}
		else{
			Node *temp= head;
			int done = 0;
			while(temp->next && done == 0){
				if(temp->next->emergency == 0){
					if(temp->next->fuel > bensin){
						newNode->next = temp->next;
						temp->next = newNode;
						done = 1;
						break;
					}
					else if(temp->next->fuel == bensin){
						temp = temp->next;
						newNode->next = temp->next;
						temp->next = newNode;
						if(temp == tail) tail = newNode;
						done = 1;
						break;
					}
				}
				temp = temp->next;
			}
			if(done == 0){
				if(tail->fuel > bensin){
					newNode->next = tail;
					head = newNode;
				}
				else{
					tail->next = newNode;
					tail = newNode;
				}
			}
		}
	}
		
}

void pop(){
	Node *temp = head;
	head = head->next;
	free(temp);
}
/*
enqueue("Apollo", 75, 0) 
enqueue("Voyager", 50, 0) 
enqueue("Odyssey", 90, 1) 
enqueue("Endeavour", 15, 0)
enqueue("Pioneer", 80, 1) 
*/

void view(){
	Node *temp = head;
	while(temp){
		printf("%s -> ", temp->name);
		temp = temp->next;
	}
	printf("NULL");
	printf("\n");
}

void queue(int x){
	for(int i = 0; i<x; i++){
		int input = 0;
		do{
			char string[100];
			scanf("%[^\n]", string); getchar();
			char name[20];
			char fuel[5];
			char emergency;
			if(strncmp(string, "enqueue", 7) == 0){
				input = 1;
				int j = 9;
				int k = 0;
				while(string[j] != '"'){
					name[k] = string[j];
					k++;
					j++;
				}
				name[k] = '\0';
				k = 0;
				j += 3;
				while(string[j] != ','){
					fuel[k] = string[j];
					k++;
					j++;
				}
				fuel[k] = '\0';
				j += 2;
				emergency = string[j];
//				printf("%s %s %c\n", name, fuel, emergency);
				push(name, fuel, emergency);
				view();
			}
			else{
				puts("Wrong input, input again...");
				input = 0;
			}
		} while(input == 0);
	}
}

void dequeue(){
	if(!head){
		puts("No queue available!");
		return;
	}
	pop();
	view();
}

bool valid(char input[]){
	if(input[0] >= '1' && input[0] <= '9') return true;
	return false;
}

int main(){
	char input[10];
	do{
		do{
			scanf("%[^\n]", input); getchar();
			if(!(strcmp(input, "dequeue") == 0 || valid(input))){
				puts("Unknown input, input again...");
			}
			else if(strcmp(input, "dequeue") == 0){
				dequeue();
			}
			else{
				queue(atoi(input));
			}
		} while(!(strcmp(input, "dequeue") == 0 || valid(input)));
	}while(1);
	
	
	
}
