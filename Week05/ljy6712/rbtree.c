#include "rbtree.h"
// GIT TEST
#include <stdlib.h>

rbtree *new_rbtree(void)
{
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed
    p->nil = (node_t *)calloc(1, sizeof(node_t));
    p->root = p->nil;
    p->nil->color = RBTREE_BLACK;
    return p;
}

void postorder_delete_rbtree(rbtree *t, node_t *x)
{
    if (x != t->nil)
    {
        postorder_delete_rbtree(t, x->left);
        postorder_delete_rbtree(t, x->right);
        free(x);
    }
}
void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    postorder_delete_rbtree(t, t->root);
    free(t->nil);
    free(t);
}
void rbtree_rotateRight(rbtree *t, node_t *x)
{
    node_t *y = x->left;
    x->left = y->right;
    if (y->right != t->nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil)
    {
        t->root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}
void rbtree_rotateLeft(rbtree *t, node_t *x)
{
    node_t *y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil)
    {
        t->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    /*node_t* rightChild = parent->right;
    parent->right = rightChild->left;
    if (rightChild->left != t->nil)
        rightChild->left->parent = parent;
    rightChild->parent = parent->parent;

    if (parent->parent == NULL)
        t->root = rightChild;
    else
    {
        if (parent == parent->parent->right)
            parent->parent->right = rightChild;
        else
            parent->parent->left = rightChild;
    }
    rightChild->left = parent;
    parent->parent = rightChild;*/
}
void rbtree_insert_fixup(rbtree *t, node_t *z)
{
    while (z->parent->color == RBTREE_RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            node_t *y = z->parent->parent->right;
            if (y->color == RBTREE_RED) //삼촌이 빨간색일때
            {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else //삼촌이 검정색일 때
            {
                if (z == z->parent->right) //꺾여있을때
                {
                    z = z->parent;
                    rbtree_rotateLeft(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                rbtree_rotateRight(t, z->parent->parent);
            }
        }
        else
        {
            node_t *y = z->parent->parent->left;
            if (y->color == RBTREE_RED)
            {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rbtree_rotateRight(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                rbtree_rotateLeft(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK; //루트 색깔 검정색으로
}
node_t *rbtree_insert(rbtree *t, const key_t key)
{
    // TODO: implement insert
    node_t *y = t->nil;
    node_t *x = t->root;
    while (x != t->nil)
    {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    node_t *z = (node_t *)calloc(1, sizeof(node_t));
    z->key = key;
    z->parent = y;
    if (y == t->nil)
        t->root = z;
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    rbtree_insert_fixup(t, z);
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *x = t->root;
    while (x != t->nil)
    {
        if (x->key == key)
        {
            return x;
        }
        if (x->key < key)
        {
            x = x->right;
        }
        else
        {
            x = x->left;
        }
    }
    return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    node_t *x = t->root;
    while (x->left != t->nil)
    {
        x = x->left;
    }
    return x;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    node_t *x = t->root;
    while (x->right != t->nil)
    {
        x = x->right;
    }
    return x;
}
void rbtree_transplant(rbtree *t, node_t *u, node_t *v)
{
    if (u->parent == t->nil)
    {
        t->root = v;
    }
    else if (u->parent->left == u)
        u->parent->left = v;
    else if (u->parent->right == u)
        u->parent->right = v;
    v->parent = u->parent;
}
node_t *tree_minimum(rbtree *t, node_t *x)
{
    while (x->left != t->nil)
    {
        x = x->left;
    }
    return x;
}
void rbtree_erase_fixup(rbtree *t, node_t *x){
  node_t *w;
  while (x != t -> root && x -> color == RBTREE_BLACK){
    if (x == x -> parent -> left) {
      w = x -> parent -> right;
      if (w -> color == RBTREE_RED){
        w -> color = RBTREE_BLACK;
        x -> parent -> color = RBTREE_RED;
        rbtree_rotateLeft(t, x -> parent);
        w = x -> parent -> right;
      }
      if (w -> left -> color == RBTREE_BLACK && w -> right -> color == RBTREE_BLACK){
        w -> color = RBTREE_RED;
        x = x -> parent;
      } else {
        if (w -> right -> color == RBTREE_BLACK) {
          w -> left -> color = RBTREE_BLACK;
          w -> color = RBTREE_RED;
          rbtree_rotateRight(t, w);
          w = x -> parent -> right;
        }
        w -> color = x -> parent -> color;
        x -> parent -> color = RBTREE_BLACK;
        w -> right -> color = RBTREE_BLACK;
        rbtree_rotateLeft(t, x -> parent);
        x = t -> root;
      }
    } else {
      w = x -> parent -> left;
      if (w -> color == RBTREE_RED){
        w -> color = RBTREE_BLACK;
        x -> parent -> color = RBTREE_RED;
        rbtree_rotateRight(t, x -> parent);
        w = x -> parent -> left;
      }
      if (w -> right -> color == RBTREE_BLACK && w -> left -> color == RBTREE_BLACK){
        w -> color = RBTREE_RED;
        x = x -> parent;
      } else {
        if (w -> left -> color == RBTREE_BLACK) {
          w -> right -> color = RBTREE_BLACK;
          w -> color = RBTREE_RED;
          rbtree_rotateLeft(t, w);
          w = x -> parent -> left;
        }
        w -> color = x -> parent -> color;
        x -> parent -> color = RBTREE_BLACK;
        w -> left -> color = RBTREE_BLACK;
        rbtree_rotateRight(t, x -> parent);
        x = t -> root;
      }
    } 
  }
  x -> color = RBTREE_BLACK;
}
int rbtree_erase(rbtree* t, node_t* p)
{
    // TODO: implement erase
    node_t* y = p;
    color_t y_original_color = y->color;
    node_t *x;
    if (p->left == t->nil)
    {
        x = p->right;
        rbtree_transplant(t, p, x);
    }
    else if (p->right == t->nil)
    {
        x = p->left;
        rbtree_transplant(t, p, x);
    }
    else
    {
        y = tree_minimum(t, p->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == p)
            x->parent = y;
        else
        {
            rbtree_transplant(t, y, y->right);
            y->right = p->right;
            y->right->parent = y;
        }
        rbtree_transplant(t, p, y);
        y->left = p->left;
        y->left->parent = y;
        y->color = p->color;
    }
    if (y_original_color == RBTREE_BLACK)
        rbtree_erase_fixup(t, x);
    free(p);
    return 0;
}

void inorder(const rbtree *t, key_t *arr, node_t *x, int *level, int n)
{
    if (x == t->nil)
    {
        return;
    }
    inorder(t, arr, x->left, level, n);
    if (*level < n)
    {
        arr[(*level)++] = x->key;
    }
    else
    {
        return;
    }
    inorder(t, arr, x->right, level, n);
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    int cnt = 0;
    int *level = &cnt;
    inorder(t, arr, t->root, level, n);
    // TODO: implement to_array
    return 0;
}