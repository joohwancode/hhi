#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>
#define SENTINEL

void rotate_left(rbtree*, node_t*);
void rotate_right(rbtree*, node_t*);
void insert_fix(rbtree*, node_t*);
node_t* min_from(const rbtree*, node_t* x);
node_t* max_from(const rbtree*, node_t* x);

rbtree* new_rbtree(void) {
  rbtree* t = (rbtree*)calloc(1, sizeof(rbtree));
  t->nil = (node_t*)malloc(sizeof(node_t));
  t->root = t->nil;
  t->nil->color = RBTREE_BLACK;
  return t;
}

void rbtree_destroy_node(rbtree* t, node_t* x) {
  //it must be post-order traversal
  if (x->left != t->nil)
    rbtree_destroy_node(t, x->left);

  if (x->right != t->nil)
    rbtree_destroy_node(t, x->right);

  free(x);
}

void delete_rbtree(rbtree* t) {
  if (t->root != t->nil)
    rbtree_destroy_node(t, t->root);
  free(t->nil);
  free(t);
}

node_t* rbtree_insert(rbtree* t, const key_t key) {
  node_t* z = (node_t*)malloc(sizeof(node_t));
  z->key = key;
  node_t* y = t->nil;
  node_t* x = t->root;
  while (x != t->nil) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    }
    else {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == t->nil) {
    t->root = z;
  }
  else if (z->key < y->key) {
    y->left = z;
  }
  else {
    y->right = z;
  }

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  insert_fix(t, z);
  return z;
}

node_t* rbtree_find(const rbtree* t, const key_t key) {
  node_t* Node = t->root;
  while (Node != t->nil) {
    if (Node->key == key) {
      return Node;
    }
    if (Node->key < key) {
      Node = Node->right;
    }
    else {
      Node = Node->left;
    }
  }
  return NULL;
}

void rotate_right(rbtree* t, node_t* p) {
  node_t* leftChild = p->left; 
  p->left = leftChild->right;
  if (leftChild->right != t->nil) {
    leftChild->right->parent = p;
  }
  leftChild->parent = p->parent;
  if (p->parent == t->nil) {
    t->root = leftChild;
  }
  else {
    if (p == p->parent->left) {
      p->parent->left = leftChild;
    }
    else {
      p->parent->right = leftChild;
    }
  }
  leftChild->right = p;
  p->parent = leftChild;
}

void rotate_left(rbtree* t, node_t* p) {
  node_t* rightChild = p->right; 
  p->right = rightChild->left;
  if (rightChild->left != t->nil) {
    rightChild->left->parent = p;
  }
  rightChild->parent = p->parent;
  if (p->parent == t->nil) {
    t->root = rightChild;
  }
  else {
    if (p == p->parent->left) {
      p->parent->left = rightChild;
    }
    else {
      p->parent->right = rightChild;
    }
  }

  rightChild->left = p;
  p->parent = rightChild;
}

void insert_fix(rbtree* t, node_t* z) {
  while (z->parent->color == RBTREE_RED) { 
    if (z->parent == z->parent->parent->left) { 
      node_t* y = z->parent->parent->right; 
      if (y->color == RBTREE_RED) { 
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;

        z = z->parent->parent; //일단 급한불 끄고 다시 불난 곳으로
      }
      else { 
        if (z == z->parent->right) {
          z = z->parent;
          rotate_left(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;

        rotate_right(t, z->parent->parent);
      }
    }
    else { //대칭적으로
      node_t* y = z->parent->parent->left;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;

        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left) {
          z = z->parent;
          rotate_right(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;

        rotate_left(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t* rbtree_min(const rbtree* t) {
  node_t* x = t->root;
  while (x->left != t->nil) {
    x = x->left;
  }
  return x;
}

node_t* rbtree_max(const rbtree* t) {
  node_t* x = t->root;
  while (x->right != t->nil) {
    x = x->right;
  }
  return x;
}
node_t* min_from(const rbtree* t, node_t* x) {
  while (x->left != t->nil) {
    x = x->left;
  }
  return x;
}
node_t* max_from(const rbtree* t, node_t* x) {
  while (x->right != t->nil) {
    x = x->right;
  }
  return x;
}

void transplant(rbtree* t, node_t* u, node_t* v) {
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

void rbtree_erase_fix(rbtree* t, node_t* x) {
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      node_t* w = x->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rotate_left(t, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rotate_right(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        rotate_left(t, x->parent);
        x = t->root;
      }
    }
    else {
      node_t* w = x->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rotate_right(t, x->parent);
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
          rotate_left(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        rotate_right(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}
int rbtree_erase(rbtree* t, node_t* z) {
  if (rbtree_find(t, z->key) == NULL) {
    return 1;
  }
  node_t* x;
  node_t* y = z;
  color_t y_original_color = y->color;
  if (z->left == t->nil) {
    x = z->right;
    transplant(t, z, z->right);
  }
  else if (z->right == t->nil) {
    x = z->left;
    transplant(t, z, z->left);
  }
  else {
    y = min_from(t, z->right);
    y_original_color = y->color;
    x = y->right;
    if (y != z->right) {
      transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    else {
      x->parent = y;
    }
    transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (y_original_color == RBTREE_BLACK) {
    rbtree_erase_fix(t, x);
  }

  free(z);
  return 0;
}

int inorder(const rbtree* t, node_t* x, key_t* arr, size_t i, size_t n) {
  if (x->left != t->nil) {
    i = inorder(t, x->left, arr, i, n);
  }

  if (i == n)
    return n;
  arr[i] = x->key;

  if (x->right != t->nil) {
    return inorder(t, x->right, arr, i + 1, n);
  }
  return i + 1;
}

int rbtree_to_array(const rbtree* t, key_t* arr, const size_t n) {
  if (n <= 0)
    return 0;
  else {
    inorder(t, t->root, arr, 0, n);
    return 1;
  }
}
