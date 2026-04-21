#ifndef TREE_H
#define TREE_H

#include "node.h"

typedef struct Tree {
	Node* root;
} Tree;

void AddToTree(Tree* tree, const char* key, float number, int* status);

void RemoveFromTree(Tree* tree, const char* key, int* status);

float SearchInTree(Tree* tree, const char* key, int* status);

void ClearTree(Tree* tree);

Tree* DestroyTree(Tree* tree);

Tree* NewTree();

void PrintTree(Tree* tree);

int ExecuteCommand(Tree* tree, const char* command);

#endif
