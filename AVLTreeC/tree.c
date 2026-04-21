#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

static void PrintNodes(Node* node, int level) {
	if (node == NULL) return;
	PrintNodes(node->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("\t");
	printf("Node(key = %s; number = %f)\n", node->data.key, node->data.number);
	PrintNodes(node->left, level + 1);
}

void AddToTree(Tree* tree, const char* key, float number, int* status) {
	*status = 0;
	tree->root = AddChild(tree->root, key, number, status);
}

void RemoveFromTree(Tree* tree, const char* key, int* status) {
	*status = 0;
	tree->root = RemoveChild(tree->root, key, status);
}

void ClearTree(Tree* tree) {
	tree->root = DestroyNodes(tree->root);
}
	
Tree* DestroyTree(Tree* tree) {
	ClearTree(tree);
	free(tree);
	return NULL;
}

Tree* NewTree() {
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	if (newTree == NULL)
	{
		printf("memory allocation error for Tree\n");
		return NULL;
	}
	newTree->root = NULL;
	return newTree;
}

float SearchInTree(Tree* tree, const char* key, int* status) {
	*status = 0;
	return FindChild(tree->root, key, status);
}

void PrintTree(Tree* tree) {
	if (tree->root == NULL)
	{
		printf("tree is empty\n");
		return;
	}
	PrintNodes(tree->root, 0);
}

void ExecuteCommand(Tree* tree, const char* input) {
	char command[11];
	char key[7];
	float number;
	int status;

	if (sscanf(input, "%10s", command) == 0)
	{
		printf("parsing error\n");
		return;
	}

	if (strcmp(command, "add") == 0)
	{
		if (sscanf(input, "%10s %6s %f", command, key, &number) != 3)
		{
			printf("parsing error\n");
			return;
		}
		AddToTree(tree, key, number, &status);
		printf("%s\n", status == 0 ? "element added" : "can't add duplicate");
	}

	else if (strcmp(command, "remove") == 0)
	{
		if (sscanf(input, "%10s %6s", command, key) != 2)
		{
			printf("Parsing error\n");
			return;
		}
		RemoveFromTree(tree, key, &status);
		printf("%s\n", status == 0 ? "element deleted" : "404 :(");
	}

	else if (strcmp(command, "print") == 0)
		PrintTree(tree);

	else if (strcmp(command, "search") == 0)
	{
		if (sscanf(input, "%10s %6s", command, key) != 2)
		{
			printf("Parsing error\n");
			return;
		}
		float result = SearchInTree(tree, key, &status);
		if (status == 0)
		{
			printf("Found result: Node(key = %s, number = %f)\n", key, result);
		}
		else printf("404 :(\n");
	}

	else if (strcmp(command, "exit") == 0)
	{
		DestroyTree(tree);
		exit(0);
	}
	
	else if (strcmp(command, "help") == 0)
	{
		printf("avaliable commands:\n");
		printf("    add [key] [float number]\n");
		printf("    remove [key]\n");
		printf("    print\n");
		printf("    serach [key]\n");
		printf("    exit\n");
	}

	else
		printf("unknown command\n");
}

