#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next, *prev;
} *top;

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = temp->prev = NULL;
  return temp;
}

void push(int value);
void remove();
int peek();
void printStack();

int main() {
  push(8);
  printStack();
  push(4);
  remove();
  printStack();;
  push(10);
  push(12);
  printStack();
  remove();
  remove();
  remove();
  printStack();

  int topValue = peek();

  if(topValue == -1) puts("There's no node in the stack.");
  else printf("Top Value: %d\n", topValue);
  return 0;
}

void push(int value) {
  Node *temp = createNode(value);
  if(!top) top = temp; // 0 node
  else {
    top->prev = temp;
    temp ->next = top;
    top = temp;
  }
}

void remove() {
  if(!top) return; // 0 node
  else if(top && top->next == NULL) {
    free(top);
    top = NULL;
  } // 1 node
  else { // > 1 node
    Node *temp = top->next;
    top->next = temp->prev = NULL;
    free(top);
    top = temp;
  }
}

int peek() { // cek ada top apa tidak
  return (top) ? top->value : -1;
}

void printStack() {
  if(!top) {
    puts("Kosong");
    return;
  }
  else {
    Node *curr = top;
    puts("Stack:");
    while(curr) {
      printf("%d\n", curr->value);
      curr = curr->next;
    }
    puts("");
  }
}

void maxValue() {
  Node *curr = top;
  int max = curr->value;

  while(curr && curr->value > max) {
    if(curr->value > max) max = curr->value;
    curr = curr->next;
  }
}

void minValue() {
  Node *curr = top;
  int min = curr->value;

  while(curr && curr->value < min) {
    if(curr->value < min) min = curr->value;
    curr = curr->next;
  }
}