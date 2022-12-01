#include "rbtree.h"
#include <stdlib.h>

#define SENTINEL
rbtree *new_rbtree(void)
{
	// TODO: initialize struct if needed
	rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
	node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));
	if (!p || !nilNode)
	{
		printf("error");
		return 0;
	}
	nilNode->color = RBTREE_BLACK;
	nilNode->key = 0;
	nilNode->parent = NULL;
	nilNode->left = NULL;
	nilNode->right = NULL;
	p->nil = nilNode;
	p->root = p->nil;
	return p;
}

node_t *new_node(key_t value)
{
	node_t *node = (node_t *)calloc(1, sizeof(node_t));
	node->color = RBTREE_RED;
	node->key = value;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void delete_by_postorder(rbtree *t, node_t *root)
{
	if (root == t->nil)
		return;
	delete_by_postorder(t, root->left);
	delete_by_postorder(t, root->right);
	free(root);
}
void delete_rbtree(rbtree *t)
{
	// TODO: reclaim the tree nodes's memory
	if (!t)
		return;
	// 트리를 후위순회하며 각 노드에 할당된 메모리를 free한다.
	delete_by_postorder(t, t->root);
	free(t->nil);
	free(t);
}

void left_rotate(rbtree *t, node_t *x)
{
	// set y
	node_t *y;
	y = x->right;

	// y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 전환
	x->right = y->left;
	if (y->left != t->nil)
		y->left->parent = x;
	// x의 부모 노드를 y의 부모 노드로 바꿔준다
	y->parent = x->parent;
	if (x->parent == t->nil)
		t->root = y;

	// x가 x의 부모의 왼쪽이면
	else if (x == x->parent->left)
		x->parent->left = y;
	// x가 x의 부모의 오른쪽이면
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void right_rotate(rbtree *t, node_t *y)
{
	// set y
	node_t *x;
	x = y->left;

	// x의 오른쪽 서브트리를 y의 왼쪽 서브트리로 전환
	y->left = x->right;
	if (x->right != t->nil)
		x->right->parent = y;
	// x의 부모를 y의 부모로 바꿔준다
	x->parent = y->parent;
	if (y->parent == t->nil)
		t->root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;
	y->parent = x;
}

void insert_fix_up(rbtree *t, node_t *z)
{
	node_t *uncle;
	node_t *parent;
	node_t *grandpa;

	while (z->parent->color == RBTREE_RED)
	{
		parent = z->parent;
		grandpa = z->parent->parent;
		// 부모 노드가 할아버지 노드의 왼쪽 노드일 경우
		if (parent == grandpa->left)
		{
			uncle = grandpa->right;
			// 삼촌 노드가 레드일 경우
			if (uncle->color == RBTREE_RED)
			{
				uncle->color = RBTREE_BLACK;
				parent->color = RBTREE_BLACK;
				grandpa->color = RBTREE_RED;
				z = grandpa;
			}
			else
			{
				// 꺽인 상태
				if (z == parent->right)
				{
					z = parent;
					left_rotate(t, z);
				}
				z->parent->parent->color = RBTREE_RED;
				z->parent->color = RBTREE_BLACK;
				right_rotate(t, z->parent->parent);
			}
		}
		// 부모 노드가 할아버지 노드의 오른쪽 노드일 경우
		else
		{
			uncle = grandpa->left;
			// 삼촌 노드가 레드일 경우
			if (uncle->color == RBTREE_RED)
			{
				uncle->color = RBTREE_BLACK;
				parent->color = RBTREE_BLACK;
				grandpa->color = RBTREE_RED;
				z = grandpa;
			}
			else
			{
				// 꺽인 상태
				if (z == parent->left)
				{
					z = parent;
					right_rotate(t, z);
				}
				z->parent->parent->color = RBTREE_RED;
				z->parent->color = RBTREE_BLACK;
				left_rotate(t, z->parent->parent);
			}
		}
	}
	t->root->color = RBTREE_BLACK;
};
node_t *rbtree_insert(rbtree *t, const key_t key)
{
	// TODO: implement insert
	node_t *y = t->nil;
	node_t *x = t->root;
	node_t *z = new_node(key); // 새로운 노드의 메모리를 할당한다.

	// 삽입하려는 key 값과 비교 노드 x->key 값을 비교하며 x를 갱신해간다.
	while (x != t->nil)
	{
		y = x;
		if (key < x->key)
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
	// 삽입 노드의 색은 항상 레드
	z->color = RBTREE_RED;
	// RB트리의 조건에 맞게 fix-up 진행
	insert_fix_up(t, z);
	return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
	// TODO: implement find
	node_t *temp = t->root;
	while (temp != t->nil)
	{
		if (key > temp->key)
			temp = temp->right;
		else if (key < temp->key)
			temp = temp->left;
		else
			return temp;
	}
	// 해당하는 노드가 없으면 NULL반환
	return NULL;
}

// 트리의 최소값을 가지는 노드를 반환
node_t *rbtree_min(const rbtree *t)
{
	// TODO: implement find
	node_t *node = t->root;
	while (node->left != t->nil)
		node = node->left;
	return node;
}

// 트리의 최대값을 가지는 노드를 반환
node_t *rbtree_max(const rbtree *t)
{
	// TODO: implement find
	node_t *node = t->root;
	while (node->right != t->nil)
		node = node->right;
	return node;
}

// 해당 노드의 오른쪽 서브트리의 노드 중 최소 노드를 반환
node_t *find_successor(rbtree *t, node_t *z)
{
	while (z->left != t->nil)
		z = z->left;
	return z;
}
void erase_fix_up(rbtree *t, node_t *x)
{

	node_t *w; // x의 형제 노드
	// x가 루트이거나 x가 레드이면 while문을 종료한다.

	while (x != t->root && x->color == RBTREE_BLACK)
	{
		// x가 x의 부모의 왼쪽 자식일 경우
		if (x == x->parent->left)
		{
			w = x->parent->right;
			// 경우1. x의 형제 노드가 레드일 때
			if (w->color == RBTREE_RED)
			{
				x->parent->color = RBTREE_RED;
				w->color = RBTREE_BLACK;
				left_rotate(t, x->parent);
				w = x->parent->right;
			}
			// 경우2. x의 형제의 왼쪽 자식, 오른쪽 자식이 둘 다 블랙일 때
			if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
			{
				w->color = RBTREE_RED;
				x = x->parent;
			}

			else
			{
				// 경우3. w는 블랙, w의 왼쪽 자식이 레드일 때
				if (w->left->color == RBTREE_RED)
				{
					w->color = RBTREE_RED;
					w->left->color = RBTREE_BLACK;
					right_rotate(t, w);
					w = x->parent->right;
				}
				// 경우4. w는 블랙, w의 오른쪽 자식이 레드일 때
				w->color = x->parent->color;
				x->parent->color = RBTREE_BLACK;
				w->right->color = RBTREE_BLACK;
				left_rotate(t, x->parent);
				x = t->root;
			}
		}
		// x가 x의 부모의 오른쪽 자식일 경우
		else
		{
			w = x->parent->left;
			// 경우1. x의 형제 노드가 레드일 때
			if (w->color == RBTREE_RED)
			{
				x->parent->color = RBTREE_RED;
				w->color = RBTREE_BLACK;
				right_rotate(t, x->parent);
				w = x->parent->left;
			}
			// 경우2. x의 형제의 왼쪽 자식, 오른쪽 자식이 둘 다 블랙일 때
			if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
			{
				w->color = RBTREE_RED;
				x = x->parent;
			}

			else
			{
				// 경우3. w는 블랙, w의 오른쪽 자식이 레드일 때
				if (w->right->color == RBTREE_RED)
				{
					w->color = RBTREE_RED;
					w->right->color = RBTREE_BLACK;
					left_rotate(t, w);
					w = x->parent->left;
				}
				// 경우4. w는 블랙, w의 왼쪽 자식이 레드일 때
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
int rbtree_erase(rbtree *t, node_t *z)
{
	// TODO: implement erase
	node_t *y; // 실제 삭제할 노드를 가르키는 포인터
	node_t *x;

	// 삭제할 노드 선택
	// 1. 삭제 노드의 자식 노드가 하나 또는 없는 경우일 때
	if (z->left == t->nil || z->right == t->nil)
		y = z;
	// 2. 삭제 노드의 자식 노드가 둘일 경우
	else
		y = find_successor(t, z->right);

	// 삭제할 노드의 자식노드 x는 nil 노드를 가르킬 수도 있음
	if (y->left != t->nil)
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;

	// 삭제할 노드가 루트인 경우
	if (y->parent == t->nil)
		t->root = x;
	// 삭제할 노드가 부모의 왼쪽 자식인 경우
	else if (y->parent->left == y)
		y->parent->left = x;
	// 삭제할 노드가 부모의 오른쪽 자식인 경우
	else
		y->parent->right = x;

	// 실제로 삭제할 노드가 삭제 노드와 다른 경우
	if (y != z)
	{
		z->key = y->key;
	}
	// 삭제한 노드가 레드이면 RB트리 조건을 위반하지 않는다
	if (y->color == RBTREE_BLACK)
		erase_fix_up(t, x);
	// 할당된 메모리 free 후 종료
	free(y);
	return 0;
}

// 트리를 중위순회하며 순서대로 주어진 배열에 하나씩 저장한다.
int inorder_traversing(const rbtree *t, node_t *node, key_t *arr, int i)
{
	if (node == t->nil)
		return i;
	i = inorder_traversing(t, node->left, arr, i);
	arr[i] = node->key;
	i += 1;
	i = inorder_traversing(t, node->right, arr, i);
	return i;
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
	// TODO: implement to_array
	inorder_traversing(t, t->root, arr, 0);
	return 0;
}