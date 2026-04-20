#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
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
		printf("Meory allocation error for Tree\n");
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
		return;
		printf("Tree is empty\n");
	}
	PrintNodes(tree->root, 0);
}

void ExecuteCommand(Tree* tree, const char* input) {
	int command;
	char key[11];
	float number;
	int status;

	if (sscanf(input, "%d", &command) == 0)
	{
		printf("Parsing error\n");
		return;
	}

	if (command == 1)
	{
		if (sscanf(input, "%d %9s %f", &command, key, &number) != 3)
		{
			printf("Parsing error\n");
			return;
		}
		AddToTree(tree, key, number, &status);
		printf("%s\n", status == 0 ? "element added" : "can't add duplicate");
	}

	else if (command == 2)
	{
		if (sscanf(input, "%d %9s", &command, key) != 2)
		{
			printf("Parsing error\n");
			return;
		}
		RemoveFromTree(tree, key, &status);
		printf("%s\n", status == 0 ? "element deleted" : "404 :(");
	}

	else if (command == 3)
		PrintTree(tree);

	else if (command == 4)
	{
		if (sscanf(input, "%d %6s", &command, key) != 2)
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

	else if (command == 0)
	{
		DestroyTree(tree);
		exit(0);
	}

	else
		printf("Unknown command\n");
}

