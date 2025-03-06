#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Pasien{
	char name[50];
	int age;
	int stat;
	struct Pasien *next;
	struct Pasien *prev;
}*head, *tail, *current;


void push(char nama[], int age, int stat){
	current = (struct Pasien*)malloc(sizeof(struct Pasien));
	strcpy(current->name, nama);
	current->age = age;
	current->stat = stat;
	current->next = NULL;
	current->prev = NULL;
	
	if(!head){
		head = tail = current;
	}
	else{
		struct Pasien *temp = head;
		// 1 1 2
		// 3
		while(temp != NULL){
			if(temp->stat > current->stat){
				break;
			}
			else{
				temp = temp->next;
			}
		}
		if(temp == head){
			current->next = head;
			head->prev = current;
			head = current;
		}
		else if(temp == NULL){
			tail->next = current;
			current->prev = tail;
			tail = current;
		}
		else{
			struct Pasien *temp2 = temp->prev;
			temp2->next = current;
			current->next = temp;
			current->prev = temp2;
			temp->prev = current;
		}
	}
}

void pop(){
	if(!head){
		puts("Tidak ada queue!");
	}
	else if(head->next != NULL){
		struct Pasien *temp = head;
		head = head->next;
		head->prev = NULL;
		printf("%s telah memasuki ruangan...\n", temp->name);
		free(temp);
		
		struct Pasien *temp2 = head;
		head = head->next;
		head->prev = NULL;
		printf("%s telah memasuki ruangan...\n", temp2->name);
		free(temp2);
	}
	else{
		struct Pasien *temp = head;
		head = head->next;
		head->prev = NULL;
		printf("%s telah memasuki ruangan...\n", temp->name);
		free(temp);
	}
}

void view(){
	if(!head){
		puts("There is no queue!");
		return;
	}
	Pasien *temp2 = head;
	puts("==========================");
	while(temp2 != NULL){
		printf("%s, %d, status : %d\n", temp2->name, temp2->age, temp2->stat);
		temp2 = temp2->next;
	}
	puts("==========================");
	puts("Stay Healthy!");
	puts("==========================");
}

void add();
void deq();

int main(){
	// Rizky
	push("Rizky", 33, 3);
	
	// Richard
	push("Richard", 26, 3);
	
	// Andi
	push("Andi", 16, 1);
	
	// Nur
	push("Nur", 74, 2);
	
	// Coki
	push("Coki", 66, 3);
	
	/*
	Andi
	Nur
	Rizki
	Richard
	Coki
	*/
	
	int choice = -1;
	do{
		puts("Antrian:");
		view();
		puts("\nRumah Sehat");
		puts("1. Tambah Pasien");
		puts("2. 2 Pasien Masuk");
		puts("3. Keluar Program");
		scanf("%d", &choice); getchar();
		switch (choice){
			case 1:
				add();
				break;
			case 2:
				pop();
				break;
			case 3:
				puts("Thankyou for using this program!");
				return 0;
		}
	}while(choice != 3);
	view();
	
}

void add(){
	char nama[50];
	int umur;
	int stat;
	
	printf("Nama : ");
	scanf("%[^\n]", nama); getchar();
	
	do{
		printf("Umur : ");
		scanf("%d", &umur); getchar();
	} while(umur <= 0);
	
	do{
		printf("Status [ 1 High | 2 Mid | 3 Low ] : ");
		scanf("%d", &stat); getchar();
	} while(stat <= 1 || stat >= 3);
	
	push(nama, umur, stat);
	printf("%s telah masuk kedalam antrian!\n", nama);
}

