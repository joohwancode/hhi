#include "rbtree.h"
#include <stdlib.h>

void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
void insert_fixup(rbtree *t, node_t *x);
void inorder_tree_walk(const rbtree *t, node_t *x, key_t *arr, int *i, const size_t n);
void delete_rbtree_helper(rbtree *t, node_t *x);
void delete_fixup(rbtree *t, node_t *x);
void transplant(rbtree *t, node_t *u, node_t *v);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  // init rbtree
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
  NIL->color = RBTREE_BLACK;
  p->root = NIL;
  p->nil = NIL;

  return p;
}

void delete_rbtree(rbtree *t) {
  if (t->root != t->nil) {
    delete_rbtree_helper(t, t->root);
    free(t->root);
  }

  free(t->nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // 노드는 힙에 할당해야 함.
  // 이렇게 동적 할당하지 않으면 본 함수가 종료될 때 노드도 사라지게 되기 떄문.
  node_t *new_node = (node_t*)malloc(sizeof(node_t));

  new_node->key = key;
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->parent = t->nil;
  new_node->color = RBTREE_RED;

  if (t->root == t->nil) {
    t->root = new_node;
    new_node->parent = t->nil;
  }
  else {
    node_t *curr = t->root;

    while (curr != t->nil) {
      if (key <= curr->key) {
        if (curr->left == t->nil) {
          curr->left = new_node;
          new_node->parent = curr;
          break;
        }
        else {
          curr = curr->left;
          continue;
        }
      }
      else {
        if (curr->right == t->nil) {
          curr->right = new_node;
          new_node->parent = curr;
          break;
        }
        else {
          curr = curr->right;
          continue;
        }
      }
    }
  }

  // 2번 또는 4번 규칙을 위반했을 가능성이 있으므로
  // insert_fixup을 통해 위반사항 정정
  insert_fixup(t, new_node);

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *p = t->root;

  while (1) {
    if (p == t->nil) {
      return NULL;
    }
    if (key == p->key) {
      return p;
    }
    if (key < p->key) {
      p = p->left;
    }
    else {
      p = p->right;
    }
  }
}

node_t *rbtree_min(const rbtree *t) {
  if (t->root == t->nil) {
    return NULL;
  }

  node_t *p = t->root;

  while (p->left != t->nil) {
    p = p->left;
  }

  return p;
}

node_t *rbtree_max(const rbtree *t) {
  if (t->root == t->nil) {
    return NULL;
  }

  node_t *p = t->root;

  while (p->right != t->nil) {
    p = p->right;
  }

  return p;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // * phase1: 노드를 삭제한다.
  node_t *target = p;
  color_t original_color = p->color;
  node_t *x;

  if (p->left == t->nil) {
    x = p->right;
    transplant(t, p, p->right);
  }
  else if (p->right == t->nil) {
    x = p->left;
    transplant(t, p, p->left);
  }
  else {
    node_t *tmp = p->right;

    while (tmp->left != t->nil) {
      tmp = tmp->left;
    }

    target = tmp;

    original_color = target->color;
    x = target->right;

    if (target->parent == p) {
      x->parent = target;
    }
    else {
      transplant(t, target, target->right);
      target->right = p->right;
      target->right->parent = target;
    }
    transplant(t, p, target);
    target->left = p->left;
    target->left->parent = target;
    target->color = p->color;
  }

  // * phase2: RB Tree를 재조정한다. (target_color가 red일 경우엔 skip)
  if (original_color == RBTREE_BLACK) {
    delete_fixup(t, x);
  }

  free(p);

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  int i = 0;
  inorder_tree_walk(t, t->root, arr, &i, n);

  return 0;
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *right_node = x->right;

  // right_node의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 옮긴다.
  x->right = right_node->left; // 부모 측(x)에서 자식 재설정
  // 자식 측(right_node->left)에서 부모를 x로 재설정
  if (right_node->left != t->nil) {
    right_node->left->parent = x;
  }

  // 우선은 자식 쪽(right_node)에서만 부모를 교체
  right_node->parent = x->parent;

  // 부모 쪽에서도 자식을 교체해주는데, 이때 기존 자식(x)의 위치에 따라 분기
  // * x가 루트였다면,
  if (x->parent == t->nil) {
    // 회전으로 인해 x는 더 이상 루트가 아니며
    // right_node가 새로운 루트가 되므로 교체
    t->root = right_node;
  }
  // * x가 왼쪽 자식이었다면,
  else if (x == x->parent->left) {
    x->parent->left = right_node;
  }
  // * x가 오른쪽 자식이었다면,
  else {
    x->parent->right = right_node;
  }

  // x를 기존 right_node의 왼쪽 자식으로 놓는다.
  right_node->left = x;
  x->parent = right_node;
}

void right_rotate(rbtree *t, node_t *y) {
  node_t *left_node = y->left;

  // left_node의 오른쪽 서브 트리를 new_node의 왼쪽 서브 트리로 옮긴다.
  y->left = left_node->right; // 부모 측(y)에서 자식 재설정
  // 자식 측(left_node->right)에서 부모를 new_node로 재설정
  if (left_node->right != t->nil) {
    left_node->right->parent = y;
  }

  // 우선은 자식 쪽(left_node)에서만 부모를 교체
  left_node->parent = y->parent;

  // 부모 쪽에서도 자식을 교체해주는데, 이때 기존 자식(y)의 위치에 따라 분기
  // * new_node가 루트였다면,
  if (y->parent == t->nil) {
    // 회전으로 인해 new_node는 더 이상 루트가 아니며
    // left_node가 새로운 루트가 되므로 교체
    t->root = left_node;
  }
  // * new_node가 왼쪽 자식이었다면,
  else if (y == y->parent->right) {
    y->parent->right = left_node;
  }
  // * new_node가 오른쪽 자식이었다면,
  else {
    y->parent->left = left_node;
  }

  // new_node를 기존 left_node의 오른쪽 자식으로 놓는다.
  left_node->right = y;
  y->parent = left_node;
}

void insert_fixup(rbtree *t, node_t *new_node) {
  node_t *curr = new_node; // 불필요함.

  // 4번 규칙을 위반하지 않을 때까지 이 반복문 실행
  while (curr->parent->color == RBTREE_RED) {
    // new_node의 부모가 new_node의 조부모의 왼쪽 자식이라면,
    if (curr->parent == curr->parent->parent->left) {
      node_t *uncle = curr->parent->parent->right; // 삼촌!

      if (uncle->color == RBTREE_RED) { // 삼촌이 빨간 색이라면,
        curr->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        uncle->parent->color = RBTREE_RED;
        curr = curr->parent->parent;
      }
      // new_node가 부모의 오른쪽 자식이라면, -> case2
      // 꺾여있는 걸 펴줘서 case3로 만들어준다.
      else {
        if (curr == curr->parent->right) {
          curr = curr->parent;
          left_rotate(t, curr);
        }
        curr->parent->color = RBTREE_BLACK;
        curr->parent->parent->color = RBTREE_RED;
        right_rotate(t, curr->parent->parent);
      }
    }
    // new_node의 부모가 new_node의 조부모의 오른쪽 자식이라면,
    else {
      node_t *uncle = curr->parent->parent->left; // 삼촌!

      if (uncle->color == RBTREE_RED) { // 삼촌이 빨간 색이라면,
        curr->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        uncle->parent->color = RBTREE_RED;
        curr = curr->parent->parent;
      }
      // new_node가 부모의 오른쪽 자식이라면, -> case2
      // 꺾여있는 걸 펴줘서 case3로 만들어준다.
      else {
        if (curr == curr->parent->left) {
          curr = curr->parent;
          right_rotate(t, curr);
        }
        curr->parent->color = RBTREE_BLACK;
        curr->parent->parent->color = RBTREE_RED;
        left_rotate(t, curr->parent->parent);
      }
    }
  }

  // 2번 규칙을 위반했을 수도 있으니 루트 색상은 검은색으로 (다시) 색칠하기
  t->root->color = RBTREE_BLACK;
}

void inorder_tree_walk(const rbtree *t, node_t *x, key_t *arr, int *i, const size_t n) {
  if (*i == n) {
    return;
  }

  if (x != t->nil) {
    inorder_tree_walk(t, x->left, arr, i, n);
    arr[*i] = x->key;
    (*i)++;
    inorder_tree_walk(t, x->right, arr, i, n);
  }
}

void delete_rbtree_helper(rbtree *t, node_t *x) {
  if (x->left != t->nil) {
    delete_rbtree_helper(t, x->left);
    free(x->left);
  }
  if (x->right != t->nil) {
    delete_rbtree_helper(t, x->right);
    free(x->right);
  }
}

void transplant(rbtree *t, node_t *u, node_t *v) {
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

void delete_fixup(rbtree *t, node_t *x) {
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      node_t *tmp = x->parent->right; // 형제 노드

      // case1. 형제 노드의 색상이 RED라면
      if (tmp->color == RBTREE_RED) {
        // 형제/부모 서로 색상 바꾸기
        // 부모 기준으로 회전하기 (타겟이 내려가도록)
        tmp->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        tmp = x->parent->right;
      }

      // case2. 형제 노드의 양쪽 자식 모두 BLACK이라면
      if (tmp->left->color == RBTREE_BLACK && tmp->right->color == RBTREE_BLACK) {
        tmp->color = RBTREE_RED;
        x = x->parent;
      }

      else {
        // case3.
        if (tmp->right->color == RBTREE_BLACK) {
          tmp->left->color = RBTREE_BLACK;
          tmp->color = RBTREE_RED;
          right_rotate(t, tmp);
          tmp = x->parent->right;
        }

        // case4.
        tmp->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        tmp->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else {
      node_t *tmp = x->parent->left; // 형제 노드

      // case1. 형제 노드의 색상이 RED라면
      if (tmp->color == RBTREE_RED) {
        // 형제/부모 서로 색상 바꾸기
        // 부모 기준으로 회전하기 (타겟이 내려가도록)
        tmp->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        tmp = x->parent->left;
      }

      // case2. 형제 노드의 양쪽 자식 모두 BLACK이라면
      if (tmp->left->color == RBTREE_BLACK && tmp->right->color == RBTREE_BLACK) {
        tmp->color = RBTREE_RED;
        x = x->parent;
      }

      else {
        // case3.
        if (tmp->left->color == RBTREE_BLACK) {
          tmp->right->color = RBTREE_BLACK;
          tmp->color = RBTREE_RED;
          left_rotate(t, tmp);
          tmp = x->parent->left;
        }

        // case4.
        tmp->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        tmp->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}
