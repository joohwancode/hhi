#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed
    
    node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
    NIL->color = RBTREE_BLACK;
    p->nil = NIL;
    p->root = p->nil;
    
    return p;
}

void free_node(rbtree *t, node_t *x) {
    if (x->left != t->nil){
        free_node(t, x->left);
    }

    if (x->right != t->nil){
        free_node(t, x->right);
    }

    free(x);
    x = NULL;
}

void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory

    if (t->root != t->nil){
        free_node(t, t->root);
    }

    free(t->nil);
    free(t);
}

node_t *left_rotate(rbtree *t, node_t *x) {
    // TODO: implement insert

    node_t *y = x->right;
    x->right = y->left;
    
    if(y->left != t->nil){
        y->left->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == t->nil){
        t->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

#include "rbtree.h"

node_t *right_rotate(rbtree *t, node_t *x) {
    // TODO: implement insert

    node_t *y = x->left;
    x->left = y->right;

    if(y->right != t->nil){
        y->right->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == t->nil){
        t->root = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

node_t *rbtree_insert_fixup(rbtree *t, node_t *z) {
    // TODO: implement insert

    while(z->parent->color== RBTREE_RED){
        if(z->parent == z->parent->parent->left){
            node_t *y = z->parent->parent->right;

            if(y->color == RBTREE_RED){
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else{ 
                if(z == z->parent->right){
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

            if(y->color == RBTREE_RED){
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
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
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
    node_t *y = t->nil;
    node_t *x = t->root;

    z->key = key;

    while(x != t->nil){
        y = x;
        if(z->key < y->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    z->parent = y;

    if(y == t->nil){
        t->root = z;
    }
    else if(z->key < y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }

    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;

    rbtree_insert_fixup(t, z);

    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
    node_t *tmp = t->root;

    while(tmp != t->nil) { 
        if (tmp->key == key){
            return tmp;
        }
        if (tmp->key > key) {
            tmp = tmp->left;
        }
        else{
            tmp = tmp->right;
        }
    }

    return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  
    node_t *tmp = t->root;

    while(tmp->left != t->nil) { 
        tmp = tmp->left;
    }

    return tmp;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
    node_t *tmp = t->root;

    while(tmp->right != t->nil) { 
        tmp = tmp->right;
    }

    return tmp;
}

void rbtree_erase_fixup(rbtree *t, node_t *x) {
    node_t *w;
    while(x != t->root && x->color == RBTREE_BLACK){
        if(x == x->parent->left){
            w = x->parent->right;

            // case1 
            if(w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                 
                left_rotate(t, x->parent);
                
                w = x->parent->right;
            }
            // case2
            if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
                w->color = RBTREE_RED;
                x = x->parent;
            }
            // case3
            else{
                if(w->right->color == RBTREE_BLACK){
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;

                    right_rotate(t, w);

                    w = x->parent->right;
                }

                // case4
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;

                left_rotate(t, x->parent);

                x = t->root;
            }
        }
        else{
            w = x->parent->left;

            if(w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;

                right_rotate(t, x->parent);

                w = x->parent->left;
            }
            
            if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
                    w->color = RBTREE_RED;
                    x = x->parent;
            }
            else{
                if(w->left->color == RBTREE_BLACK){
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

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){
    if(u->parent == t->nil){
        t->root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    v->parent = u->parent;
}

int rbtree_erase(rbtree *t, node_t *z) {
    // TODO: implement erase

    node_t *y = z;
    color_t y_original_color = y->color;

    node_t *x;
    if(z->left == t->nil){
        x = z->right;
        rbtree_transplant(t, z, z->right);
    }
    else if(z->right == t->nil){
        x = z->left;
        rbtree_transplant(t, z, z->left);
    }
    else{
        y = z->right;

        while(y->left != t->nil){
            y = y->left;
        }
        y_original_color = y->color;
        x = y->right;

        if(y != z->right){
            rbtree_transplant(t, y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }
       else{
            x->parent = y;
        }

        rbtree_transplant(t, z, y);
        
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(y_original_color == RBTREE_BLACK){
        rbtree_erase_fixup(t,x);
    }

    free(z);
    z = NULL;

    return 0;
}

int inorder_array(const rbtree *t, node_t *p, key_t *arr, int i){
    if(p == t->nil){
        return i;
    }

    i = inorder_array(t, p->left, arr, i);
    arr[i++] = p->key;
    i = inorder_array(t, p->right, arr, i);

    return i;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array

  node_t *tmp = t->root;    
    
  inorder_array(t, tmp, arr, 0);
  return 0;
}
