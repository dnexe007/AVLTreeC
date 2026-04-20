#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"



//=========================================
//            PRIVATE METHODS
//=========================================

static int Max(int a, int b) {
    if (a >= b) return a;
    return b;
}

static int RightHeight(Node* root) {
    return (root->right != NULL) ? root->right->height : 0;
}

static int LeftHeight(Node* root) {
    return (root->left != NULL) ? root->left->height : 0;
}

static void UpdateHeight(Node* root) {
    if (root == NULL) return;
    root->height = 1 + Max(RightHeight(root), LeftHeight(root));
}

static int GetBalance(Node* root) {
    if (root == NULL) return 0;
    return LeftHeight(root) - RightHeight(root);
}

static Node* RotateRight(Node* root) {
    if (root == NULL) return NULL;
    Node* leftChild = root->left;
    if (leftChild == NULL) return root;

    root->left = leftChild->right;

    leftChild->right = root;

    UpdateHeight(root);

    UpdateHeight(leftChild);

    return leftChild;
}

static Node* RotateLeft(Node* root) {
    if (root == NULL) return NULL;
    Node* rightChild = root->right;
    if (rightChild == NULL) return root;

    root->right = rightChild->left;

    rightChild->left = root;

    UpdateHeight(root);
    UpdateHeight(rightChild);

    return rightChild;
}

static Node* Balanced(Node* root) {
    if (root == NULL) return NULL;
    UpdateHeight(root);
    int balance = GetBalance(root);

    if (balance > 1)
    {
        if (GetBalance(root->left) < 0)
            root->left = RotateLeft(root->left);
        return RotateRight(root);
    }
    if (balance < -1)
    {
        if (GetBalance(root->right) > 0)
            root->right = RotateRight(root->right);
        return RotateLeft(root);
    }
    return root;
}

static NodeData FindMinimumChild(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root->data;
}


static void FreeNode(Node* node) {
    free(node->data.key);
    free(node);
}

//=========================================
//            PUBLIC METHODS
//=========================================

Node* AddChild(Node* root, char* key, float number, int* status) {
    if (root == NULL)
    {
        root = (Node*)malloc(sizeof(Node));

        if (root == NULL)
        {
            printf("Memory allocation error\n");
            exit(1);
        }

        root->data.key = strdup(key);

        if (root->data.key == NULL)
        {
            printf("Memory allocation error\n");
            exit(1);
        }

        root->data.number = number;

        root->height = 1;
        root->left = NULL;
        root->right = NULL;

        return root;
    }

    if (strcmp(key, root->data.key) == 0)
    {
        *status = 1;
        return root;
    }

    else if (strcmp(key, root->data.key) > 0)
        root->right = AddChild(root->right, key, number, status);
    else
        root->left = AddChild(root->left, key, number, status);

    return Balanced(root);
}

Node* RemoveChild(Node* root, const char* key, int* status) {
    if (root == NULL)
    {
        *status = 1;
        return NULL;
    }


    if(strcmp(key, root->data.key) == 0)
    {
        if (root->right != NULL && root->left != NULL)
        {
            NodeData min = FindMinimumChild(root->right);
                
            free(root->data.key);
            root->data.key = strdup(min.key);

            if (root->data.key == NULL)
            {
                printf("Memory allocation error");
                exit(1);
            }

            root->data.number = min.number;

            root->right = RemoveChild(root->right, min.key, status);
        }

        else if (root->right != NULL)
        {
            Node* temp = root;
            root = root->right;
            FreeNode(temp);
        }

        else if (root->left != NULL)
        {
            Node* temp = root;
            root = root->left;
            FreeNode(temp);
        }

        else
        {
            FreeNode(root);
            root = NULL;
        }
    }
    else
    {
        if(strcmp(key, root->data.key) > 0)
            root->right = RemoveChild(root->right, key, status);

        else
            root->left = RemoveChild(root->left, key, status);
    }
    return Balanced(root);
}

Node* DestroyNodes(Node* root) {
    if (root == NULL) return NULL;
    DestroyNodes(root->right);
    DestroyNodes(root->left);
    FreeNode(root);
    return NULL;
}


float FindChild(Node* root, const char* key, int* status) {
    while (root != NULL)
    {
        int cmp = strcmp(key, root->data.key);
        if (cmp > 0)
            root = root->right;
        else if (cmp < 0)
            root = root->left;
        else break;
    }
    if (root == NULL) *status = 1;
    return root == NULL ? 0 : root->data.number;
}
