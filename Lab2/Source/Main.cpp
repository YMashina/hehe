#include <stdio.h>
#include "L_func.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

using namespace h_list;

int func(lisp L, int count){
	count = 0;
	if(h_list::isAtom(L->node.pair.hd)){
		count++;
		printf("\n%c\n", h_list::isAtom(L));
		//L=L->node.pair.tl;
		return count;
	}
	else 
		if (isNull(L))
			return 0;
	L=L->node.pair.tl;
	count+=func(L,count);
	
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

	int count = 0;
	count = func(el, count);

	printf("\n%d\n",count);

	h_list::destroy(L);
	putchar('\n');
	return 0;
}
