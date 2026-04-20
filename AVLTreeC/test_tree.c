#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tree.h"

static int GetHeight(Node* root) {
    if (root == NULL) return 0;
    int left = GetHeight(root->left);
    int right = GetHeight(root->right);
    return (left > right ? left : right) + 1;
}

static int IsBalanced(Node* root) {
    if (root == NULL) return 1;
    int balance = GetHeight(root->left) - GetHeight(root->right);
    if (balance < -1 || balance > 1) return 0;
    return IsBalanced(root->left) && IsBalanced(root->right);
}

void TestAdd() {
    printf("Add (success)\n");

    Tree* tree = NewTree();
    int status;

    AddToTree(tree, "zebra", 10.5, &status);
    AddToTree(tree, "apple", 5.2, &status);
    AddToTree(tree, "monkey", 7.8, &status);
    AddToTree(tree, "banana", 3.1, &status);
    AddToTree(tree, "cat", 2.4, &status);

    assert(status == 0);
    assert(tree->root != NULL);
    assert(IsBalanced(tree->root));

    DestroyTree(tree);
    printf("PASSED\n");
}

void TestAddDuplicate() {
    printf("Add (duplicate)\n");

    Tree* tree = NewTree();
    int status;

    AddToTree(tree, "test", 10.0, &status);
    assert(status == 0);

    AddToTree(tree, "test", 20.0, &status);
    assert(status == 1);

    float result = SearchInTree(tree, "test", &status);
    assert(result == 10.0);

    DestroyTree(tree);
    printf("PASSED\n");
}

void TestRemove() {
    printf("Remove (success)\n");

    Tree* tree = NewTree();
    int status;

    AddToTree(tree, "root", 100.0, &status);
    AddToTree(tree, "left", 50.0, &status);
    AddToTree(tree, "right", 150.0, &status);

    RemoveFromTree(tree, "left", &status);
    assert(status == 0);

    float result = SearchInTree(tree, "left", &status);
    assert(status == 1);

    assert(IsBalanced(tree->root));

    DestroyTree(tree);
    printf("PASSED\n");
}

void TestRemoveNotFound() {
    printf("Remove (non-existing element)\n");

    Tree* tree = NewTree();
    int status;

    AddToTree(tree, "exists", 10.0, &status);

    RemoveFromTree(tree, "notexists", &status);
    assert(status == 1);

    float result = SearchInTree(tree, "exists", &status);
    assert(status == 0);
    assert(result == 10.0);

    DestroyTree(tree);
    printf("PASSED\n");
}

void TestSearch() {
    printf("Search (success)\n");

    Tree* tree = NewTree();
    int status;

    float targetResult = 2.2;

    AddToTree(tree, "alpha", 1.1, &status);
    AddToTree(tree, "beta", targetResult, &status);
    AddToTree(tree, "gamma", 3.3, &status);

    float result = SearchInTree(tree, "beta", &status);
    assert(status == 0);
    assert(result == targetResult);

    DestroyTree(tree);
    printf("PASSED\n");
}

void TestSearchNotFound() {
    printf("Search (not found)\n");

    Tree* tree = NewTree();
    int status;

    AddToTree(tree, "present", 5.5, &status);

    float result = SearchInTree(tree, "absent", &status);
    assert(status == 1);
    assert(result == 0.0);

    DestroyTree(tree);
    printf("PASSED\n");
}

int main() {
    TestAdd();
    TestAddDuplicate();
    TestRemove();
    TestRemoveNotFound();
    TestSearch();
    TestSearchNotFound();

    printf("All tests passed\n");

    return 0;
}