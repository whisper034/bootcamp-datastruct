#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int num;
  Node* next;
} *head, *tail;

Node * createNode(int num) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->num = num;
  newNode->next = NULL;
  return newNode;
}

void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void pushHead(int num);
void printLinkedList();

int main() {

  return 0;
}

void merge(int arr[], int l, int m, int r) {
  int temp[r - l + 1], p1 = l, p2 = m + 1, k = 0;
  while(p1 <= m && p2 <= r) {
    if(arr[p1] > arr[p2]) {
        temp[k++] = arr[p1++];
    }
    else {
         temp[k++] = arr[p2++];
    }
  }
  while(p1 <= m) {
    temp[k++] = arr[p1++];
  }
  for(int i = 0; i < k; i++) {
    arr[i + l] = temp[i];
  }
}

void mergeSort(int arr[], int l, int r) {
  if(l != r) {
    int m = (l + r) / 2;
      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);
      merge(arr, l, m, r);
  }
}

void pushHead(int num) {
  Node *temp = createNode(num);
  if(!head) head = tail = temp;
  else {
    temp->next = head;
    head = temp;
  }
}

void printLinkedList() {
  Node *curr = head;
  while(curr) {
    printf("%d\n", curr->num);
    curr->next;
  }
}