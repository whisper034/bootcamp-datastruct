#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  int height;
  Node *left, *right;
};

int max(int a, int b);
int getHeight(Node *root);
int getBalanceFactor(Node *root);
int computeNewHeight(Node *root);

Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *z = y->left;
  y->left = x;
  x->right = z;
  x->height = computeNewHeight(x);
  y->height = computeNewHeight(y);
  return y;
}

Node *rightRotate(Node *x) {
  Node *y = x->left;
  Node *z = y->right;
  y->right = x;
  x->left = z;
  x->height = computeNewHeight(x);
  y->height = computeNewHeight(y);
  return y;
}

Node *rotation(Node *root) {
  // tentukan tinggi root baru pakai compute new height
  // cari BF (Balanced Factor) root, BF lrft, BF right
  // balanced || unbalanced --> tentukan tipe rotasi
  // buat function leftRotate dan rightRotate
  root->height = computeNewHeight(root);
  int BFRoot = getBalanceFactor(root);
  int BFLeft = getBalanceFactor(root->left);
  int BFRight = getBalanceFactor(root->right);
  if(BFRoot > 1 && BFLeft >= 0) return rightRotate(root);
  else if(BFRoot > 1 && BFLeft < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  else if(BFRoot < -1 && BFRight <= 0) return leftRotate(root);
  else if(BFRoot < -1 && BFRight > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

Node *createNode(int value) {
  Node *temp = (Node*) malloc(sizeof(Node));
  temp->value = value;
  temp->height = 1;
  temp->left = temp->right = NULL;
  return temp;
}

Node *insertNode(Node *root, int value) {
  if(!root) return createNode(value);
  else if(value < root->value) root->left = insertNode(root->left, value);
  else if(value > root->value) root->right = insertNode(root->right, value);
  return rotation(root);
}

Node *predecessor(Node *root) {
  Node *curr = root->left;
  while(curr && curr->right) {
    curr = curr->right;
  }
  return curr;
}

Node *deleteNode(Node *root, int value) {
  if(!root) return root;
  else if(value < root->value) root->left = deleteNode(root->left, value);
  else if(value > root->value) root->right = deleteNode(root->right, value);
  else {
    if(!root->left || !root->right) {
      Node *newRoot = root->left ? root->left : root->right;
      free(root);
      root = NULL;
      return newRoot;
  }

  Node *temp = predecessor(root);
  root->value = temp->value;
  root->left = deleteNode(root->left, temp->value);
  }

  return (root) ? rotation(root) : root;
}

void inOrder(Node *root);

int main() {
  Node *baseRoot = NULL;

  baseRoot = insertNode(baseRoot, 9);
  baseRoot = insertNode(baseRoot, 1);
  baseRoot = insertNode(baseRoot, 100);
  baseRoot = insertNode(baseRoot, 67);
  baseRoot = insertNode(baseRoot, 3);
  baseRoot = insertNode(baseRoot, 25);
  baseRoot = insertNode(baseRoot, 14);
  baseRoot = insertNode(baseRoot, 50);
  inOrder(baseRoot);

  return 0;
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf("Height %d, Value %d\n", root->height, root->value);
    inOrder(root->right);
  }
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

int getHeight(Node *root) {
  return (root) ? root->height : 0;
}

int getBalanceFactor(Node *root) {
  return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

int computeNewHeight(Node *root) {
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}