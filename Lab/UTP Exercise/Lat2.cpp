#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100


struct Node{
	char name[35];
	char phone[15];
	int age;
	char type[10];
	int stay;
	char id[10];
	Node *next;
}*head[MAX_SIZE];

void printMenu(){
	puts("-----------------------------------");
	puts("Hotel GrAnsylvania");
	puts("-----------------------------------");
	puts("1. Booking Hotel");
	puts("2. View Bookings");
	puts("3. Delete Booking");
	puts("4. Exit");
}

void book();
void view();
void del();

int main(){
	do{
		printMenu();
		int choice = -1;
		do{
			printf(">> ");
			scanf("%d", &choice); getchar();
			switch(choice){
				case 1:
					book();
					break;
				case 2:
					view();
					break;
				case 3:
					del();
					break;
				case 4:
					return 0;
			}
		} while(choice < 1 || choice > 4);
	}while(1);
}

bool validNum(char phone[]){
	if(strncmp(phone, "+62", 3) != 0){
		return false;
	}
	
	int len = strlen(phone);
	int countSpace = 0;
	for(int i = 3; i<len; i++){
		if(phone[i] == ' ') countSpace++;
	}
	if(countSpace < 1) return false;
	if((len - countSpace - 3) != 11) return false;
	
	return true;
}

void enter(){
	printf("Press ENTER to continue...");
	getchar();
}

void book(){
	char name[35];
	char phone[15];
	int age;
	char type[10];
	int stay;
	char id[10];
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	do{
		printf("Input Full Name [3..30] : ");
		scanf("%[^\n]", name); getchar();
		if(!(strlen(name) >= 3 && strlen(name) <= 30)){
			puts("Full name length must between 3 and 30");
		}
	} while(!(strlen(name) >= 3 && strlen(name) <= 30));
	
	do{
		printf("Input Phone Number : ");
		scanf("%[^\n]", phone); getchar();
		if(!validNum(phone)){
			puts("Phone number must begin with '+62', contains with at least 1 space and the length must be 11 (Exclude +62 and space)");
		}
	} while(!validNum(phone));
	
	do{
		printf("Input Age [Minimum 18] : ");
		scanf("%d", &age); getchar();
		if(age < 18){
			puts("Age must be minimum 18");
		}
	} while(age < 18);
	
	do{
		printf("Input Room Type [Regular | Deluxe | Suite] (Case Sensitive) : ");
		scanf("%[^\n]", type); getchar();
		if(!(
		strcmp(type, "Regular") == 0 ||
		strcmp(type, "Deluxe") == 0 ||
		strcmp(type, "Suite") == 0
		)){
			puts("Room type must be either Regular or Deluxe or Suite (Case Sensitive)");
		}
	} while(!(
		strcmp(type, "Regular") == 0 ||
		strcmp(type, "Deluxe") == 0 ||
		strcmp(type, "Suite") == 0
	));
	
	do{
		printf("Input How Many Night You Will Stay [1..30] : ");
		scanf("%d", &stay); getchar();
		if(stay < 1 || stay > 30){
			puts("You can't stay less than 1 night or more than 30 nights");
		}
	} while(stay < 1 || stay > 30);
	
	int key = 0;
	
	id[0] = type[0];
	id[1] = type[1] - ('a' - 'A');
	for(int i = 2; i<=4; i++){
		int random = rand() % 10;
		key += random;
		id[i] = random + '0';
	}
	id[5] = '\0';
	
	key -= 1;
	key %= MAX_SIZE;
	
	strcpy(newNode->name, name);
	strcpy(newNode->phone, phone);
	newNode->age = age;
	strcpy(newNode->type, type);
	newNode->stay = stay;
	strcpy(newNode->id, id);
	newNode->next = NULL;
	
	//Pushing
	if(!head[key]){
		head[key] = newNode;
	}
	else{
		Node *temp = head[key];
		while(temp->next){
			temp = temp->next;
		}
		temp->next = newNode;
	}
	
	puts("============================");
	printf("| Booking ID\t : %s\n", id);
	puts("============================");
	printf("| Full Name\t : %s\n", name);
	printf("| Phone Number\t : %s\n", phone);
	printf("| Room Type\t : %s\n", type);
	printf("| Night Stay\t : %d %s", stay, (stay == 1) ? "night\n" : "night(s)\n");
	puts("============================");
	enter();
	
}

void view(){
	int flag = 0;
	for(int i = 0; i<MAX_SIZE; i++){
		Node *temp = head[i];
		while(temp){
			puts("============================");
			printf("| Booking ID\t : %s\n", temp->id);
			puts("============================");
			printf("| Full Name\t : %s\n", temp->name);
			printf("| Phone Number\t : %s\n", temp->phone);
			printf("| Room Type\t : %s\n", temp->type);
			printf("| Night Stay\t : %d %s", temp->stay, (temp->stay == 1) ? "night\n" : "night(s)\n");
			puts("============================\n");
			temp = temp->next;
			flag = 1;
		}
	}
	if(flag == 0){
		puts("============================");
		puts("There is no booking !");
		puts("============================");
	}
	enter();
}

void del(){
	int flag = 0;
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i] != NULL){
			flag = 1;
			break;
		}
	}
	if(flag == 0){
		puts("============================");
		puts("There is no booking !");
		puts("============================");
		enter();
		return;
	}
	
	int ketemu = 0;
	if(flag == 1){
		char idTemp[10];
		printf("Input Booking ID (Case Sensitive) : ");
		scanf("%s", idTemp); getchar();
		
		// Popping
		for(int i = 0; i<MAX_SIZE; i++){
			if(head[i] != NULL){
				if(strcmp(head[i]->id, idTemp) == 0){
					//Pop Head
					Node *temp = head[i];
					head[i] = head[i]->next;
					printf("BookingID %s is Succesfully Deleted!\n", temp->id);
					free(temp);
					ketemu = 1;
				}
				else{
					Node *temp = head[i]->next;
					//Biar berhenti di belakang target
					while(temp){
						if(strcmp(temp->id, idTemp) == 0){
							ketemu = 1;
							Node *target = temp->next;
							temp->next = target->next;
							printf("BookingID %s is Succesfully Deleted!", target->id);
							target->next = NULL;
							free(target);
						}
						temp = temp->next;
					}
				}
			}
		}
	}
	if(ketemu == 0){
		puts("Failed to Delete, No Data!");
	}
	enter();
}
