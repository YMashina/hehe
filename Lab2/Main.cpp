#include <stdio.h>
#include "L_func.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

using namespace h_list;

int func(lisp L, int count){
	count = 0;
	if(h::listisAtom(L)){
		count++;
		//L=L->node.pair.tl;
		return count;
	}
	else 
		if (isNull(L))
	if(L->node.pair.hd->tag == 0){
		el = L;
		L = L->node.pair.hd; 
		delete el;
	}
	L=L->node.pair.hd;
	count+=func(el,count);
	
	return count;
}

int main(){
	lisp L;
	h_list::read_lisp(L);
	if(h_list::isNull(L)){
		printf("Empty list.\n");
		return 0;
	}
	lisp el;
	//printf("\n\nProcessing:\n");
	//examine(L, NULL, L, Stack);
	/*if(h::listisAtom(el)!=1){
		el->node.pair.hd = L;
		el->node.pair.tl = NULL;
		el->tag = false;
		L = el;
		simplify(L, Stack);
	}*/
	
	
	h_list::write_lisp(L);

	h_list::destroy(L);
	putchar('\n');
	return 0;
}
