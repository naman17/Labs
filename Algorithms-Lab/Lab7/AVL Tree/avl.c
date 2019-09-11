#include<stdio.h>
#include<stdlib.h>

struct node {
	int value;
	struct node *left, *right;
};

typedef struct node * NODE;

int max(int a, int b) {
	return (a > b) ? a : b;
}

NODE newNode(int x) {
	NODE root = (NODE)malloc(sizeof(struct node));
	root->value = x;
	root->left = root->right = NULL;
	return root;
}

NODE insert(NODE node, int value) 
{ 
    if (node == NULL) return newNode(value); 
    if (value < node->value) 
        node->left  = insert(node->left, value); 
    else if (value > node->value) 
        node->right = insert(node->right, value);
    return node;
}
int count = 0;

int calulateHeight(NODE root) {
	if (root == NULL) {
		return 0;
	}
	return 1 + max(calulateHeight(root->right), calulateHeight(root->left));
}

void findBalanceFactors(NODE root)
{
    if (root == NULL)
        return;
    findBalanceFactors(root->left);
    int balance = calulateHeight(root->left) - calulateHeight(root->right);
    printf("Balance Factor of Root %d is %d\n", root->value, balance);
    findBalanceFactors(root->right);
}



void main() {

	NODE root = NULL;
	printf("Enter Values to insert into BST, enter -1 to stop\n");
	int val = 0;
	while(val != -1){
		scanf("%d", &val);
		if (val != -1)
		{
			root = insert(root, val);
		}
	}
	findBalanceFactors(root);
}