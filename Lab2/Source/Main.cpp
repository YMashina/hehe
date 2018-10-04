#include <stdio.h>
#include "l_intrfc.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define N 20

using namespace h_list;

int count(lisp L){
	if(h_list::isNULL(L)) return 0;
	int count=0;
	if(h_list::isAtom(L)){
		cout << h_list::getAtom(L) << endl;
		tmp=L->node.pair.tl;
		
	}
	else {
		L=L->node.pair.hd;
	}
	count+=count(L);
	return count;
}



int main(){
	lisp L;
	h_list::read_lisp(L);
	if(h_list::isNull(L)){
		printf("Empty list.\n");
		return 0;
	}
	//lisp el;

	int c = count(L);

	printf("\n\nProcessing:\n");
	examine(L, NULL, L, Stack);
	if(Stack->topIndex != -1){
		el = new s_expr;
		el->node.pair.hd = L;
		el->node.pair.tl = NULL;
		el->tag = false;
		L = el;
		simplify(L, Stack);
	}
	if(L->node.pair.hd->tag == 0){
		el = L;
		L = L->node.pair.hd; 
		delete el;
	}
	
	return 0;
}