#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

struct Node{
	char name[50];
	char no[20];
	char email[50];
	Node *next;
	Node *prev;
}*head[MAX];

int hash(const char *name){
	int key = 0;
	for(int i = 0; i<strlen(name); i++){
		key += name[i];
	}
	key *= key;
	char keyString[10000];
	sprintf(keyString, "%d", key);
	int len = strlen(keyString);
	char tengah[3];
	int valMid;
	if(len % 2 == 0){
		int mid = len/2;
		tengah[0] = keyString[mid-1];
		tengah[1] = keyString[mid];
		valMid = atoi(tengah);
	}
	else{
		int mid = len/2;
		tengah[0] = keyString[mid];
		valMid = atoi(tengah);
	}
//	printf("%s\n", keyString);
	return valMid;
}

void add();
void search();
void del();
int ada = 0;

int main(){
	int choice = -1;
	do{
		puts("App nomor telepon");
		puts("1. Add Contact");
		puts("2. Search Contact");
		puts("3. Delete Contact");
		puts("4. Exit");
		do{
			printf(">> ");
			scanf("%d", &choice); getchar();
			switch (choice){
				case 1:
					add();
					ada = 1;
					break;
				case 2:
					if(ada == 0){
						puts("Tidak ada list");
					}
					else{
						search();
					}
					break;
				case 3:
					if(ada == 0){
						puts("Tidak ada list");
					}
					else{
						del();
					}
					break;
				case 4:
					puts("Thankyou for using this program!");
					return 0;
			}
			if(choice < 1 || choice > 4){
				puts("Input 1-4");
			}
		}while(choice < 1 || choice > 4);
	}while(1);
}


void add(){
	Node *newNode = (Node*)malloc(sizeof(Node));
	printf("Input Contact Name : ");
	scanf("%[^\n]", newNode->name); getchar();
	
	printf("Input Contact Number : ");
	scanf("%s", newNode->no); getchar();
	
	printf("Input Contact Email : ");
	scanf("%s", newNode->email); getchar();
	
	newNode->next = NULL;
	newNode->prev = NULL;
	
	int pos = hash(newNode->name);
	
	if(head[pos] == NULL){
		head[pos] = newNode;
		return;
	}
	
	Node *temp = head[pos];
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
	puts("Contact has been added...");
	return;
}

void search(){
	for(int i = 0; i<100; i++){
		printf("%d. ", i);
		if(head[i] != NULL){
			Node *temp = head[i];
			while(temp != NULL){
				printf("%s -> ", temp->name);
				temp = temp->next;
			}
		}
		puts("NULL");
	}
	
	
	int coba = 1;
	while(coba == 1){
		char target[50];
		printf("Mau nomor siapa? [0 Cancel] : ");
		scanf("%[^\n]", target); getchar();
		if(strcmp(target, "0") == 0){
			puts("Okee... gajadi");
			return;
		}
		int flag = 0;
		for(int i = 0; i<100; i++){
			if(head[i] != NULL){
				Node *temp = head[i];
				while(temp != NULL){
					if(strcmp(temp->name, target) == 0){
						printf("%s\n", temp->name);
						printf("%s\n", temp->no);
						printf("%s\n", temp->email);
						getchar();
						flag = 1;
						coba = 0;
						break;
					}
					temp = temp->next;
				}
			}
			if(flag == 1) break;
		}
		do{
			puts("Namanya ngga ketemu!");
			printf("Mau coba lagi? [ 0(GA) | 1(MAU) ] : ");
			scanf("%d", &coba); getchar();
		} while(coba == 1 && flag == 0);
	}
	
}

void del(){
	for(int i = 0; i<100; i++){
		printf("%d. ", i);
		if(head[i] != NULL){
			Node *temp = head[i];
			while(temp != NULL){
				printf("%s -> ", temp->name);
				temp = temp->next;
			}
		}
		puts("NULL");
	}
	
	int coba = 1;
	while(coba == 1){
		char target[50];
		printf("Mau hapus siapa? [0 Cancel] : ");
		scanf("%[^\n]", target); getchar();
		if(strcmp(target, "0") == 0){
			puts("Okee... gajadi");
			return;
		}
		int flag = 0;
		for(int i = 0; i<100; i++){
			if(head[i] != NULL){
				Node *temp = head[i];
				while(temp != NULL){
					if(strcmp(temp->name, target) == 0){
						flag = 1;
						coba = 0;
						if(temp == head[i]){
							head[i] = head[i]->next;
							head[i]->prev = NULL;
							free(temp);
						}
						else if(temp->next == NULL){
							Node *temp2 = temp->prev;
							temp2->next = NULL;
							free(temp);
						}
						else{
							Node *temp2 = temp->prev;
							temp2->next = temp->next;
							free(temp);
						}
						puts("Contact has been deleted!");
						getchar();
						break;
					}
					temp = temp->next;
				}
			}
			if(flag == 1) break;
		}
		do{
			puts("Namanya ngga ketemu!");
			printf("Mau coba lagi? [ 0(GA) | 1(MAU) ] : ");
			scanf("%d", &coba); getchar();
		} while(coba == 1 && flag == 0);
	}
}

