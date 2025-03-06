#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count = 3;

struct Lagu{
	char judul[25];
	struct Lagu *next;
	struct Lagu *prev;
}*head, *tail, *current;

void push(char title[]){
	current = (struct Lagu*)malloc(sizeof(struct Lagu));
	strcpy(current->judul, title);
	current->next = NULL;
	current->prev = NULL;
	
	if(!head){
		head = tail = current;
	}
	else{
		tail->next = current;
		current->prev = tail;
		tail = current;
	}
}

int flag = 0;

void pop(char title[]){
	if(head == NULL){
		puts("There is no queue to delete!");
		return;
	}
	

	struct Lagu *temp;
	
	if(strcmp(head->judul, title) == 0){ // pop head
		temp = head;
		head = head->next;
		head->prev = NULL;
		free(temp);
		puts("Berhasil menghapus lagu!");
		flag = 1;
		return;
	}
	else if(strcmp(tail->judul, title) == 0){ // pop tail
		temp = tail->prev;
		tail = temp;
		tail->next = NULL;
		temp = temp->next;
		free(temp);
		puts("Berhasil menghapus lagu!");
		flag = 1;
		return;
	}
	else{ // pop mid
		struct Lagu *current = head;
		while(current != NULL){
			if(strcmp(current->judul, title) == 0){
				flag = 1;
				break;
			}
			current = current->next;
		}
		
		if(flag == 1){
			temp = current->prev;
			temp->next = current->next;
			temp = current->next;
			temp->prev = current->prev;
			free(current);
			puts("Berhasil menghapus lagu!");
		}
		else{
			puts("Lagu tidak ditemukan!");
		}
	}
}

void view();
void add();
void del();
void tog();
void prev();
void next();
int loop = 0;

void enterToContinue(){
	printf("Press ENTER to Continue...");
	getchar();
}

struct Lagu *playing;

int main(){
	char nama[25];
	strcpy(nama, "Ruang Sendiri");
	push(nama);
	
	strcpy(nama, "Monokrom");
	push(nama);
	
	strcpy(nama, "Gajah");
	push(nama);
	
	playing = head;
	playing = playing->next;
	
	int choice = -1;
	do{
//		view();
		system("cls");
		printf("Now Playing : %s\n", playing->judul);
		printf("Loop : %s\n", loop ? "ON" : "OFF");
		puts("1. Add Song");
		puts("2. View Queue");
		puts("3. Delete Song");
		puts("4. Toggle Loop/Play Once");
		puts("7. Previous Song");
		puts("8. Next Song");
		puts("0. Exit");
		do{
			printf(">> ");
			scanf("%d", &choice); getchar();
			switch (choice){
				case 1:
					add();
					enterToContinue();
					break;
				case 2:
					view();
					enterToContinue();
					break;
				case 3:
					del();
					enterToContinue();
					break;
				case 4:
					tog();
					enterToContinue();
					break;
				case 7:
					prev();
					enterToContinue();
					break;
				case 8:
					next();
					enterToContinue();
					break;
				case 0:
					puts("Thankyou for using this program!");
					return 0;
			}
			if(!((choice >= 1 && choice <= 5) || (choice == 7 || choice == 8))){
				puts("Wrong input!");
			}
		} while(!((choice >= 1 && choice <= 5) || (choice == 7 || choice == 8)));
	}while(1);
}

void view(){
	if(!head){
		puts("There is no song in the queue");
		return;
	}
	struct Lagu *temp;
	temp = head;
	
	for(int i = 1; i<=count; i++){
		printf("%d. %s\n", i, temp->judul);
		temp = temp->next;
	}
	puts("===============================");
}

void add(){
	char title[25];
	printf("Input song title : ");
	scanf("%[^\n]", title); getchar();
	push(title);
	puts("Song has been added successfully!");
	count++;
}

void del(){
	if(!head){
		puts("There is no song in the queue");
		return;
	}
	
	char title[25];
	do{
		printf("Input song title to delete : ");
		scanf("%[^\n]", title); getchar();
		pop(title);
	} while(flag == 0);
	
	puts("Song has been deleted successfully!");
	count--;
}

void tog(){
	if(loop == 0){
		puts("Loop activated!");
		loop = 1;
		tail->next = head;
		head->prev = tail;
	}
	else{
		puts("Loop inactive!");
		loop = 0;
		tail->next = NULL;
		head->prev = NULL;
	}
}

void prev(){
	if(playing->prev == NULL){
		puts("There is no previous song!");
		return;
	}
	playing = playing->prev;
	puts("Success play previous song!");
}

void next(){
	if(playing->next == NULL){
		puts("There is no next song!");
		return;
	}
	playing = playing->next;
	puts("Success skip the song!");
}
