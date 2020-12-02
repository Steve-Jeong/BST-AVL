#include <iostream>

using namespace std;

struct Node {
  int data;
};

void swapNode(Node **a, Node **b) {
  Node *temp = new Node();
  temp= *a;
  *a = *b;
  *b = temp;
}

void swapInt(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main() {
  Node *a = new Node();
  a->data=3;
  cout << "a address : " << a << endl;

  Node *b = new Node();
  b->data=4;
  cout << "b address : " << b << endl;

  cout << "a : " << a->data << ", b : " << b->data << endl;
  swapNode(&a, &b);
  cout << "a address : " << a << endl;
  cout << "b address : " << b << endl;
  cout << "a : " << a->data << ", b : " << b->data << endl<<endl<<endl;

  int c=3, d=4;
  cout << "c address : " << &c << endl;
  cout << "d address : " << &d << endl;
  cout << "c : " << c << ", d : " << d << endl;
  swapInt(&c, &d);
  cout << "c : " << c << ", d : " << d << endl;
  cout << "c address : " << &c << endl;
  cout << "d address : " << &d << endl;
}