#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define HASH_SIZE 100

struct Booking{
	char fullname[40];
	char phonenumber[15];
	int age;
	char roomtype[10];
	int stayduration;
	char bookingid[7];
	Booking *next;
}*bookings[HASH_SIZE];

int getHashKey(char* id){
	int x = 0;
	for(int i = 2; i<5; i++){
		x += id[i] - '0';
	}
	
	return (x-1)%100;
}

Booking* newBooking(char* fullname, char* phonenumber, int age, char* roomtype, int stayduration, char* id){
	Booking* curr = (Booking*)malloc(sizeof(Booking));
	strcpy(curr->fullname, fullname);
	strcpy(curr->phonenumber, phonenumber);
	curr->age = age;
	strcpy(curr->roomtype, roomtype);
	curr->stayduration = stayduration;
	strcpy(curr->bookingid, id);
	
	curr->next = NULL;
	
	return curr;
}

void pushTail(Booking* newData){
	int hash = getHashKey(newData->bookingid);
	
	if(bookings[hash] == NULL){
		bookings[hash] = newData;
	}
	else{
		Booking* curr = bookings[hash];
		while(curr->next){
			curr = curr->next;
		}
		curr->next = newData;
	}
}

bool pop(char* bookingid){
	int hash = getHashKey(bookingid);
	Booking* curr = bookings[hash];
	if(strcmp(curr->bookingid, bookingid) == 0){
		//data di head
		bookings[hash] = curr->next;
		free(curr);
		return true;
	}
	else{
		while(curr->next){
			if(strcmp(curr->next->bookingid, bookingid) == 0){
				Booking* temp = curr->next;
				curr->next = temp->next;
				free(temp);
				return true;
			}
			curr = curr->next;
		}
	}
	return false;
}

bool validPhoneNumber(char* phonenumber){
	if(phonenumber[0] != '+' || phonenumber[1] != '6' || phonenumber[2] != '2'){
		return false;
	}
	
	int space = 0;
	int len = strlen(phonenumber);
	for(int i = 3; i<len; i++){
		if(phonenumber[i] == ' '){
			space++;
		}
	}
	return space>=1 && (len - (space + 3) == 11);
}

void createBooking(){
	char fullname[40];
	char phonenumber[15];
	int age;
	char roomtype[10];
	int stayduration;
	char bookingid[7];
	
	do{
		printf("Input Name: ");
		scanf("%[^\n]", fullname); getchar();
		if(strlen(fullname) < 3 || strlen(fullname) > 30){
			puts("Full name length must between 3 and 30");
		}
	} while(strlen(fullname) < 3 || strlen(fullname) > 30);
	
	do{
		printf("Input Phone Number: ");
		scanf("%[^\n]", phonenumber); getchar();
		if(!(validPhoneNumber(phonenumber))){
			puts("Phone number must begin with '+62', contains with at least 1 space and the length must be 11 (Exclude +62 and space)");
		}
	} while(!(validPhoneNumber(phonenumber)));
	
	do{
		printf("Input Age [Minimum 18]: ");
		scanf("%d", &age); getchar();
		if(age < 18){
			puts("Age must be minimum 18");
		}
	} while(age < 18);
	
	do{
		printf("Input Room Type [Regular | Deluxe | Suite] (Case Sensitive): ");
		scanf("%[^\n]", roomtype); getchar();
		if(!(strcmp(roomtype, "Regular") == 0 || strcmp(roomtype, "Deluxe") == 0 || strcmp(roomtype, "Deluxe") == 0 || strcmp(roomtype, "Suite") == 0)){
			puts("Room type must be either Regular or Deluxe or Suite (Case Sensitive)");
		}
	} while(!(strcmp(roomtype, "Regular") == 0 || strcmp(roomtype, "Deluxe") == 0 || strcmp(roomtype, "Deluxe") == 0 || strcmp(roomtype, "Suite") == 0));

	do{
		printf("Input How Many Night You Will Stay [1..30] : ");
		scanf("%d", &stayduration); getchar();
		if(stayduration <= 0 || stayduration > 30){
			puts("You can't stay less than 1 night or more than 30 nights");
		}
	} while(stayduration <= 0 || stayduration > 30);
	
	
	bookingid[0] = roomtype[0];
	bookingid[1] = roomtype[1] - ('a' - 'A');
	srand(time(NULL));
	bookingid[2] = rand() % 10 + '0';
	bookingid[3] = rand() % 10 + '0';
	bookingid[4] = rand() % 10 + '0';
	bookingid[5] = '\0';
	
	printf("%s\n", bookingid);
	printf("Name : %s\n", fullname);
	printf("Phone Num : %s\n", phonenumber);
	printf("Age : %d\n", age);
	printf("Room : %s\n", roomtype);
	printf("Nights : %d\n", stayduration);
	
	pushTail(newBooking(fullname, phonenumber, age, roomtype, stayduration, bookingid));
	
}

bool viewBooking(){
	bool found = false;
	for(int i = 0; i<HASH_SIZE; i++){
		Booking *curr = bookings[i];
		while(curr){
			printf("Booking ID : %s\n", curr->bookingid);
			curr = curr->next;
			found = true;
		}
	}
	if(!found){
		puts("Not found!");
	}
	return found;
}

void deleteBooking(){
	if(!viewBooking()){
		return;
	}
	
	char bookingid[7];
	printf("Input Booking ID : ");
	scanf("%[^\n]", bookingid); getchar();
	
	if(pop(bookingid)){
		printf("Booking ID %s is successfully deleted\n", bookingid);
	}
	else{
		puts("Failed to Delete, there is no data!");
	}
}

int main(){
	int choice = -1;
	do{
		printf("Hotel Granyslavia\n");
		printf("1. Booking Hotel\n");
		printf("2. View Booking\n");
		printf("3. Delete Booking\n");
		printf("4. Exit\n");
		scanf("%d", &choice); getchar();
		switch(choice){
			case 1:
				createBooking();
				break;
			case 2:
				viewBooking();
				break;
			case 3:
				deleteBooking();
				break;
			case 4:
				break;
		}
	}while(1);
	
	return 0;
}
