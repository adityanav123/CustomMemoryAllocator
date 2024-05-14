#include "../MemoryAllocate.h"
#include <stdio.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *head = NULL;

Node *createNewNode(int val) {
  Node *newNode = (Node *)customMalloc(sizeof(Node));
  newNode->data = val;
  newNode->next = NULL;
  return newNode;
}

// insert Node to the end of linked list
void insert(int value) {
  // check if list is empty
  if (head == NULL) {
    // direct add
    head = createNewNode(value);
    return;
  }

  Node *ptr = head;
  while (ptr->next) {
    ptr = ptr->next;
  }

  Node *newNode = createNewNode(value);
  ptr->next = newNode;
}

void see(Node *ptr) {
  if (ptr) {
    printf("%d ", ptr->data);
    see(ptr->next);
  }
}

void convertArrayToList(int *array, int size) {
  for (int i = 0; i < size; ++i) {
    insert(array[i]);
  }
}

int main() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = 10;

  // create list
  convertArrayToList(arr, size);

  see(head);
  printf("\n");

  return 0;
}
