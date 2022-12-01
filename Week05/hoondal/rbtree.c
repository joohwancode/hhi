#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
    // * tree = new_tree(): RB tree 구조체 생성
    // * 여러 개의 tree를 생성할 수 있어야 하며 각각 다른 내용들을 저장할 수 있어야 합니다.
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));

  p->root = nil;
  p->nil = nil;

  nil->color = RBTREE_BLACK;
  // nil->parent = nil;
  // nil->left = nil;
  // nil->right = nil;

  return p;
}

void right_rotate(rbtree *t, node_t *y){
  node_t *x = y->left;
  y->left = x->right;
  if (x->right != t->nil)  // nil이 아닌 경우이면, node가 존재하므로 밑에 노드의 부모를 y로 설정해야 함.
    x->right->parent = y;
  x->parent = y->parent; // 원래 부모였던 y의 부모를 새롭게 오는 x의 부모로 연결해주어야 함.
  if (y->parent == t->nil) //y가 루트인 경우이다. 이 경우에는 x가 새로운 루트가 되므로 재설정 해주어야 함.
    t->root = x;
  else if (y == y->parent->left) //y가 부모의 왼쪽 자식이었던 경우 x가 왼쪽자식이 되도록 설정
    y->parent->left = x;
  else // y 가 오른쪽 자식이었던 경우면, x를 오른쪽 자식이 되도록 설정
    y->parent->right = x;
  x->right = y; //오른쪽 회전이므로 x가 새로운 부모가 되고, y가 오른쪽 자식이 된다.
  y->parent = x; //마지막으로 y노드에서 부모 노드를 x로 설정해준다.
}

void left_rotate(rbtree *t, node_t *x){
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil)
    {t->root = y;}
  
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    {x->parent->right = y;}
  y->left = x;
  x->parent = y;
}


node_t *rbtree_insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color == RBTREE_RED){
    if (z->parent == z->parent->parent->left)
      {
        node_t *y;
        y = z->parent->parent->right;
        if (y->color == RBTREE_RED)
          {
            // case 1 parent's and uncle's colors are red
            z->parent->color = RBTREE_BLACK;
            y->color = RBTREE_BLACK;
            z->parent->parent = RBTREE_RED;
            z = z->parent->parent;
          }
            // uncle's color is black
        else
        {
          if (z == z->parent->right)
          // case2, parent is red, uncle is black and
          // the order of grandfather,parents and children is bent
            {
              z = z->parent;
              left_rotate(t,z);
            }
          //case3, the order of grandfarther , parents and children is in line
          z->parent->color = RBTREE_BLACK;
          z->parent->parent = RBTREE_RED;
          right_rotate(t,z->parent->parent);
        }
      }
    else
      {
        //"right" <-> "left" reverse
        node_t *y;
        y = z->parent->parent->left;
        if (y->color == RBTREE_RED)
          {
            z->parent->color = RBTREE_BLACK;
            y->color = RBTREE_BLACK;
            z->parent->parent = RBTREE_RED;
            z = z->parent->parent;
          }
        else
        {
          if (z == z->parent->left)
          {
            z = z->parent;
            right_rotate(t,z); 
          }
          z->parent->color = RBTREE_BLACK;
          z->parent->parent = RBTREE_RED;
          left_rotate(t,z->parent->parent);
        }
      }
    }
  t->root->color = RBTREE_BLACK;
  return t->root;
}


node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  //   * 구현하는 ADT가 multiset이므로 이미 같은 key의 값이 존재해도 하나 더 추가 합니다.
  node_t *z = (node_t*)calloc(1,sizeof(node_t));
  z->key = key;

  node_t *y = t->nil;
  node_t *x = t->root;

  //find insert z's position
  while (x != t->nil){
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
  rbtree_insert_fixup(t,z);
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    // TODO: implement find
    // * RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
    // * 해당하는 node가 없으면 NULL 반환
    node_t *cur_node = t->root;
    while (cur_node != t->nil)
      {
        if (cur_node->key == key)
          return cur_node;
        else if (cur_node->key < key)
          cur_node = cur_node->right;
        else
          cur_node = cur_node->left;
      }

  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  // RB tree 중 최소 값을 가진 node pointer 반환
  node_t *x = t->root;
  while (x->left != t->nil)
    {
    x = x->left;
    }
  return x;
}

node_t *rbtree_max(const rbtree *t) {
    // TODO: implement find
    // 최대값을 가진 node pointer 반환
  node_t *x = t->root;
  while (x->right != t->nil)
    {
      x = x->right;
    }

  return x;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
//   * delete_tree(tree): RB tree 구조체가 차지했던 메모리 반환
//     * 해당 tree가 사용했던 메모리를 전부 반환해야 합니다. (valgrind로 나타나지 않아야 함)
  node_t *x = t->root;
  
  delete_one(t, x);

  free(t->nil);
  free(t);
}

void delete_one(rbtree *t, node_t *cur){
  if (cur != t->nil){
    delete_one(t, cur->left);
    free(cur);
    delete_one(t, cur->right);
  }
}

void rb_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    {u->parent->right = v;}
  v->parent = u->parent;
}

void rbtree_erase_fixup(rbtree *t, node_t *x)
{
  node_t *w;
  while (x != t->root && x->color == RBTREE_BLACK)
  {
    if (x == x->parent->left)
    {
      w = x->parent->right;
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t,x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else 
        {
          if (w->right->color == RBTREE_BLACK)
            {
              w->left->color = RBTREE_BLACK;
              w->color = RBTREE_RED;
              right_rotate(t,w);
              // w = w->parent;  sudo 코드랑은 다르긴한데 right rotate실시하면 이렇게 적어도 똑같을듯?
              w = x->parent->right;
            }
          w->color = w->parent->color;
          x->parent->color = RBTREE_BLACK;
          w->right->color = RBTREE_BLACK;
          left_rotate(t,x->parent);
          x = t->root;
        }
      }
    else
      {
        w = x->parent->left;
        if (w->color == RBTREE_RED)
        {
          w->color = RBTREE_BLACK;
          x->parent->color = RBTREE_RED;
          right_rotate(t,x->parent);
          w = x->parent->left;
        }
        if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK)
        {
          w->color = RBTREE_RED;
          x = x->parent;
        }
        else{
          if (w->left->color == RBTREE_BLACK)
          {
           w->color = RBTREE_RED;
           w->right->color = RBTREE_BLACK;
           left_rotate(t,w);
          //  w = w->parent;
           w = x->parent->left; 
          }
          w->color = x->parent->color;
          x->parent->color = RBTREE_BLACK;
          w->left->color = RBTREE_BLACK;
          right_rotate(t,x->parent);
          x = t->root;
        }
      }
  }
}

node_t *tree_minimum(rbtree *t, node_t *cur)
{
  node_t *y;
  y = cur;
  while (y->left != t->nil)
  {
    y = y->left;

  }
  return y;
}

int rbtree_erase(rbtree *t, node_t *z) {
    //   TODO: implement erase
    // RB tree 내부의 ptr로 지정된 node를 삭제하고 메모리 반환
  node_t *y = z;    //y는 트리에서 삭죄될 노드 또는 트리에서 이동한 노드를 가리킨다.
  color_t y_origin_color = y->color; //y의 색깔이 변경될 수 있기 때문에 색깔 미리 저장
  node_t *x;
  if (z->left == t->nil) //z가 하나 이하의 자식을 갖는 경우, 바로 삭제됨
    {
      x = z->right;
      rb_transplant(t,z,z->right);
    }
  else if (z->right == t->nil) //z가 하나 이하의 자식을 갖는 경우
    {
      x = z->left;
      rb_transplant(t,z,z->left);
    }
  else  //2개의 자식을 갖는 경우는 다르게 적용해야한다.
    {
      y = tree_minimum(t, z->right);
      y_origin_color = y->color; //y의 색깔 변경 여부 때문에 저장해야함 밑에서 씀
      x = y->right;
      if (y->parent == z)
        x->parent = y;
      else
        {
          rb_transplant(t,y,y->right);
          y->right = z->right;
          y->right->parent = y;
        }
      rb_transplant(t,z,y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
  if (y_origin_color == RBTREE_BLACK) //y의 색깔이 검정색인 경우 룰 위반이다.
    rbtree_erase_fixup(t,x);
  free(z);
  return 0;
}



int in_order(const rbtree *t, node_t *cur, key_t *arr, size_t n, int index){
  if (index < n)
    {
      if (cur->left != t->nil)
        index = in_order(t, cur->left,arr,n,index);

      arr[index++] = cur->key; //어레이에 값 삽입

      if (cur->right != t->nil)
        index = in_order(t, cur->right,arr,n,index);
    }
  return index;
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  // * RB tree의 내용을 key 순서대로 주어진 array로 변환
  // * array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
  // * array의 메모리 공간은 이 함수를 부르는 쪽에서 준비하고 그 크기를 n으로 알려줍니다.
  //inorder traversing
    
    in_order(t, t->root, arr, n, 0);
    
    return 0;
}
