#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));

  nil_node->color = RBTREE_BLACK;

  p->root = nil_node;
  p->nil = nil_node;
  return p;
}

void postorder(const rbtree *t, node_t *start){
    if (start == t->nil){
      return;
    }

    postorder(t, start->left);
    postorder(t, start->right);
    free(start);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  postorder(t, t->root);
  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *n){
    node_t *temp_node = n->right;

    if (temp_node == t->nil){
        return;
    }

    n->right = temp_node->left;

    if (temp_node->left != t->nil){
        temp_node->left->parent = n;
    }

    temp_node->parent = n->parent;

    if (n->parent == t->nil){
        t->root = temp_node;
    }else if (n == n->parent->left){
        n->parent->left = temp_node;
    }else{
        n->parent->right = temp_node;
    }

    temp_node->left = n;
    n->parent = temp_node;
}

void right_rotate(rbtree *t, node_t *n){
    node_t *temp_node = n->left;

    if (temp_node == t->nil){
        return;
    }

    n->left = temp_node->right;

    if (temp_node->right != t->nil){
        temp_node->right->parent = n;
    }

    temp_node->parent = n->parent;

    if (n->parent == t->nil){
        t->root = temp_node;
    }else if (n == n->parent->left){
        n->parent->left = temp_node;
    }else{
        n->parent->right = temp_node;
    }

    temp_node->right = n;
    n->parent = temp_node;
}

void rbtree_insert_fixup(rbtree *t, node_t *key){
    node_t *target_node = key;
    if (target_node == t->nil){
        return;
    }

    while(target_node->parent->color == RBTREE_RED){
        if(target_node->parent == target_node->parent->parent->left){
            node_t *uncle = target_node->parent->parent->right;

            if(uncle->color == RBTREE_RED){
                target_node->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                target_node = target_node->parent->parent;
            }else{
                if(target_node == target_node->parent->right){
                    target_node = target_node->parent;
                    left_rotate(t, target_node);
                }
                target_node->parent->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                right_rotate(t, target_node->parent->parent);
            }
        }else{
            node_t *uncle = target_node->parent->parent->left;

            if(uncle->color == RBTREE_RED){
                target_node->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                target_node = target_node->parent->parent;
            }else{
                if(target_node == target_node->parent->left){
                    target_node = target_node->parent;
                    right_rotate(t, target_node);
                }
                target_node->parent->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                left_rotate(t, target_node->parent->parent);
            }
        } 
    }

    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *root_node = t->root;
  node_t *temp_node = t->nil;
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;

  while (root_node != t->nil){
    temp_node = root_node;
    if(new_node->key < root_node->key){
  
      root_node = root_node->left;

    }else{
    
      root_node = root_node->right;

    }
  }

  new_node->parent = temp_node;
  
  if (temp_node == t->nil){
    t->root = new_node;
  }else if(new_node->key < temp_node->key){
    temp_node->left = new_node;
  }else{
    temp_node->right = new_node;
  }

  new_node->color = RBTREE_RED;
  new_node->left = t->nil;
  new_node->right = t->nil;

  rbtree_insert_fixup(t, new_node);

  return new_node;
}


node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find key
  node_t *root_node = t->root;
  node_t *temp_node = t->nil;

  while (root_node != t->nil){
    temp_node = root_node;
    if(root_node->key < key){
      root_node = root_node->right;
    }else if(root_node->key > key){
      root_node = root_node->left;
    }else{
      break;
    }
  }
  
  if (temp_node->key == key){
    return temp_node;
  }else{
    return NULL;
  }
}

node_t *rbtree_min(const rbtree *t) {
    // TODO: implement find max
    node_t *root_node = t->root;
    node_t *temp_node = t->nil;

    while (root_node != t->nil){
        temp_node = root_node;
        root_node = root_node->left;
    }

    return temp_node;
}

node_t *rbtree_max(const rbtree *t) {
    // TODO: implement find max
    node_t *root_node = t->root;
    node_t *temp_node = t->nil;

    while (root_node != t->nil){
        temp_node = root_node;
        root_node = root_node->right;
    }

    return temp_node;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){
  if (u->parent == t->nil){
    t->root = v;
  }else if (u == u->parent->left){
    u->parent->left = v;
  }else{
    u->parent->right = v;
  }
  v->parent = u->parent;
}

node_t *subtree_min(const rbtree *t, node_t *key) {
    // TODO: implement find max
    node_t *root_node = key;
    node_t *temp_node = t->nil;

    while (root_node != t->nil){
        temp_node = root_node;
        root_node = root_node->left;
    }

    return temp_node;
}

void rbtree_erase_fixup(rbtree *t, node_t *key){
    node_t *target_node = key;

    while ((target_node != t->root) && (target_node->color == RBTREE_BLACK)){
        if (target_node == target_node->parent->left){
            node_t *w = target_node->parent->right;
            if (w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                target_node->parent->color = RBTREE_RED;
                left_rotate(t, target_node->parent);
                w = target_node->parent->right;
            }
            if ((w->left->color == RBTREE_BLACK) && (w->right->color == RBTREE_BLACK)){
                w->color = RBTREE_RED;
                target_node = target_node->parent;
            }else{
                if (w->right->color == RBTREE_BLACK){
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    right_rotate(t, w);
                    w = target_node->parent->right;
                }
                w->color = target_node->parent->color;
                target_node->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                left_rotate(t, target_node->parent);
                target_node = t->root;
            }
        }else{
            node_t *w = target_node->parent->left;
            if (w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                target_node->parent->color = RBTREE_RED;
                right_rotate(t, target_node->parent);
                w = target_node->parent->left;
            }
            if ((w->right->color == RBTREE_BLACK) && (w->left->color == RBTREE_BLACK)){
                w->color = RBTREE_RED;
                target_node = target_node->parent;
            }else{
                if (w->left->color == RBTREE_BLACK){
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    left_rotate(t, w);
                    w = target_node->parent->left;
                }
                w->color = target_node->parent->color;
                target_node->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;
                right_rotate(t, target_node->parent);
                target_node = t->root;
            }
        }
    }
    target_node->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *temp_node = p; // y
  node_t *target_node; // x
  int temp_color = temp_node->color;

  if (p->left == t->nil){
    target_node = p->right;
    rbtree_transplant(t, p, p->right);
  }else if (p->right == t->nil){
    target_node = p->left;
    rbtree_transplant(t, p, p->left);
  }else{
    temp_node = subtree_min(t, p->right);
    temp_color = temp_node->color;
    target_node = temp_node->right;
    if (temp_node != p->right){
      rbtree_transplant(t, temp_node, temp_node->right);
      temp_node->right = p->right;
      temp_node->right->parent = temp_node;
    }else{
      target_node->parent = temp_node;
    }
    rbtree_transplant(t, p, temp_node);
    temp_node->left = p->left;
    temp_node->left->parent = temp_node;
    temp_node->color = p->color;
  }
  
  if (temp_color == RBTREE_BLACK){
    rbtree_erase_fixup(t, target_node);
  }
  free(p);
  return 0;
}

void inorder(const rbtree *t, node_t *start, key_t *arr, const size_t n, int *ptr){
    if (start == t->nil){
      return;
    }

    inorder(t, start->left, arr, n, ptr);

    if (*ptr == n){
      return;
    }
    arr[*ptr] = start->key;
    *ptr += 1;

    inorder(t, start->right, arr, n, ptr);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  int cnt = 0;
  int *ptr = &cnt;
  inorder(t, t->root, arr, n, ptr);

  return 0;
}
