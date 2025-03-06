#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mahasiswa{
	char NIM[10];
	char Nama[50];
};

int main(){
	
//	mahasiswa ppti21[100];
//	strcpy(ppti21[0].NIM, "2802540055");
//	
//	printf("%s\n", ppti21[0].NIM);

	struct mahasiswa* ppti = (struct mahasiswa*)malloc(sizeof(struct mahasiswa*));
	
	return 0;
}
