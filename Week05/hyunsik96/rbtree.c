#include "rbtree.h"

#include <stdlib.h>

rbtree* new_rbtree(void) {
  rbtree* tree = (rbtree*)calloc(1, sizeof(rbtree));
  node_t* NIL = (node_t*)calloc(1, sizeof(node_t));
  tree->root = NIL;
  tree->nil = NIL;
  NIL->color = RBTREE_BLACK;
  return tree;
}

node_t* delete_node(rbtree* tree, node_t* current) {
  if (current->left == tree->nil && current->right == tree->nil) {
    return current;
  }
  if (current->left != tree->nil) {
    node_t* temp = delete_node(tree, current->left);
    free(temp);         // 주소가 가르키던 메모리를 회수시키면
    temp = NULL;     // 그 메모리를 가르키던 주소도 지우기
  }
  if (current->right != tree->nil) {
    node_t* temp = delete_node(tree, current->right);
    free(temp);
    temp = NULL;
  }
  return current;
}

void delete_rbtree(rbtree* tree) {
  if (tree->root != tree->nil) {
    node_t* temp = delete_node(tree, tree->root);
    free(temp);
    temp = NULL;
  }
  free(tree->nil);
  tree->nil = NULL;
  free(tree);
  tree = NULL;
}

void left_rotate(rbtree* tree, node_t* current) {
  node_t* up = current->right;                                // 올라갈 노드의 부모노드가 current로 들어왔다.
  current->right = up->left;                                      // 올라갈 노드의 왼쪽 서브트리를 내려갈 노드 오른쪽에 배치
  if (up->left != tree->nil) {                                       // 배치할 서브트리가 nil이 아닐경우
    up->left->parent = current;                                // 배치할 서브트리의 부모도 내려갈 노드로 설정
  }
  up->parent = current->parent;
  if (current->parent == tree->nil) {                        // 위와 비슷한 과정으로 내려갈 노드의 부모를 올라갈 노드의 부모로 설정
    tree->root = up;
  }
  else if (current == current->parent->left) {
    current->parent->left = up;
  }
  else {
    current->parent->right = up;
  }
  up->left = current;
  current->parent = up;
}

void right_rotate(rbtree* tree, node_t* current) {
  node_t* up = current->left;
  current->left = up->right;
  if (up->right != tree->nil) {
    up->right->parent = current;
  }
  up->parent = current->parent;
  if (current->parent == tree->nil) {
    tree->root = up;
  }
  else if (current == current->parent->right) {
    current->parent->right = up;
  }
  else {
    current->parent->left = up;
  }
  up->right = current;
  current->parent = up;
}


void rbtree_adjust_insert(rbtree* tree, node_t* current) {
  while (current->parent->color == RBTREE_RED) {                             // 현재 노드의 부모 노드 색이 레드라면 조정이 필요하다.
    if (current->parent == current->parent->parent->left) {   // 부모 노드가 조상 노드의 왼쪽 노드라면
      // Case (1)
      node_t* temp_uncle = current->parent->parent->right;                // 조상 노드의 오른쪽 노드를 엉클 노드로 만든다.
      if (temp_uncle->color == RBTREE_RED) {                                   // 엉클 노드의 색이 레드라면
        current->parent->color = temp_uncle->color = RBTREE_BLACK;        // 부모 및 엉클 노드의 색을 블랙으로 바꾸고,
        current->parent->parent->color = RBTREE_RED;                      // 조상 노드의 색을 레드로 바꾼다.
        current = current->parent->parent;                                  // 조상 노드를 기준으로 다시 위의 과정을 반복한다.
      }

      else {
        // Case (2)
        if (current == current->parent->right) {                               // 현재 노드가 부모 노드의 오른쪽 노드라면
          current = current->parent;                                           // 현재 노드를 갱신하고 left_rotate를 실행한다.
          left_rotate(tree, current);
        }

        // Case (3)
        current->parent->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        right_rotate(tree, current->parent->parent);
      }
    }

    else {                                                                                    // 부모 노드가 조상 노드의 오른쪽 노드라면
      node_t* temp_uncle = current->parent->parent->left;                  // 조상 노드의 왼쪽 노드를 엉클 노드로 만든다.
      if (temp_uncle->color == RBTREE_RED) {                                    // 엉클 노드의 색이 레드라면
        current->parent->color = temp_uncle->color = RBTREE_BLACK;           // 부모 및 엉클 노드의 색을 블랙으로 바꾸고,
        current->parent->parent->color = RBTREE_RED;                       // 조상 노드의 색을 레드로 바꾼다.
        current = current->parent->parent;                                   // 조상 노드를 기준으로 다시 위의 과정을 반복한다.
      }

      else {
        if (current == current->parent->left) {                               // 현재 노드가 부모 노드의 왼쪽 노드라면
          current = current->parent;
          right_rotate(tree, current);
        }
        current->parent->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        left_rotate(tree, current->parent->parent);
      }
    }
  }
}

node_t* rbtree_insert(rbtree* tree, const key_t key) {
  node_t* new_node = (node_t*)calloc(1, sizeof(node_t));    // 새로운 노드를 생성한다.
  node_t* temp_parent = tree->nil;  // 새 노드의 부모노드를 찾기 위해, 임시 부모, 자식노드를 만든다.
  node_t* temp_child = tree->root;  // 임시 자식이 곧 새 노드가 될때 까지며, 임시 자식은 root부터 출발.
  while (temp_child != tree->nil) {    // 임시 자식이 nil에 도착해 새 노드로 대체될 때 까지 트리 따라 내려감.
    temp_parent = temp_child;         // nil에 도착 못했으니 한칸 내려서 임시 부모에 현 임시 자식 대입.
    if (key < temp_child->key) {         // 임시 자식 코드(내려가고 있는 중의 노드)와 새 노드의 키 지속 비교
      temp_child = temp_child->left;
    }
    else {
      temp_child = temp_child->right;
    }
  }

  new_node->parent = temp_parent; // 새로운 노드의 부모를 갱신한다.

  if (temp_parent == tree->nil) {          // 임시 부모가 nil 이라면 루트가 nil이라는 뜻이므로 새 노드가 루트 노드
    tree->root = new_node;
  }
  else if (key < temp_parent->key) {  // 임시 부모의 키가 새 노드 키보다 크면 새 노드는 임시부모 왼자식
    temp_parent->left = new_node;
  }
  else {                                                  // 이외의 경우 임시부모 오른자식
    temp_parent->right = new_node;
  }

  new_node->key = key;                                     // 새로운 노드의 값들을 갱신한다.
  new_node->left = new_node->right = tree->nil;
  new_node->color = RBTREE_RED;

  rbtree_adjust_insert(tree, new_node);         // 노드를 삽입한 후, 규칙에 어긋난 것들을 조정해준다.
  tree->root->color = RBTREE_BLACK;
  return tree->root;
}

node_t* rbtree_find(const rbtree* t, const key_t key) {

  node_t* temp_node = t->root;

  while (temp_node->key != key && temp_node != t->nil) {
    if (temp_node->key > key) {
      temp_node = temp_node->left;
    }
    else {
      temp_node = temp_node->right;
    }
  }

  if (temp_node->key == key) {
    return temp_node;
  }
  else {
    return NULL;
  }
}

node_t* rbtree_min(const rbtree* t) {
  if (t->root == t->nil) {
    return NULL;
  }

  node_t* temp_node = t->root;

  while (temp_node->left != t->nil) {
    temp_node = temp_node->left;
  }

  return temp_node;
}

node_t* rbtree_max(const rbtree* t) {
  if (t->root == t->nil) {
    return NULL;
  }

  node_t* temp_node = t->root;

  while (temp_node->right != t->nil) {
    temp_node = temp_node->right;
  }

  return temp_node;
}

void rbtree_transplant(rbtree* tree, node_t* node, node_t* adj_node)
{
  if (node->parent == tree->nil) {
    tree->root = adj_node;
  }
  else if (node == node->parent->left) {
    node->parent->left = adj_node;
  }
  else {
    node->parent->right = adj_node;
  }
  adj_node->parent = node->parent;
}

void rbtree_adjust_delete(rbtree* tree, node_t* node) {
  while (node != tree->root && node->color == RBTREE_BLACK) {
    node_t* sibling;
    if (node == node->parent->left) {
      sibling = node->parent->right;
      if (sibling->color == RBTREE_RED) {
        sibling->color = RBTREE_BLACK;
        node->parent->color = RBTREE_RED;
        left_rotate(tree, node->parent);
        sibling = node->parent->right;
      }
      if (sibling->left->color == RBTREE_BLACK && sibling->right->color == RBTREE_BLACK) {
        sibling->color = RBTREE_RED;
        node = node->parent;
      }
      else {
        if (sibling->right->color == RBTREE_BLACK) {
          sibling->left->color = RBTREE_BLACK;
          sibling->color = RBTREE_RED;
          right_rotate(tree, sibling);
          sibling = node->parent->right;
        }
        sibling->color = node->parent->color;
        node->parent->color = RBTREE_BLACK;
        sibling->right->color = RBTREE_BLACK;
        left_rotate(tree, node->parent);
        node = tree->root;
      }
    }
    else {
      sibling = node->parent->left;
      if (sibling->color == RBTREE_RED) {
        sibling->color = RBTREE_BLACK;
        node->parent->color = RBTREE_RED;
        right_rotate(tree, node->parent);
        sibling = node->parent->left;
      }
      if (sibling->right->color == RBTREE_BLACK && sibling->left->color == RBTREE_BLACK) {
        sibling->color = RBTREE_RED;
        node = node->parent;
      }
      else {
        if (sibling->left->color == RBTREE_BLACK) {
          sibling->right->color = RBTREE_BLACK;
          sibling->color = RBTREE_RED;
          left_rotate(tree, sibling);
          sibling = node->parent->left;
        }
        sibling->color = node->parent->color;
        node->parent->color = RBTREE_BLACK;
        sibling->left->color = RBTREE_BLACK;
        right_rotate(tree, node->parent);
        node = tree->root;
      }
    }
  }
  node->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree* tree, node_t* node) {
  if (node == NULL) {
    return 0;
  }
  node_t* to_be_deleted = node;
  node_t* temp;
  color_t to_be_deleted_original_color;
  to_be_deleted_original_color = to_be_deleted->color;
  if (node->left == tree->nil) {
    temp = node->right;
    rbtree_transplant(tree, node, node->right);
  }
  else if (node->right == tree->nil) {
    temp = node->left;
    rbtree_transplant(tree, node, node->left);
  }
  else {
    to_be_deleted = node->right;
    while (to_be_deleted->left != tree->nil) {
      to_be_deleted = to_be_deleted->left;
    }
    to_be_deleted_original_color = to_be_deleted->color;
    temp = to_be_deleted->right;
    if (to_be_deleted->parent == node) {
      temp->parent = to_be_deleted;
    }
    else {
      rbtree_transplant(tree, to_be_deleted, to_be_deleted->right);
      to_be_deleted->right = node->right;
      to_be_deleted->right->parent = to_be_deleted;
    }
    rbtree_transplant(tree, node, to_be_deleted);
    to_be_deleted->left = node->left;
    to_be_deleted->left->parent = to_be_deleted;
    to_be_deleted->color = node->color;
  }
  if (to_be_deleted_original_color == RBTREE_BLACK) {
    rbtree_adjust_delete(tree, temp);
  }
  free(node);
  node = NULL;
  return 0;
}

void c_trip(const rbtree* tree, key_t* arr, const size_t n, node_t* node, int* ind) {     // 중위 순회

  if (node->left != tree->nil) {
    c_trip(tree, arr, n, node->left, ind);
  }
  if (node != tree->nil) {
    arr[*ind] = node->key;
    (*ind)++;
  }
  if (node->right != tree->nil) {
    c_trip(tree, arr, n, node->right, ind);
  }

}

int rbtree_to_array(const rbtree* tree, key_t* arr, const size_t n) {
  int index = 0;            //  arr 에 삽입 될 인덱스 차례
  int* ind = &index;

  c_trip(tree, arr, n, tree->root, ind);

  return 0;
}
