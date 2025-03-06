#include <stdio.h>

void popMid(){
	struct tnode *temp1 = h;
	struct tnode *curr = h->next;
	
	while(temp1->next->valueNode != target->valueNode){
		temp1 = temp1->next;
	}
	curr = temp1->next;
	
	temp1->next = curr->next;
	free(curr);
}
