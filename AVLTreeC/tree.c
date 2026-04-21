#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

static void PrintNodes(Node* node, int level, FILE* stream) {
	if (node == NULL) return;
	PrintNodes(node->right, level + 1, stream);
	for (int i = 0; i < level; i++)
		fprintf(stream, "\t");
	fprintf(stream, "Node(key = %s; number = %f)\n", node->data.key, node->data.number);
	PrintNodes(node->left, level + 1, stream);
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

void PrintTree(Tree* tree, FILE* stream) {
	if (tree->root == NULL)
	{
		fprintf(stream, "tree is empty\n");
		return;
	}
	PrintNodes(tree->root, 0, stream);
}

int ExecuteCommand(Tree* tree, const char* input, FILE* stream) {
	char command[11];
	char key[7];
	float number;
	int status;

	if (sscanf(input, "%10s", command) == 0)
	{
		fprintf(stream, "parsing error\n");
		return 0;
	}

	if (strcmp(command, "add") == 0)
	{
		if (sscanf(input, "%10s %6s %f", command, key, &number) != 3)
		{
			fprintf(stream, "parsing error\n");
			return 0;
		}
		AddToTree(tree, key, number, &status);
		fprintf(stream, "%s\n", status == 0 ? "element added" : "can't add duplicate");
	}

	else if (strcmp(command, "remove") == 0)
	{
		if (sscanf(input, "%10s %6s", command, key) != 2)
		{
			fprintf(stream, "parsing error\n");
			return 0;
		}
		RemoveFromTree(tree, key, &status);
		fprintf(stream, "%s\n", status == 0 ? "element deleted" : "404 :(");
	}

	else if (strcmp(command, "print") == 0)
	{
		PrintTree(tree, stream);
	}

	else if (strcmp(command, "search") == 0)
	{
		if (sscanf(input, "%10s %6s", command, key) != 2)
		{
			fprintf(stream, "parsing error\n");
			return 0;
		}
		float result = SearchInTree(tree, key, &status);
		if (status == 0)
		{
			fprintf(stream, "found result: Node(key = %s, number = %f)\n", key, result);
		}
		else fprintf(stream, "404 :(\n");
	}

	else if (strcmp(command, "exit") == 0)
	{
		DestroyTree(tree);
		return 1;
	}
	
	else if (strcmp(command, "help") == 0)
	{
		fprintf(stream, "avaliable commands:\n");
		fprintf(stream, "    add [key] [float number]\n");
		fprintf(stream, "    remove [key]\n");
		fprintf(stream, "    print\n");
		fprintf(stream, "    search [key]\n");
		fprintf(stream, "    exit\n");
	}

	else
		fprintf(stream, "unknown command\n");

	return 0;
}

