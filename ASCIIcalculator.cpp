#include <stdio.h>
#include <string.h>

int main(){
	do{
		char inp[100];
		scanf("%s", inp); getchar();
		int key = 0;
		for(int i = 0; i<strlen(inp); i++){
			key += inp[i];
		}
		printf("%d\n", key);
	} while(1);
}
