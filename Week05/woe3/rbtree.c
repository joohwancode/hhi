#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil->color = RBTREE_BLACK;
  p->nil = nil;
  p->root = nil;
  return p;
}

void PostOrder(rbtree *t, node_t *p) {
    if(p == t->nil) return;
    PostOrder(t, p->left);
    PostOrder(t, p->right);
    free(p);
}


void delete_rbtree(rbtree *t) {
  PostOrder(t, t->root);
  free(t->nil);
  free(t);
}

//로테이션
void left_rotate(rbtree *t, node_t *x) {
  node_t *x_child = x->right;
  //x의 오른자식으로 y의 왼자식 노드를 받아온다.
  x->right = x_child->left;
  //y의 왼자식 노드가 nil이 아니라면 해당 노드 부모값을 x로 변환
  if (x_child->left != t->nil) x_child->left->parent = x;
  //y의 부모로 x의 부모로 변경
  x_child->parent = x->parent;
  //x의 부모가 nil이라면(즉, 루트 노드라면) 루트 노드는 y가 된다.
  if (x->parent == t->nil) t->root = x_child;
  //x가 x의 부모노드의 왼자식이라면 y가 왼자식이 된다.
  else if (x == x->parent->left) x->parent->left = x_child;
  //x가 x의 부모노드의 오른자식이라면 y가 오른자식이 된다.
  else x->parent->right = x_child;
  //y의 왼자식은 x가 된다.
  x_child->left = x;
  //x의 부모는 y가 된다.
  x->parent = x_child;
}

void right_rotate(rbtree *t, node_t *x) {
  node_t *x_child = x->left;
  //x의 왼자식으로 y의 오른자식 노드를 받아온다.
  x->left = x_child->right;
  //y의 오른자식 노드가 nil이 아니라면 해당 노드 부모값을 x로 변환
  if (x_child->right != t->nil) x_child->right->parent = x;
  //y의 부모로 x의 부모로 변경
  x_child->parent = x->parent;
  //x의 부모가 nil이라면(즉, 루트 노드라면) 루트 노드는 y가 된다.
  if (x->parent == t->nil) t->root = x_child;
  //x가 x의 부모노드의 오른자식이라면 y가 오른자식이 된다.
  else if (x == x->parent->left) x->parent->left = x_child;
  //x가 x의 부모노드의 오른자식이라면 y가 오른자식이 된다.
  else x->parent->right = x_child;
  //y의 오른자식은 x가 된다.
  x_child->right = x;
  //x의 부모는 y가 된다.
  x->parent = x_child;
}
//삽입 수정
void insert_fixup(rbtree *t, node_t *x) {
  //x가 red이기 때문에 부모가 red이면 실행.
  while (x->parent->color == RBTREE_RED) {
    //x의 부모 노드가 red이고, x의 조부모 노드의 다른 자식 노드가 red라면 
    //=> 조부모 노드의 자식들을 black으로 조부모 노드를 red로 바꾼다.
    if (x->parent == x->parent->parent->left) {
      node_t *another = x->parent->parent->right;
      if (another->color == RBTREE_RED){
        x->parent->color = RBTREE_BLACK;
        another->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        x = x->parent->parent;
      }else {
        if (x == x->parent->right) {
          x = x->parent;
          left_rotate(t, x);
        }
        x->parent->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        right_rotate(t,x->parent->parent);
      }
    }
    else if (x->parent == x->parent->parent->right) {
      node_t *another = x->parent->parent->left;
      if (another->color == RBTREE_RED){
        x->parent->color = RBTREE_BLACK;
        another->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        x = x->parent->parent;
      }else {
        if (x == x->parent->left) {
          x = x->parent;
          right_rotate(t, x);
        }
        x->parent->color = RBTREE_BLACK;
        x->parent->parent->color = RBTREE_RED;
        left_rotate(t,x->parent->parent);
      }  
    }
    
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *parent = t->nil;
  node_t *p = t->root;
  while (p != t->nil) {
    parent = p;
    if (p->key > key) p = p->left;
    else p = p->right;
  }
  node_t *insertion_node = (node_t *)calloc(1, sizeof(node_t));
  insertion_node->color = RBTREE_RED;
  insertion_node->key = key;
  insertion_node->parent = parent;
  insertion_node->left = t->nil;
  insertion_node->right = t->nil;
  
  if (parent == t->nil) t->root = insertion_node;
  else if (parent->key > key) parent->left = insertion_node;
  else parent->right = insertion_node;
  insert_fixup(t, insertion_node);
  return insertion_node;
}


node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *p = t->root;
  while (p != t->nil) {
    if (p->key == key) return p;
    if (p->key > key) p = p->left;
    else p = p->right;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *p = t->root;
  while (p->left != t->nil) {
    p = p->left;
  }
  return p;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *p = t->root;
  while (p->right != t->nil) {
    p = p->right;
  }
  return p;
}



void transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) t->root = v;
  else if (u == u->parent->left) u->parent->left = v;
  else u->parent->right = v;
  v->parent = u->parent;
}

void erase_fixup(rbtree *t, node_t *x) {
  node_t *target = x;
  while ((target!= t->root) && (target->color == RBTREE_BLACK)) {
    if (target == target->parent->left) {
      node_t *w = target->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        target->parent->color = RBTREE_RED;
        left_rotate(t, target->parent);
        w = target->parent->right;
      }
      if ((w->left->color == RBTREE_BLACK) && (w->right->color == RBTREE_BLACK)) {
        w->color = RBTREE_RED;
        target = target->parent;
      }
      else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = target->parent->right;
        }
        w->color = target->parent->color;
        target->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, target->parent);
        target = t->root;
      }
    }
    else {
      node_t *w = target->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        target->parent->color = RBTREE_RED;
        right_rotate(t, target->parent);
        w = target->parent->left;
      }
      if ((w->left->color == RBTREE_BLACK) && (w->right->color == RBTREE_BLACK)) {
        w->color = RBTREE_RED;
        target = target->parent;
      }
      else {
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = target->parent->left;
        }
        w->color = target->parent->color;
        target->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, target->parent);
        target = t->root;
      }
    }
  }
  target->color = RBTREE_BLACK;
}

node_t *find_successor(rbtree *t, node_t *p) {
  while (p->left != t->nil) {
    p = p->left;
  }
  return p;  
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *y = p;
  node_t *x;
  color_t y_original_color = y->color;
  if (p->left == t->nil) {
    x = p->right;
    transplant(t, p, p->right);
  }
  else if (p->right == t->nil) {
    x = p->left;
    transplant(t, p, p->left);
  }
  else {
    y = find_successor(t, p->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == p) x->parent = y;
    else {
      transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  if (y_original_color == RBTREE_BLACK) {
    erase_fixup(t, x);
  }
  free(p);
  return 0;
}

void inOrder(const rbtree *t, node_t *p, key_t *arr, const size_t n, int *cnt) {
    if(p == t->nil) return;

    inOrder(t, p->left, arr, n, cnt);
    if (*cnt == n) return;
    arr[*cnt] = p->key;
    *cnt += 1;
    inOrder(t, p->right, arr, n, cnt);
    
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    int cnt = 0;
    int *p = &cnt;
    inOrder(t, t->root, arr, n, p);

    return 0;
}
