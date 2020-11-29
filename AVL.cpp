/**
 * File processing, 2020
 * AVL.cpp
 * implementation of AVL tree
 * 소프트웨어학과 20191666 정주은
 */

#include <stdio.h>
#include <iostream>

/**
 * Node represents a single node in AVL tree.
 */
typedef struct Node {
  int         key, bf;
  struct Node *left, *right;
  Node(int nkey):key(nkey), left(NULL), right(NULL), bf(0){}
  Node(){}

} Node;

typedef Node *Tree;

/**
 * createNode returns a new node.
 * @return a new node
 */
Node *createNode() {
  return new Node();
}
Node *createNode(int newkey) {
  return new Node(newkey);
}

// data를 data로 갖고있는 Node찾는 함수
Node* searchKey(Node* T, int data){
  Node* p = T;
  if(p == NULL){return NULL;}
  if(p->data == data){ return p;}
  else if(p->data < data){return searchKey(p->right, data);}
  else{                   return searchKey(p->left, data);}
}

// data를 data로 갖고 있는 Node의 부모 Node 찾는 함수
Node* searchParent(Node* T, int data, Node* current,Node* parent){
  current = T;
  while(current != NULL){
    if(current->data==data){return parent;}
    parent = current;
    if(current->data < data){current = current->right;}
    else{current=current->left;}
  }
  return NULL;
}

// tree의 높이를 알려주는 함수
int height(Node* T){
  if(T == nullptr){
      return 0;
  }
  int left = height(T->left);
  int right = height(T->right);

  int h =0;
  if(left>right) h = left+1;
  else h = right +1;

  return h;
}

// node의 개수를 알려주는 함수
int numNodes(Node* T){
  int count=0;

  if( T != NULL ){
    count = 1 + numNodes(T->left)+numNodes(T->right);
  }
  return count;
}

// tree에서 최소값을 갖는 노드를 알려주는 함수
Node* minNode(Node* T){
  Node* tmp_t = T;
  while(tmp_t->left !=NULL){
    tmp_t = tmp_t->left;
  }
  return tmp_t;
}

// tree에서 최댓값을 갖는 노드를 알려주는 함수
Node* maxNode(Node* T){
  Node* tmp_t = T;
  while(tmp_t->right !=NULL){
    tmp_t = tmp_t->right;
  }
  return tmp_t;
}

/**
 * updateBF updates balancing factors of nodes in T
 * and finds the unbalanced node nearest to y.
 * @param T: an AVL tree
 * @param y: the inserted/deleted node
 * @param x: the unbalanced node nearest to y
 * @param p: parent node of x
 */
void updateBF(Tree *T, Node *y, Node **x, Node **p) {
  Node* tmp_N = T;
  if(height(tmp_N)==1) { T->bf = 0; return;}
  updateBF(T->left, y, x, p);
  int tmp_bf = height(tmp_N->left)-height(tmp_N->right);
  T->bf = tmp_bf;
  if(x!=NULL&&(tmp_bf==2 || tmp_bf==-2)){*x=&T; }
  update(T->right, y, x, p);
}

/**
 * rotateLL implements LL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLL(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

/**
 * rotateRR implements RR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRR(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

/**
 * rotateLR implements LR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLR(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

/**
 * rotateRL implements RL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRL(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

// use bf and RR, LL, RL, LR rotation to make a balance tree
void balance(Tree *T){

}

/**
 * insertBST inserts newKey into T
 * and returns the inserted node.
 * @param T: a binary search tree
 * @param newKey: a key to insert
 * @return the inserted node
 */
Node *insertBST(Tree *T, int newKey) {
  Node *q=NULL, *tmp_t=T, *newNode;
  while(tmp_t !=NULL){
    if(newKey == tmp_t->data) return T;
    q = tmp_t;
    if(newKey < tmp_t->data) tmp_t = tmp_t->left;
    else tmp_t = tmp_t->right;
  }
  newNode = createNode();
  if(T == NULL){
    T = newNode;
  }else if(newKey < q->data){
    q->left = newNode;
  }else{
    q->right = newNode;
  }
  return T;
}

/**
 * insertAVL inserts newKey into T.
 * @param T: an AVL tree
 * @param newKey: a key to insert
 */
void insertAVL(Tree *T, int newKey) {
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  if(T==NULL){
    T = new Node(newKey);
  }
  T = insertBST(T, newKey);
  Node *tmp_key = createNode();
  updateBF(T, tmp_key, );
  balance(T);  // bf에 따라 노드 재정
}


/**
 * deleteBST deletes deleteKey from T
 * and returns the parent node of the deleted node.
 * @param T: a binary search tree
 * @param deleteKey: a key to delete
 * @return the parent node of the deleted node
 */
}
Node *deleteBST(Tree *T, int deleteKey) {
  Node *p, *q= NULL, *tmp; //q는 p의 부모노드
  int flag =0;
  // key를 갖는 노드 p를 탐색, 이때,p는 현재노드
  p = searchKey(T, deleteKey);
  q = searchParent(T, deleteKey, p, q);

  //노드가 없을 경우
  if(p==NULL){  return T;  }
  if(q==NULL&& p==NULL){T=NULL; return T;}

  //자식노드 0개일 때
  if(( p->left == NULL ) && ( p->right == NULL )){
      if(q==NULL){return NULL;}
      if(q->left == p){q->left = NULL;}
      else{q->right = NULL;}
  }

  // 하나의 자식이 있는 경우
  else if((p->left == NULL) || (p->right == NULL)){
      if(p->left != NULL){
        if(q==NULL){
          if(numNodes(p->left)!=1){
            p->data = maxNode(p->left)->data;
            deleteBST(p->left, p->data);
          }else{p->data = p->left->data; p->left = NULL;}
        }
        else{
          if(q->left == p){q->left = p ->left;}
          else{q->right = p->left;}
        }
      }else{
        if(q==NULL){
          if(numNodes(p->right)!=1){
            p->data = minNode(p->right)->data;
            deleteBST(p->right,p->right->data);
          }else{p->data = p->right->data; p->right = NULL;}
        }
        else{
          if(q->left == p){q->left = p->right;}
          else{q->right = p->right;}
        }
      }
  }
  // 자식이 두개인 경우
  else if((p->left != NULL) && (p->right != NULL)){
    //왼쪽 트리가 더 큰 경우
    if(height(p->left) > height(p->right)){
      tmp = maxNode(p->left); flag =0;
    }
    //오른쪽 트리가 더 큰 경우
    else if(height(p->left) < height(p->right)){
      tmp = minNode(p->right); flag = 1;
    }
    //높이가 같을 경우: 더 개수가 많은 것으로 대//
    else{
      if(numNodes(p->left) >= numNodes(p->right)){
        tmp = maxNode(p->left); flag =0;
      }else{
        tmp = minNode(p->right); flag =1;
      }
    }

    p->data = tmp->data;

    //flag==0: 왼쪽, 1:오른쪽
    if(flag==0){
      tmp = deleteBST(p->left, tmp->data);
      if(tmp==NULL){
        p->left = NULL;
      }
    }
    else{
      tmp = deleteBST(p->right, tmp->data);
      if(tmp==NULL){
        p->right = NULL;
      }
    }
  }
  return T;
}

/**
 * deleteAVL deletes deleteKey from T.
 * @param T: an AVL tree
 * @param deleteKey: a key to delete
 */
void deleteAVL(Tree *T, int deleteKey) {
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  /* write your code here */
}

/**
 * inorderAVL implements inorder traversal in T.
 * @param T: an AVL tree
 */
void inorderAVL(Tree T) {
  if (T == NULL)
      return;

  inorderBST(T->left);
  cout << T->data << " ";
  inorderBST(T->right);
}

int main() {
  /* Do not modify the code below */

  int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };

  Tree T = NULL;

  // insertion
  cout<<"\n\n------------insert1---------------\n\n";
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // deletion
  cout<<"\n\n------------delete1---------------\n\n";
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  T = NULL;

  // reinsertion
  cout<<"\n\n------------insert2---------------\n\n";
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // redeletion
  cout<<"\n\n------------delete2---------------\n\n";
  for (int i=19; 0<=i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}
