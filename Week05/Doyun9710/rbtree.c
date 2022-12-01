#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#define SENTINEL

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));

  nilNode->color = RBTREE_BLACK;
  p->nil = nilNode;
  p->root = nilNode;

  return p;
}

void left_rotate(rbtree *tree, node_t *x) {

  node_t *y;

  y = x->right;
  x->right = y->left;

  if (y->left != tree->nil)
    y->left->parent = x;

  y->parent = x->parent;

  if (x->parent == tree->nil)
    tree->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *tree, node_t *x) {

  node_t *y;

  y = x->left;
  x->left = y->right;

  if (y->right != tree->nil)
    y->right->parent = x;

  y->parent = x->parent;

  if (x->parent == tree->nil)
    tree->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->right = x;
  x->parent = y;
}

void free_node(rbtree *t, node_t *x) {

  if (x->left != t->nil)
    free_node(t, x->left);
  if (x->right != t->nil)
    free_node(t, x->right);
  free(x);
  x = NULL;
}

void delete_rbtree(rbtree *t) {

  if (t->root != t->nil)
    free_node(t, t->root);
  free(t->nil);
  free(t);
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {

  node_t *y;

  while (z->parent->color == RBTREE_RED) {

    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;

      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }

      else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }

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
  node_t *x = t->root;
  node_t *z = (node_t *)calloc(1, sizeof(node_t));

  z->key = key;

  while (x != t->nil) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;

  if (y == t->nil)
    t->root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  rbtree_insert_fixup(t, z);

  return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *current = t->root;

  while (current != t->nil) {
    if (current->key == key)
      return current;

    if (current->key < key)
      current = current->right;
    else
      current = current->left;
  }

  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find

  node_t *target = t->root;

  if (t->root == t->nil)
    return NULL;

  while (target->left != t->nil) {
    target = target->left;
  }

  return target;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find

  node_t *target = t->root;

  if (t->root == t->nil)
    return NULL;

  while (target->right != t->nil) {
    target = target->right;
  }

  return target;
}

// 12.3 이진검색트리 삽입과 삭제 (참고 299p)
// transplant : 이식하다
// node u가 root인 서브 트리를 node v가 root인 서브 트리로 교체
void rbtree_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  // v->parent = u->parent;
  v->parent = u->parent;
}

// 수행시간 = tree-height = O(lg n)
void rbtree_delete_fixup(rbtree *t, node_t *x) {

  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      // w = x 의 삼촌 (부모의 형제)
      node_t *w = x->parent->right;

      // 경우 1 : x의 형제 w가 적색인 경우
      // ? <- Red -> ?
      // w->color <-> x->parent->color
      // x->parent 기준 좌회전
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      // 경우 2 : x의 형제 w는 흑색이고 w의 두 지식이 모두 흑색인 경우
      // Black <- Black -> Black
      // w의 자식이 모두 RBTREE_BLACK
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }

      // 경우 3 : x의 형제 w는 흑색, w의 왼쪽 자식은 적색, w의 오른쪽 자신은 흑색인 경우
      // Red <- Black -> Black
      // w->color <-> w->left->color 후 right_rotate
      else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }

        // 경우 4 : x의 형제 w는 흑색이고 w의 오른쪽 자식은 적색인 경우
        // ? <- Black -> Red
        // w->color <-> w->parent->color 후 left_rotate
        // w_original_color = RBTREE_BLACK 이었기 때문. 색 교환
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK; 
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    } 
    else {
      node_t *w = x->parent->left;

      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
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

// p => (variable in book 600p) z
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase

  node_t *x;
  node_t *y;
  node_t *z = p;

  color_t y_original_color;

  // Error!!!
  // y = z->parent;
  y = z;
  y_original_color = y->color;

  if (z->left == t->nil) {
    x = z->right;
    rbtree_transplant(t, z, z->right);
  } 
  else if (z->right == t->nil) {
    x = z->left;
    rbtree_transplant(t, z, z->left);
  } 
  else { 
    // 삭제 노드 z의 자식 노드 중 어느 하나도 nil이 아닐 경우
    // y = rbtree_max(z->left); 는 안되는가? 될 것 같은데?
    // rbtree(rbtree != node)
    // y = rbtree_min(t);
    y = z->right;
    while (y->left != t->nil) {
      // printf("%p", y);
      y = y->left;
    }
    y_original_color = y->color;
    x = y->right;

    if (y->parent == z)
      x->parent = y;
    else {
      rbtree_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (y_original_color == RBTREE_BLACK)
    rbtree_delete_fixup(t, x);

  free(p);

  return 0;
}
/*
// z => (original variable) p
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *y;
  node_t *x;

  color_t y_original_color;

  y = p;
  y_original_color = y->color;

  if (p->left == t->nil) {
    x = p->right;
    rbtree_transplant(t, p, p->right);
  }
  else if (p->right == t->nil) {
    x = p->left;
    rbtree_transplant(t, p, p->left);
  }
  else {
    y = p->right;
    while(y->left != t->nil){
      y = y->left;
    }
    y_original_color = y->color;
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

  if (y_original_color == RBTREE_BLACK) {
    rbtree_delete_fixup(t, x);
  }

  free(p);

  return 0;
}
*/

void recursion_rbtree_to_array(const rbtree *t, node_t *current, key_t *arr, size_t n, size_t *count) {
  // 트리 t, 현재(검사) 노드 current, key 복사할 배열 arr, arr의 길이 n, 반복할 횟수 count

  // node_t *target  = t->root;
  // size_t count = 0;

  if (current == t->nil)
    return;

  // recursion_rbtree_to_array(t, arr, n, count);
  recursion_rbtree_to_array(t, current->left, arr, n, count);

  if (*count < n)
    arr[(*count)++] = current->key;
  else
    return;

  recursion_rbtree_to_array(t, current->right, arr, n, count);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  if (t->root == t->nil)
    return 0;

  // tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
  // for (count < n) ==> n번 반복
  size_t count = 0;

  // 재귀 필요! create recusion function
  // if (t->root == t->nil)
  //   return;
  // rbtree_to_array();

  // count 변경되므로 &count
  // left, right 분리 후 recursion
  recursion_rbtree_to_array(t, t->root, arr, n, &count);

  return 0;
}