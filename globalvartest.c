#include <stdio.h>

int globalVar = 15;



void function() {
	printf("globalVar: %d\n", globalVar);
}


int main() {
	function();
	
	globalVar = 16;
	function();
	
	return 0;
}



