#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"



int main(int argc, char* argv[]) {

	char buffer[256];
	Tree* tree = NewTree();

	if (argc == 1)
	{
		printf("enter \"help\" to see avaliable commands\n");
		for (;;)
		{
			printf("enter command: ");
			fgets(buffer, 255, stdin);

			if (ExecuteCommand(tree, buffer, stdout) == 1)
				break;
		}
	}

	else
	{
		FILE* input = fopen(argv[1], "r");

		if(input == NULL)
		{
			printf("input file opening error\n");
			exit(1);
		}

		FILE* output = argc == 3? fopen(argv[2], "w"): stdout;
		
		if (output == NULL)
		{
			printf("output file opening error\n");
			fclose(input);
			exit(1);
		}

		while (fgets(buffer, sizeof(buffer), input))
		{
			if (ExecuteCommand(tree, buffer, output) == 1)
				break;
		}
		fclose(input);
		if(argc == 3)
			fclose(output);
	}
	return 0;
}