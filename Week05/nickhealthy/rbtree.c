#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));

  nilNode->color = RBTREE_BLACK;
  p->nil = nilNode;
  p->root = nilNode;
  return p;
}

void free_node(rbtree *t, node_t *x) {
  // 후위 순회 방식으로 RB Tree 내의 노드 메모리 반환
  if(x != t->nil){

  if (x->left != t->nil)
    free_node(t, x->left);
  if (x->right != t->nil)
    free_node(t, x->right);
  free(x);
  }
  x = NULL;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  node_t *x = t->root;
  
  free_node(t, x);
  free(t->nil);
  free(t);
}

void left_rotate(rbtree *T, node_t *x) {
  node_t *y;

  y = x->right; // y를 설정한다.
  x->right = y->left;   // y의 왼쪽 서브트리를 x의 오른쪽 서브 트리로 옮긴다.

  if (y->left != T->nil)
    y->left->parent = x;

  y->parent = x->parent; // x의 부모를 y로 연결한다.
  
  if (x->parent == T->nil)
    T->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *T, node_t *x) {
  node_t *y;

  y = x->left; // y를 설정한다.
  x->left = y->right;   // y의 왼쪽 서브트리를 x의 오른쪽 서브 트리로 옮긴다.
  
  if (y->right != T->nil)
    y->right->parent = x;

  y->parent = x->parent; // x의 부모를 y로 연결한다.
  
  if (x->parent == T->nil)
    T->root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;

  y->right = x;
  x->parent = y;
  
}

void rbtree_insert_fixup(rbtree* t, node_t* z) {
  node_t *y;

  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;

      // CASE 1: 노드 z의 삼촌 y가 적색인 경우
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      // CASE 2: z의 삼촌 y가 흑색이며 z가 오른쪽 자식인 경우
      else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        // CASE 3: z의 삼촌 y가 흑색이며 z가 오른쪽 자식인 경우
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    else {
      y = z->parent->parent->left;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *y = t->nil;
  node_t *x = t->root; // 현 노드의 위치를 기억하는 포인터
  node_t *z = (node_t *)calloc(1, sizeof(node_t));

  z->key = key;

  /*
    CASE1.
    현 노드(x)의 삽입할 위치를 잡아주는 while문
    x가 nil 값을 만나야 비로서 삽입할 수 있는 위치를 찾음
    while문 탈출 시 x는 nil 노드를 가르키고 있기 때문에 y의 값으로 삽입할 위치를 최종적으로 잡아줌
  */

  /*
    CASE2.
    빈 Tree라면 루트 노드가 처음 삽입할 시 while문에 들어가지 않음
    x가 nil이 아니라면 즉, while문을 들어가게 된다면 노드가 하나 이상 존재하는 트리
  */ 
  while (x != t->nil) {
    y = x; // x 노드의 이전 노드를 기억함
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  
  z->parent = y; // 현 노드(z-parent)에 y 값 저장


  /*
    빈 트리에서 루트를 처음 삽입할 때를 구분하는 if문
    처음 노드를 삽입할 때 y는 nil(NULL 값을 갖는다.)
    즉, while 문을 한번도 돌지 않을 시 진입함
  */
  if (y == t->nil)
    t->root = z; // z 노드를 루트 노드로 삽입

  // 현 노드 z->key 값이 y->key 값보다 작다면
  // y->left에 z 삽입
  else if (z->key < y->key)
    y->left = z;
  
  // 현 노드 z->key 값이 y->key 값보다 크다면
  // y->right에 z 삽입
  else
    y->right = z;

  // RBTREE의 특성을 유지하기 위해서 속성값 부여
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  // (보류)위배 사항 체크 로직 구현
  rbtree_insert_fixup(t, z);

  return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  node_t *curr = t->root;
  while (curr != t->nil) {
    if (curr->key == key) 
      return curr;
    
    if (curr->key < key)
      curr = curr->right;

    else
      curr = curr->left;
  }

  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *z = t->root;
  while (z->left != t->nil) {

    z = z->left;
  }

  return z;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *z = t->root;
  while (z->right != t->nil) {

    z = z->right;
  }

  return z;
}

void rbtree_delete_fixup(rbtree* t, node_t* x) {
  node_t *w;

  while ((x != t->root) && (x->color == RBTREE_BLACK)) {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if ((w->left->color == RBTREE_BLACK) && (w->right->color == RBTREE_BLACK)) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }

    else {
      w = x->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if ((w->right->color == RBTREE_BLACK) && (w->left->color == RBTREE_BLACK)) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}



// 오른쪽 서브트리를 기준으로 가장 작은 값을 리턴하는 함수
node_t* subtree_min(rbtree* t, node_t* p) {
  while (p->left != t->nil) {
    p = p->left;
  }

  return p;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) {
    t->root = v;
  }
  else if (u == u->parent->left) {
    u->parent->left = v;
  }
  else {
    u->parent->right = v;
  }

  v->parent = u->parent;
}

// 테스트 케이스'test_find_erase_fixed' 실행중인데 뭔가 여기서 잘못됨
// segmentation fault 잡아야함
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  // parent y를 nil로 정의
  node_t *x;
  node_t *y;
  color_t yOriginalColor;

  y = p;
  yOriginalColor = y->color;

  if (p->left == t->nil) {
    x = p->right;
    rbtree_transplant(t, p, p->right);
  }
  else if (p->right == t->nil) {
    x = p->left;
    rbtree_transplant(t, p, p->left);
  }
  // [교재 - 4판.ver]
  // else {
  //   y = subtree_min(t, p->right);
  //   yOriginalColor = y->color;
  //   x = y->right;
    
  //   if (y != p->right) {
  //       rbtree_transplant(t, y, y->right);
  //       y->right = p->right;
  //       y->right->parent = y;
  //   }
  //   else {
  //     x->parent = y;
  //   }
  //   rbtree_transplant(t, p, y);
  //   y->left = p->left;
  //   y->left->parent = y;
  //   y->color = p->color;
  // }

  // if (yOriginalColor == RBTREE_BLACK) {
  //   rbtree_delete_fixup(t, x);
  // }

  // // free(p);
  // free(y);

  // [교재 - 3판.ver]
  else {
    y = subtree_min(t, p->right);
    yOriginalColor = y->color;
    x = y->right;

    if (y->parent == p) {
      x->parent = y;
    }
    else {
      rbtree_transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  if (yOriginalColor == RBTREE_BLACK) {
    rbtree_delete_fixup(t, x);
  }

  free(p);

  return 0;
}

// 재귀적으로 중위 순회하여 출력
void make_to_array(const rbtree *t, node_t *curr, key_t *arr, size_t n, size_t *count) {
  if (curr == t->nil)
    return;

  make_to_array(t, curr->left, arr, n, count);
  if (*count < n) {
    arr[(*count)++] = curr->key;
  }
  else return;
  make_to_array(t, curr->right, arr, n, count);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  /*
  - RB tree의 내용을 key 순서대로 주어진 array로 변환
  - array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
  - array의 메모리 공간은 이 함수를 부르는 쪽에서 준비하고 그 크기를 n으로 알려줍니다.
  */
  if (t->root == t->nil)
    return 0;

  size_t count = 0;
  // arr은 동적메모리를 이미 할당함
  make_to_array(t, t->root, arr, n, &count);

  return 0;
}
