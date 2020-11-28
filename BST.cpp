/*
소프트웨어학과 20191666 정주은
프로그램 명: BST 구현
*/

#include <iostream>

using namespace std;

// Node 구조체 만들기
struct Node{
  int data;
  struct Node* left;
  struct Node* right;
  Node* operator=(Node* a){
    this->data = a->data;
    this->left = a->left;
    this->right = a->right;
  }
};

Node *getNode() {
  return new Node();
}

Node* insertBST(Node* Tree, int newKey);
Node* deleteBST(Node* Tree, int deleteKey);
void inorderBST(Node* Tree);
int height(Node* Tree);
int noNodes(Node* Tree);
Node* minNodes(Node* Tree);
Node* maxNodes(Node* Tree);
Node* searchKey(Node* Tree, int data);
Node* searchParent(Node* Tree, int data, Node* current,Node* parent);

int main(){
  Node* T = NULL;

  cout<<"----------insert1-------\n\n";

  int a[] = {25, 500, 33 , 17, 49, 403, 29, 105, 39, 66, 305, 44, 19, 441, 390, 12, 81, 50, 100, 999};
  for(int i=0; i<20; i++){T =insertBST(T, a[i]); inorderBST(T); cout<<"\n";}

  // deleteBST
  cout<<"\n\n----------delete1-------\n\n";
  for(int i=0; i<20; i++){T = deleteBST(T, a[i]); inorderBST(T); cout<<"\n";}

  int b[] = {999, 100, 50, 81, 12, 390, 441, 19, 44, 305, 66, 39, 105, 29, 403, 49, 17, 33, 500, 25};

  cout<<"\n\n----------insert2-------\n\n";
  for(int i=0; i<20; i++){T =insertBST(T, b[i]); inorderBST(T); cout<<"\n";}

  //deleteBST
  cout<<"\n\n----------delete2-------\n\n";
  for(int i=0; i<20; i++){T = deleteBST(T, b[i]); inorderBST(T); cout<<"\n";}
  return 0;

}

// BST를 만드는 함수.
Node* insertBST(Node* Tree, int newKey){
  Node *q=NULL, *tmp_t=Tree, *newNode;
  while(tmp_t !=NULL){
    if(newKey == tmp_t->data) return Tree;
    q = tmp_t;
    if(newKey < tmp_t->data) tmp_t = tmp_t->left;
    else tmp_t = tmp_t->right;
  }
  newNode = getNode();
  newNode->data = newKey;
  newNode->left = NULL; newNode->right = NULL;
  if(Tree == NULL){
    Tree = newNode;
  }else if(newKey < q->data){
    q->left = newNode;
  }else{
    q->right = newNode;
  }
  return Tree;
}


// 특정 키 값을 갖는 노드를 삭제하는 함수
Node* deleteBST(Node* Tree, int deleteKey){
  Node *p, *q= NULL, *tmp; //q는 p의 부모노드
  int flag =0;
  // key를 갖는 노드 p를 탐색, 이때,p는 현재노드
  p = searchKey(Tree, deleteKey);
  q = searchParent(Tree, deleteKey, p, q);

  //노드가 없을 경우
  if(p==NULL){  return Tree;  }
  if(q==NULL&& p==NULL){Tree=NULL; return Tree;}

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
          if(noNodes(p->left)!=1){
            p->data = maxNodes(p->left)->data;
            deleteBST(p->left, p->data);
          }else{p->data = p->left->data; p->left = NULL;}
        }
        else{
          if(q->left == p){q->left = p ->left;}
          else{q->right = p->left;}
        }
      }else{
        if(q==NULL){
          if(noNodes(p->right)!=1){
            p->data = minNodes(p->right)->data;
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
      tmp = maxNodes(p->left); flag =0;
    }
    //오른쪽 트리가 더 큰 경우
    else if(height(p->left) < height(p->right)){
      tmp = minNodes(p->right); flag = 1;
    }
    //높이가 같을 경우: 더 개수가 많은 것으로 대//
    else{
      if(noNodes(p->left) >= noNodes(p->right)){
        tmp = maxNodes(p->left); flag =0;
      }else{
        tmp = minNodes(p->right); flag =1;
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
  return Tree;
}

// data를 data로 갖고있는 Node찾는 함수
Node* searchKey(Node* Tree, int data){
  Node* p = Tree;
  if(p == NULL){return NULL;}
  if(p->data == data){ return p;}
  else if(p->data < data){return searchKey(p->right, data);}
  else{                   return searchKey(p->left, data);}
}

// data를 data로 갖고 있는 Node의 부모 Node 찾는 함수
Node* searchParent(Node* Tree, int data, Node* current,Node* parent){
  current = Tree;
  while(current != NULL){
    if(current->data==data){return parent;}
    parent = current;
    if(current->data < data){current = current->right;}
    else{current=current->left;}
  }
  return NULL;
}

// tree의 높이를 알려주// 함수
int height(Node* Tree){
  if(Tree == nullptr){
      return 0;
  }
  int left = height(Tree->left);
  int right = height(Tree->right);

  int h =0;
  if(left>right) h = left+1;
  else h = right +1;

  return h;
}

// node의 개수를 알려주는 함수
int noNodes(Node* Tree){
  int count=0;

  if( Tree != NULL ){
    count = 1 + noNodes(Tree->left)+noNodes(Tree->right);
  }
  return count;
}

// tree에서 최소값을 갖는 노드를 알려주는 함수
Node* minNodes(Node* Tree){
  Node* tmp_t = Tree;
  while(tmp_t->left !=NULL){
    tmp_t = tmp_t->left;
  }
  return tmp_t;
}

// tree에서 최댓값을 갖는 노드를 알려주는 함수
Node* maxNodes(Node* Tree){
  Node* tmp_t = Tree;
  while(tmp_t->right !=NULL){
    tmp_t = tmp_t->right;
  }
  return tmp_t;
}

// print BST
void inorderBST(Node* Tree){
  if (Tree == NULL)
      return;

  inorderBST(Tree->left);
  cout << Tree->data << " ";
  inorderBST(Tree->right);
}
