#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int count = 1;
int money = 1400;

struct Node{
	int ID;
	char name[25];
	int price;
	struct Node *next;
} *head, *tail, *current;

void push(char name[]){
	current = (struct Node*)malloc(sizeof(struct Node));
	
	// assign attribute buat cardnya
	strcpy(current->name, name);
	current->ID = count;
	count++;
	current->price = rand() % 10000 + 1000;
	current->next = NULL;
	
	// masukin ke deretnya
	if(!head){ // kalo belom ada deret samsek
		head = tail = current;
	}
	else if(strcmp(name, head->name) < 0){ // push head
		current->next = head;
		head = current;
	}
	else if(strcmp(name, tail->name) > 0){ // push tail
		tail->next = current;
		tail = current;
	}
	else{ // push mid (masukin di tengah)
		Node *temp = head;
		while(strcmp(temp->next->name, name) < 0){
			temp = temp->next;
		}
		current->next = temp->next;
		temp->next = current;
	}
}

void pop(char name[]){
	if(head == NULL){
		return;
	}
	Node *temp = head;
	if(strcmp(head->name, name) == 0){ // pop head
		head = head->next;
		temp->next = NULL;
		free(temp);
	}
	else if(strcmp(tail->name, name) == 0){ // pop tail
		while(strcmp(temp->next->name, name) != 0){
			temp = temp->next;
		}
		tail = temp;
		temp = temp->next;
		temp->next = NULL;
		free(temp);
	}
	else{
		while(strcmp(temp->next->name, name) != 0){
			temp = temp->next;
		}
		Node *current = temp->next;
		temp->next = current->next;
		current->next = NULL;
		free(current);
	}
}

void buy();
void show();
void change();
void del();

int main(){
	// Inisiasi card awal
	srand(time(NULL));
	char CardAwal[20];
	strcpy(CardAwal, "Vulpix");
	push(CardAwal);
	
	strcpy(CardAwal, "Diglett");
	push(CardAwal);
	
	strcpy(CardAwal, "Zubat");
	push(CardAwal);
	
	strcpy(CardAwal, "Nidoran");
	push(CardAwal);
	
	do{
		int choice = -1;
		puts("Card Exchange");
		puts("===============================");
		puts("1. Buy Card");
		puts("2. Show Card");
		puts("3. Change Card");
		puts("4. Delete Card");
		puts("5. Exit");
		do{
			printf(">> ");
			scanf("%d", &choice); getchar();
			switch (choice){
				case 1:
					buy();
					break;
				case 2:
					show();
					break;
				case 3:
					change();
					break;
				case 4:
					del();
					break;
				case 5:
					puts("Thankyou for using this program!");
					return 0;
			}
			if(!(choice >= 1 && choice <= 5)){
				puts("Invalid input");
			}
		} while(!(choice >= 1 && choice <= 5));
	} while(1);
}

void buy(){
	char name[25];
	do{
		printf("Input card name you want to buy : ");
		scanf("%s", name); getchar();
		if(strlen(name) > 25){
			puts("Card name must less than 25 characters");
		}
	} while(strlen(name) > 25);
	
	printf("%s has been bought!\n", name);
	push(name);
	printf("=========================\n");
	return;
}

void show(){
	Node *temp = head;
	while (head != NULL) {
        printf("ID  : %d\nName : %s\nPrice: %d\n", head->ID, head->name, head->price);
        head = head->next;
        printf("---------------------------------\n");
    }
    head = temp;
}

void change(){
	char name[25];
	do{
		printf("Input card name you want to change : ");
		scanf("%s", name); getchar();
		if(strlen(name) > 25){
			puts("Card name must less than 25 characters");
		}
	} while(strlen(name) > 25);
	printf("%s has been bought!\n", name);
	push(name);
	
	show();
	
	char del[25];
	do{
		printf("Input card name you want to delete : ");
		scanf("%s", del); getchar();
		
		Node *temp = head;
		while (temp != NULL) {
			if(temp)
	        printf("ID  : %d\nName : %s\nPrice: %d\n", temp->ID, temp->name, temp->price);
	        temp = temp->next;
	        printf("---------------------------------\n");
	    }
		
		if(flag == 0){
			puts("Gaada kartunya");
		}
	} while(flag == 0);
}

void del(){
	
}
