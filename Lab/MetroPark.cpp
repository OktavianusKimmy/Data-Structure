#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

struct Node{
	char plat[15];
	char jenis[10];
	char id[10];
	Node *next;
}*head[MAX_SIZE];

void add();
void view();
void del();

int main(){
	srand(time(NULL));
	do{
		int choice = -1;
		puts("Mall MetroPark");
		puts("1. Tambah Kendaraan");
		puts("2. Tampilkan Kendaraan");
		puts("3. Hapus Kendaraan");
		puts("4. Exit");
		do{
			printf(">> ");
			scanf("%d", &choice); getchar();
			switch (choice){
				case 1:
					add();
					break;
				case 2:
					view();
					break;
				case 3:
					del();
					break;
			}
		} while(choice < 1 || choice > 4);
	} while(1);
}

bool validPlate(char plat[]){
	if(!(plat[0] >= 'A' && plat[0] <= 'Z' && plat[1] >= 'A' && plat[1] <= 'Z')) return false;
	
	if(!(plat[3] >= '0' && plat[3] <= '9' && 
		plat[4] >= '0' && plat[4] <= '9' && 
		plat[5] >= '0' && plat[5] <= '9' &&
		plat[6] >= '0' && plat[6] <= '9')) return false;
	if(!(plat[8] >= 'A' && plat[8] <= 'Z' &&
		plat[9] >= 'A' && plat[9] <= 'Z')) return false;
		
	return true;
}

int getHashKey(char id[]){
	int len = strlen(id);
	int key = 0;
	
	for(int i = 2; i<len; i++){
		key += id[i] - '0';
	}
	
	return key % 100;
}

void add(){
	char plat[15];
	char jenis[10];
	char id[10];
	
	do{
		printf("Masukkan nomor plat kendaraan: ");
		scanf("%[^\n]", plat); getchar();
		if(!validPlate(plat)){
			puts("(format: XX 1234 YY, dengan XX adalah dua huruf, 1234 adalah empat angka, dan YY adalah dua huruf)");
		}
	} while(!validPlate(plat));
	
	do{
		printf("Masukkan jenis kendaraan: ");
		scanf("%[^\n]", jenis); getchar();
		if(!(strcmp(jenis, "Motor") == 0 ||
			strcmp(jenis, "Mobil") == 0 ||
			strcmp(jenis, "Bus") == 0)){
				puts("Motor, Mobil, atau Bus - harus sesuai dan case-sensitive");
			}
	}while(!(strcmp(jenis, "Motor") == 0 ||
			strcmp(jenis, "Mobil") == 0 ||
			strcmp(jenis, "Bus") == 0));
	
	sprintf(id, "%c%c%d%d%d", plat[0], plat[1], rand()%9 + 1, rand()%10, rand()%10);
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->plat, plat);
	strcpy(newNode->jenis, jenis);
	strcpy(newNode->id, id);
	newNode->next = NULL;
	
	// Hashing
	int key = getHashKey(id);
	
	// Pushing
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
	
	puts("=================================");
	printf("Plat: %s\n", plat);
	printf("Jenis: %s\n", jenis);
	printf("ID: %s\n", id);
	puts("=================================");
	puts("Has been added successfully");
	
}

void view(){
	int flag = 0;
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			flag = 1;
			Node *temp = head[i];
			while(temp){
				puts("=================================");
				printf("Plat: %s\n", temp->plat);
				printf("Jenis: %s\n", temp->jenis);
				printf("ID: %s\n", temp->id);
				temp = temp->next;
			}
		}
	}
	puts("=================================");
	
	if(flag == 0){
		puts("Tidak ada mobil");
	}
}

void del(){
	char id[10];
	
	printf("Masukkan ID parkir kendaraan: ");
	scanf("%[^\n]", id); getchar();
	
	for(int i = 0; i<MAX_SIZE; i++){
		if(head[i]){
			if(strcmp(head[i]->id, id) == 0){
				Node *temp = head[i];
				head[i] = head[i]->next;
				printf("Berhasil menghapus ID %s, Plat %s\n", temp->id, temp->plat);
				free(temp);
				return;
			}
			else{
				Node *temp = head[i];
				while(temp->next){
					if(strcmp(temp->next->id, id) == 0){
						Node *target = temp->next;
						temp->next = target->next;
						target->next = NULL;
						printf("Berhasil menghapus ID %s, Plat %s\n", target->id, target->plat);
						free(target);
						return;
					}
					temp = temp->next;
				}
			}
		}
	}
	
	printf("ID parkir tidak ditemukan.\n");
}





