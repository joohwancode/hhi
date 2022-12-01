#include "rbtree.h"
#include <stdlib.h>


rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));

  nilNode->color = RBTREE_BLACK;
  p->nil = nilNode;
  p->root = p->nil;

  return p;
}

void delete_rbtree(rbtree *t){
  
  free(t);
}

void rbtree_insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left){
      node_t *y = z->parent->parent->right;

      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->right){
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;

        right_rotate(t, z->parent->parent);
      }
    }
    else{
      node_t *y = z->parent->parent->left;

      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }

      else {
        if (z->parent->left == z){
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
  node_t *x = t->root;
  node_t *y = t->nil;
  node_t *z = (node_t*)calloc(1, sizeof(node_t));
  z->key = key;
  z->color = RBTREE_RED;

  while(x != t->nil){
    y = x;
    if ((z->key) < (x->key)){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }

  z->parent = y;

  if (y == t->nil){
    t->root = z;
  }
  else if ((z->key) < (y->key)){
    y->left = z;
  }
  else {
    y->right = z;
  }

  z->left = t->nil;
  z->right = t->nil;
  rbtree_insert_fixup(t, z);

  return z;

}


void right_rotate(rbtree *t, node_t *x){
  node_t *y = x->left;
  x->left = y->right;

  if (y->right != t->nil){
      y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil){
      t->root = y;
  }
  else if (x== x->parent->right){
      x->parent->left = y;
  }
  else {
      x->parent->right = y;
  }
  y->right = x;
  x->parent = y;

}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;

  if (y->left != t->nil){
    y->left->parent = x;
  }

  y->parent = x->parent;

  if(x->parent == t->nil){
    t->root = y;
  }
  else if (x == x->parent->left){
    x->parent->left = y;
  }
  else {
    x->parent->right = y;
  }
  
  y->left = x;
  x->parent =y;
}


node_t *rbtree_find(const rbtree *t, const key_t key){
  node_t *temp = t->root;

  while(temp != t->nil){

    if (temp->key > key){
      temp = temp->left;
    }

    else if (temp->key < key){
      temp = temp->right;
    }

    else {
      return temp;
    }
  }
  return NULL;

}

node_t *rbtree_min(const rbtree *t){
  node_t *min = t->root;

  while (min->left != t->nil){
      min = min->left;
  }
  return min;
}

node_t *rbtree_max(const rbtree *t){
  node_t *max = t->root;

  while (max->right != t->nil){
      max = max->right;
  }
  return max;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){
  if (u->parent == t->nil){
    t->root = v;
  }
  else if (u == u->parent->left){
    u->parent->left = v;
  }
  else{
    u->parent->right = v;
  }
  v->parent = u->parent;
}


node_t *successor(rbtree *t, node_t *z){

    while (z->left != t->nil){
      z = z->left;
    }
    return z;
}

void rbtree_erase_fixup(rbtree *t, node_t *z){  

  while (z != t->root && z->color == RBTREE_BLACK){
    if (z == z->parent->left){
      
      node_t *x = z->parent->right;

      if (x->color == RBTREE_RED){

        x->color = RBTREE_BLACK;
        z->parent->color = RBTREE_RED;
        left_rotate(t, z->parent);
        
        x = z->parent->right;
      }

      if (x->left->color == RBTREE_BLACK && x->right->color == RBTREE_BLACK){

        x->color = RBTREE_RED;
     
        z = z->parent;
      }
      else {

        if (x->right->color == RBTREE_BLACK){
          x->left->color = RBTREE_BLACK;
          x->color = RBTREE_RED;
          right_rotate(t, x);
          x = z->parent->right;
        }

        x->color = z->parent->color;
        x->right->color = RBTREE_BLACK;
        z->parent->color = RBTREE_BLACK;
        
 
        left_rotate(t, z->parent);
        z = t->root;
      }
    }

    else{
      node_t *x = z->parent->left;
      if(x->color == RBTREE_RED){
        x->color = RBTREE_BLACK;
        z->parent->color = RBTREE_RED;
        right_rotate(t, z->parent);

        x = z->parent->left;
      }

      if (x->right->color == RBTREE_BLACK && x->left->color == RBTREE_BLACK){
        x->color = RBTREE_RED;

        z = z->parent;
      }
      
      else{
        // case3 형제 자식 중 꺽인 자식이 red
        if(x->left->color == RBTREE_BLACK){
          x->right->color = RBTREE_BLACK;
          x->color = RBTREE_RED;
          left_rotate(t, x);
          x = z->parent->left;
        }
        x->color = z->parent->color;
        x->left->color = RBTREE_BLACK;
        z->parent->color =RBTREE_BLACK;
        
        right_rotate(t, z->parent);
        // 루트로 설정
        z = t->root;

      
      }
    }
  }

  z->color = RBTREE_BLACK;
}



int rbtree_erase(rbtree *t, node_t *z){

  node_t *x;
  node_t *y = z; 
  color_t yOriginalColor = y->color; 

  if (z->left == t->nil){
    x = z->right;
    rbtree_transplant(t, z, z->right);
  }
  else if (z->right == t->nil){
    x = z->left;
    rbtree_transplant(t, z, z->left);
  }
  else{
    y = successor(t, z->right);
    yOriginalColor = y->color;
    x = y->right;

    if (y->parent == z){
      x->parent = y;
    }

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

  if (yOriginalColor == RBTREE_BLACK){
    rbtree_erase_fixup(t, z);
  }

  return z->key;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  node_t *r = t->root;

  while (r->left != t->nil)
  {
    r = r->left;
  }

  arr[0] = r->key;
  for (int i = 1; i < n; i++)
  {
    if (r->right == t->nil)
    {
      while (r->key > r->parent->key)
      {
        r = r->parent;
      }
      arr[i] = r->parent->key;
      r = r->parent;
    }
    else
    {
      r = r->right;
      while (r->left != t->nil)
      {
        r = r->left;
      }
      arr[i] = r->key;
    }
  }
  return 0;
}
