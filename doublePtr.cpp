#include <iostream>
#include <iomanip>
using namespace std;

struct Node {
  // Node *prev;
  Node *next;
  int data;
};

typedef Node *Tree;

Node *CreateNode(int data) {
  Node *p = new Node();
  p->data = data;
  p->next = NULL;
  return p;
}

void PrependNode(Node **head, Node *newNode) {
  newNode->next = *head;
  *head = newNode;
}

void AppendNode(Node **tail, Node *newNode) {
  while (*tail) {
      tail = &(*tail)->next;
  }
  newNode->next = *tail;
  *tail = newNode;
}

void PrintList(Node *Root) {
  if(Root !=NULL) {
    cout << Root->data << setw(4);
    PrintList(Root->next);
  }
}

Node *DeRoot(Node *Root, int data) {

}

int main() {
  int a[] ={6, 4, 10};

  Node *head = CreateNode(10);

  PrependNode(&head, CreateNode(89));
  PrependNode(&head, CreateNode(55));
  AppendNode(&head, CreateNode(33));

  PrintList(head);
}