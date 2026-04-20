#ifndef  NODE_H
#define NODE_H
#include "nodedata.h"
typedef struct Node
{
    NodeData data;
    int height;

    struct Node* right;
    struct Node* left;
} Node;

Node* AddChild(Node* root, const char* key, float number, int* status);

Node* RemoveChild(Node* root, const char* key, int* status);

Node* DestroyNodes(Node* root);

float FindChild(Node* root, const char* key, int* status);

#endif 
