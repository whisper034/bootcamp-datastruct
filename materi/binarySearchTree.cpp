#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *left, *right;
};

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->left = temp->right = NULL;
  return temp;
}

Node *insertNode(Node *root, int value) {
  if(!root) return createNode(value);
  else if(value < root->value) root->left = insertNode(root->left, value);
  else if(value > root->value) root->right = insertNode(root->right, value);
  return root;
}

Node *minValueNode(Node *root) {
  Node *curr = root->right;
  while(curr && curr->left) {
    curr = curr->left;
  }
  return curr;
}

Node *deleteNode(Node *root, int value) {
  if(!root) return root;
  else if(value < root->value) root->left = deleteNode(root->left, value);
  else if(value > root->value) root->right = deleteNode(root->right, value);
  else {
    if(!root->left) {
      Node *newRoot = root->right;
      free(root);
      root = NULL;
      return newRoot;
    }
    else if(!root->right) {
      Node *newRoot = root->left;
      free(root);
      root = NULL;
      return newRoot;
    }

    // kasus 2 anak
    Node *minValueRightSubtree = minValueNode(root);
    root->value = minValueRightSubtree->value;
    root->right = deleteNode(root->right, minValueRightSubtree->value);
  }
  return root;
}

bool searchNode(Node *root, int key);
void inOrder(Node *root);
void preOrder(Node *root);
void postOrder(Node *root);


int main() {
  // if(searchNode(baseRoot, 15)) puts("Duplicate key detected.");
  Node *baseRoot = NULL;
  baseRoot = insertNode(baseRoot, 10);
  baseRoot = insertNode(baseRoot, 13);
  baseRoot = insertNode(baseRoot, 16);
  baseRoot = insertNode(baseRoot, 5);
  baseRoot = insertNode(baseRoot, 21);
  baseRoot = insertNode(baseRoot, 4);
  baseRoot = insertNode(baseRoot, 7);
  // baseRoot = deleteNode(baseRoot, 5);
  // baseRoot = deleteNode(baseRoot, 10);
  baseRoot = deleteNode(baseRoot, 13);
  baseRoot = deleteNode(baseRoot, 16);
  // baseRoot = deleteNode(baseRoot, 4);
  // baseRoot = deleteNode(baseRoot, 21);
  baseRoot = deleteNode(baseRoot, 7);
  inOrder(baseRoot);

  return 0;
}

bool searchNode(Node *root, int key) {
  if(root->value == key) return true;
  else if(key < root->value) return searchNode(root->left, key);
  else if(key > root->value) return searchNode(root->right, key);
  return false;
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf("%d ", root->value);
    inOrder(root->right);
  }
}

void preOrder(Node *root) {
  if(root) {
    printf("%d ", root->value);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void postOrder(Node *root) {
  if(root) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->value);
  }
}