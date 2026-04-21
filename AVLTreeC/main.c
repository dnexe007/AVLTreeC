#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "tree.h"



int main() {
	char buffer[256];
	Tree* tree = NewTree();

	printf("enter \"help\" to see avaliable commands\n");
	for(;;)
	{
		printf("enter command: ");
		fgets(buffer, 255, stdin);

		if (ExecuteCommand(tree, buffer) == 1)
			break;
	}

	return 0;
}