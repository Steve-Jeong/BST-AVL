/*
소프트웨어학과 20191666 정주은
프로그램 명: BST 구현
*/

#include <iostream>

using namespace std;

// Node 구조체 만들기
struct Node
{
  int data;
  struct Node *left=NULL;
  struct Node *right=NULL;
  struct Node *parent=NULL;
  Node(int data) {
    this->data = data;
  }
  // Node *operator=(Node *a)
  // {
  //   this->data = a->data;
  //   this->left = a->left;
  //   this->right = a->right;
  //   this->parent = a->parent;
  //   return this;
  // }
};

Node *createNode(int data)
{
  return new Node(data);
}

Node *insertBST(Node *Tree, int newKey);
Node *deleteBST(Node *Tree, int deleteKey);
void inorderBST(Node *Tree);
int height(Node *Tree);
int numNodes(Node *Tree);
Node *minNode(Node *Tree);
Node *maxNode(Node *Tree);
Node *searchKey(Node *Tree, int data);
Node *searchParent(Node *Tree, int data, Node *current, Node *parent);

int main()
{
  Node *T = NULL;

  cout << "----------insert1-------\n\n";

  int a[] = {25, 500, 33 , 17, 49, 403, 29, 105, 39, 66, 305, 44, 19, 441, 390, 12, 81, 50, 100, 999};
  for (int i = 0; i < sizeof(a)/sizeof(int); i++)
  {
    T = insertBST(T, a[i]);
    inorderBST(T);
    cout << "\n";
  }

  // deleteBST
  cout << "\n\n----------delete1-------\n\n";
  for (int i = 0; i < sizeof(a)/sizeof(int); i++)
  {
    inorderBST(T);
    deleteBST(T, a[i]);
    cout << "\n";
  }

  T = NULL;
  int b[] = {999, 100, 50};

  cout << "\n\n----------insert2-------\n\n";
  for (int i = 0; i < sizeof(b)/sizeof(int); i++)
  {
    T = insertBST(T, b[i]);
    inorderBST(T);
    cout << "\n";
  }

  //deleteBST
  cout << "\n\n----------delete2-------\n\n";
  for (int i = 0; i < sizeof(b)/sizeof(int); i++)
  {
    inorderBST(T);
    deleteBST(T, b[i]);
    cout << "\n";
  }
  return 0;
}

// BST를 만드는 함수.
Node *insertBST(Node *Tree, int newKey)
{
  if(Tree == NULL) {
    Tree = createNode(newKey);
  } 
  else {
    Node *Parent;
    Parent = Tree;
    if(Tree->data > newKey) {
      Tree->left = insertBST(Tree->left, newKey);
      Tree->left->parent = Parent;
    } else if(Tree->data < newKey) {
      Tree->right = insertBST(Tree->right, newKey);
      Tree->right->parent = Parent;
    }
  }
  return Tree;
}

// 특정 키 값을 갖는 노드를 삭제하는 함수
Node *deleteBST(Node *Tree, int deleteKey)
{
  Node *tmp_T, *current = NULL;

  if(Tree == NULL) return NULL;

  if(Tree->data > deleteKey)
    current = deleteBST(Tree->left, deleteKey);
  else if(Tree->data < deleteKey)
    current = deleteBST(Tree->right, deleteKey);
  else {
    current = Tree;
    Node *Parent = Tree->parent;

    // 자식노드가 없는 경우
    if(Tree->left==NULL && Tree->right==NULL) {
      if(Parent != NULL) {
        if(Parent->left==Tree)
          Parent->left = NULL;
        else
          Parent->right = NULL;
        delete Tree;
      }
      Tree = NULL;
    }

    //자식노드가 한개인 경우
    else if(Tree->left == NULL || Tree->right == NULL) {
      tmp_T = NULL;
      if(Tree->left != NULL)
        tmp_T = Tree->left;
      else
        tmp_T = Tree->right;

      if(Parent != NULL) {
        if(Parent->left == Tree) {
          Parent->left = tmp_T;
        }
        else {
          Parent->right = tmp_T;
        }
        tmp_T->parent = Parent;
      } else {
        Tree = tmp_T;
        Tree->parent = NULL;
        cout<<"hello"<<endl;
      }
    }

    //자식노드가 두개인 경우
    else {
      int leftHeight, rightHeight;

      leftHeight = height(Tree->left);
      rightHeight = height(Tree->right);
      if(leftHeight < rightHeight) 
        tmp_T = minNode(Tree->right);
      else 
        tmp_T = maxNode(Tree->left);

      Tree->data = tmp_T->data;
      tmp_T = deleteBST(tmp_T, tmp_T->data);
    }
  }
  return current;
}

// data를 data로 갖고있는 Node찾는 함수
Node *searchKey(Node *Tree, int data)
{
  Node *current = Tree;
  if (current == NULL)
  {
    return NULL;
  }
  if (current->data == data)
  {
    return current;
  }
  else if (current->data < data)
  {
    return searchKey(current->right, data);
  }
  else
  {
    return searchKey(current->left, data);
  }
}

// data를 data로 갖고 있는 Node의 부모 Node 찾는 함수
Node *searchParent(Node *Tree, int data, Node *current, Node *parent)
{
  current = Tree;
  while (current != NULL)
  {
    if (current->data == data)
    {
      return parent;
    }
    parent = current;
    if (current->data < data)
    {
      current = current->right;
    }
    else
    {
      current = current->left;
    }
  }
  return NULL;
}

// tree의 높이를 알려주는 함수
int height(Node *Tree)
{
  if (Tree == NULL)
  {
    return 0;
  }
  int left = height(Tree->left);
  int right = height(Tree->right);

  int h = 0;
  if (left > right)
    h = left + 1;
  else
    h = right + 1;

  return h;
}

// node의 개수를 알려주는 함수
int numNodes(Node *Tree)
{
  int count = 0;

  if (Tree != NULL)
  {
    count = 1 + numNodes(Tree->left) + numNodes(Tree->right);
  }
  return count;
}

// tree에서 최소값을 갖는 노드를 알려주는 함수
Node *minNode(Node *Tree)
{
  Node *current = Tree;
  while (current->left != NULL)
  {
    current = current->left;
  }
  return current;
}

// tree에서 최댓값을 갖는 노드를 알려주는 함수
Node *maxNode(Node *Tree)
{
  Node *current = Tree;
  while (current->right != NULL)
  {
    current = current->right;
  }
  return current;
}

// print BST
void inorderBST(Node *Tree)
{
  if (Tree == NULL)
    return;

  inorderBST(Tree->left);
  cout << Tree->data << " ";
  inorderBST(Tree->right);
}
