//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode
{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode; // You should not change the definition of BSTNode

typedef struct _stackNode
{
	BSTNode *data;
	struct _stackNode *next;
} StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
} Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS1(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS1(BSTNode *root)
{
	if (root == NULL) // 루트가 NULL이면 함수 종료
		return;

	Stack *s = malloc(sizeof(Stack)); // 스택을 할당하여 생성
	BSTNode *last_visited = NULL;	  // 마지막으로 방문한 노드를 나타내는 포인터 초기화

	while (1) // 무한 루프 시작
	{
		while (root != NULL) // 현재 노드가 NULL이 아닐 때까지 반복
		{
			push(s, root);	   // 현재 노드를 스택에 푸시
			root = root->left; // 왼쪽 자식 노드로 이동
		}

		if (isEmpty(s)) // 스택이 비어있으면 무한 루프 종료
			break;

		root = peek(s); // 스택의 맨 위 노드를 확인

		// 오른쪽 자식이 비어있거나 오른쪽 자식을 이미 방문했을 경우
		if (root->right == NULL || root->right == last_visited)
		{
			printf("%d ", root->item); // 현재 노드의 값을 출력 (후위 순회)
			pop(s);					   // 스택에서 현재 노드를 팝
			last_visited = root;	   // 마지막으로 방문한 노드를 현재 노드로 설정
			root = NULL;			   // 현재 노드를 NULL로 설정하여 다음 반복에서 스택에서 팝하도록 함
		}
		else // 오른쪽 자식이 아직 방문되지 않았을 경우
		{
			root = root->right; // 오른쪽 자식 노드로 이동하여 다음 반복에서 처리
		}
	}

	free(s); // 스택에 할당된 메모리 해제
}

// void postOrderIterativeS1(BSTNode *root)
// {
// 	Stack *s = malloc(sizeof(Stack));
// 	BSTNode *last_visited = NULL;
// 	if (root == NULL)
// 	{
// 		return;
// 	}

// 	while (root != NULL)
// 	{
// 		push(s, root);
// 		root = root->left;
// 	}

// 	while (isEmpty(s) != 1)
// 	{
// 		root = pop(s);
// 		if (root->right != NULL)
// 		{
// 			push(s, root->right);
// 			last_visited = root->right;
// 		}
// 		else if (last_visited == root->right)
// 		{
// 			printf("%d ", root->item);
// 			continue;
// 		}
// 		else
// 		{
// 			printf("%d ", root->item);
// 			continue;
// 		}
// 	}
// }

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL)
		{
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value > (*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}

BSTNode *pop(Stack *s)
{
	StackNode *temp, *t;
	BSTNode *ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode *peek(Stack *s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
