#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../models/models.h"

Node *createNode(Character c) {
  Node *temp = (Node*)malloc(sizeof(Node));
  strcpy(temp->c.name, c.name);
  strcpy(temp->c.job, c.job);
  temp->c.level = c.level;
  temp->c.damage = c.damage;
  temp->left = temp->right = NULL;
  return temp;
}

Node *insertNode(Node *root, Character c) {
  if(!root) return createNode(c);
  else if(c.damage < root->c.damage) root->left = insertNode(root->left, c);
  else if(c.damage > root->c.damage) root->right = insertNode(root->right, c);
  return root;
}

void preOrder(Node *root) {
  if(root) {
    printf(" %d", root->c.damage);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf(" %d", root->c.damage);
    inOrder(root->right);
  }
}

void postOrder(Node *root) {
  if(root) {
    postOrder(root->left);
    postOrder(root->right);
    printf(" %d", root->c.damage);
  }
}

void printDamage(Node *root) {
  preOrder(root);
  inOrder(root);
  postOrder(root);
}

void printData(Node *root) {
  // printf(" |   Name   |   Job   |   level   |   Damage   |");
  if(root) {
    printf("> %s | %s | lvl. %d | damage: %d\n", root->c.name, root->c.job, root->c.level, root->c.damage);
    printData(root->left);
    printData(root->right);
  }
}

void popAll(Node *root) {
  if(root) {
    popAll(root->left);
    popAll(root->right);
    free(root);
    root = NULL;
  }
}