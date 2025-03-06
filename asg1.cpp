#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Player{
	char name[50];
	char rank[10];
	int hp;
	int magic;
	int gold;
};

Player* ppti = (Player*)malloc(sizeof(Player));

int playerCount = 0;

void insert();
void view();
void del();
void upgrade();


int main(){
	int choice = -1;
	do{
		puts("Game");
		puts("1. Insert");
		puts("2. View");
		puts("3. Delete");
		puts("4. Upgrade");
		puts("5. Exit");
		scanf("%d", &choice); getchar();
		switch (choice){
			case 1:
				insert();
				break;
			case 2:
				view();
				break;
			case 3:
				del();
				break;
			case 4:
				upgrade();
				break;
		}
	}while(choice != 5);
}

void insert(){
	Player temp;
	printf("Enter Player Name : ");
	scanf("%[^\n]", temp.name); getchar();
	
	do{
		printf("Enter Player Rank [Bronze | Silver | Gold] : ");
		scanf("%[^\n]", temp.rank); getchar();
	} while(!(strcmp(temp.rank, "Bronze") == 0 || 
			strcmp(temp.rank, "Silver") == 0 || 
			strcmp(temp.rank, "Gold") == 0));
	
	printf("Enter Player HP : ");
	scanf("%d", &temp.hp); getchar();
	
	printf("Enter Player Magic : ");
	scanf("%d", &temp.magic); getchar();
	
	printf("Enter Player Gold : ");
	scanf("%d", &temp.gold); getchar();
	
	ppti[playerCount] = temp;
	playerCount++;
	puts("Your Player has been inserted successfully!");
	return;
}

void view(){
	if(playerCount == 0){
		printf("There is no player to display!\n");
		return;
	}
	
	for(int i = 0; i<playerCount; i++){
		printf("%d. %s - %s - %d(HP) - %d(Magic) - %d(Gold)\n", i+1, ppti[i].name, ppti[i].rank, ppti[i].hp, ppti[i].magic, ppti[i].gold);
	}
	printf("\n");
}

void del(){
	view();
	if(playerCount == 0){
		return;
	}
	int idx;
	do{
		printf("Select player number you want to delete : ");
		scanf("%d", &idx); getchar();
		idx -= 1;
	} while(!(idx >= 0 && idx < playerCount));
	
	for(int i = idx; i<playerCount-1; i++){
		ppti[i] = ppti[i+1];
	}
	playerCount--;
	
	puts("Player has been deleted successfully!");
}

void upgrade(){
	view();
	if(playerCount == 0){
		return;
	}
	int idx;
	do{
		printf("Select player number you want to upgrade : ");
		scanf("%d", &idx); getchar();
		idx -= 1;
	} while(!(idx >= 0 && idx < playerCount));
	
	if(ppti[idx].gold >= 50){
		ppti[idx].hp += 150;
		ppti[idx].magic += 150;
		ppti[idx].gold -= 50;
		puts("Player has been upgraded successfully!");
	}
	else{
		puts("Player has not enough gold for upgrade!");
	}
	
}
