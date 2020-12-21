#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  char name[255];
  int score;
  Node *next;
} *head, *tail;

Node *createNode(const char *name, int score) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->score = score;
  newNode->next = NULL;
  return newNode;
}

void pushHead(const char *name, int score);
void pushTail(const char *name, int score);
void popHead();
void popTail();
void printLinkedList();

int main() {
  pushHead("Darnell", 95);
  pushTail("whisper0", 97);
  pushHead("pai", 100);
  pushHead("romario", 98);
  pushTail("vincent", 94);
  pushTail("denny", 93);

  printLinkedList();
  return 0;
}

void pushHead(const char *name, int score) {
  Node *temp = createNode(name, score);
  if(!head) head = tail = temp;
  else {
    temp->next = head;
    head = temp;
  }
}

void pushTail(const char *name, int score) {
  Node *temp = createNode(name, score);
  if(!head) head = tail = temp;
  else {
    tail->next = temp;
    tail = temp;
  }
}

void printLinkedList() {
  Node *curr = head;
  puts("Nama           Score");
  while(curr) {
    printf("%-15s %d\n", curr->name, curr->score);
    curr = curr->next;
  }
}

void popHead() {
  if(!head) return;
  else {
    Node *temp = head;
    head = temp->next;
    temp->next = NULL;
    free(temp);
  }
}

void popTail() {
  if(!head) return;
  else if(head == tail) free(head);
  else {
    Node *temp = head;
    while(temp->next != tail) {
      temp = temp->next;
    }
    temp->next = NULL;
    free(tail);
    tail = temp;
  }
}