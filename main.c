#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"
#include "header.h"

int main(int argc, char *argv[]){	
        if(argc != 4){
                return(EXIT_FAILURE);
        }
        if(strcmp(argv[1],"-b") == 0){	
		FILE *fp = fopen(argv[2], "rb");
        	if(fp == NULL){
			printf("FAIL-1\n");
                	return(EXIT_FAILURE);
        	}
	        fseek(fp, 0, SEEK_END);
        	int size = ftell(fp) / 5;
	        fseek(fp, 0, SEEK_SET);
        	int keys[10000];
    		char actions[10000];
        	char ch;
       		for(int counter = 0; counter < size; counter++){
         		ch = fgetc(fp);
                	keys[counter] = ch;
                	ch = fgetc(fp);
                	ch = fgetc(fp);
                	ch = fgetc(fp);
                	ch = fgetc(fp);
                	actions[counter] = ch;
        	}
		Tnode *root = NULL;
		for(int i = 0; i <= size; i++){
			if(actions[i] == 105){
				root = insertNode(root,keys[i]); 	
			}
			else if(actions[i] == 100){
				root = deleteNode(root,keys[i]);
			}
		}
		FILE *output = fopen(argv[3], "wb");
		preOrderBinary(root, output);
		fclose(output);
		fclose(fp);
		return(EXIT_SUCCESS);
	}
}

void preOrderBinary(Tnode *root, FILE *fileName)
{
	int nodes =0;
 	if(root != NULL)
   	{
        	if(root->right != NULL && root->left != NULL){
			nodes = 3;
		}
		else if(root->right != NULL){
			nodes = 1;
		}
		else if(root->left != NULL){
			nodes = 2;
		}		
		fwrite(&root->key, sizeof(int), 1, fileName);
		printf("%d\n", root->key);
		fwrite(&nodes, 1, 1, fileName);
        	preOrderBinary(root->left, fileName);
        	preOrderBinary(root->right, fileName);
    	}	
}

int height(Tnode *node){
	if(node == NULL){
		return 0;
	}
	return( node->height);
}

Tnode *insertNode(Tnode *node, int key){
	//base case and starting root
	if(node == NULL){
		return(createNode(key));
	}
	
	//to the left
	if(node->key >= key){
		node->left = insertNode(node->left, key);
	}
	//to the right
	else if(node->key < key){
		node->right = insertNode(node->right, key);
	}
	else{
		return node;
	}

	//updating height of node
	if(height(node->left) > height(node->right)){
		node->height = height(node->left) + 1;
	}
	else if(height(node->left) < height(node->right)){
		node->height = height(node->right) + 1;
	}

	//calculating balance of node 
	int balance = calcBalance(node);

	//checking if balance or need to be rotated 
	
	//left leaning 
	if (balance > 1 && key < node->left->key){
		return rightRotate(node);
	}
	//left then right leaning 
	if (balance > 1 && key > node->left->key){
    		node->left = leftRotate(node->left);
    		return rightRotate(node);
	}
	//right leaning 
	if (balance < -1 && key > node->right->key){
    		return leftRotate(node);
	}
	//right then left leaning 
	if (balance < -1 && key < node->right->key){
    		node->right = rightRotate(node->right);
    		return leftRotate(node);
	}
	
	//end of insertion return root
	return node;
}

Tnode *rightRotate(Tnode  *a) {
  	
	Tnode *b = a->left;
  	Tnode *c = b->right;
	
	//right rotation
  	b->right = a;
  	a->left = c;

  	a->height = max(height(a->left), height(a->right)) + 1;
  	b->height = max(height(b->left), height(b->right)) + 1;

  	return b;
}


Tnode *leftRotate(Tnode *b) {
 	Tnode *a = b->right;
 	Tnode *c = a->left;
	
	//left rotation
  	a->left = b;
  	b->right = c;

 	b->height = max(height(b->left), height(b->right)) + 1;
  	a->height = max(height(a->left), height(a->right)) + 1;

  	return a;
}
int max(int v1, int v2){
	return ( (v1 > v2) ? v1 : v2);
}

int calcBalance(Tnode *node){
	if(node == NULL){
		return 0;
	}
	else{
		int balance = (height(node->left) - height(node->right));
		return balance;
	}
}

Tnode *createNode(int key){
	Tnode *node = malloc(sizeof(Tnode));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}


Tnode *minValueNode(Tnode *node) {
  Tnode *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

Tnode *deleteNode(Tnode *root, int key) {
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key >= root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      Tnode *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      Tnode *temp = minValueNode(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = calcBalance(root);
  if (balance > 1 && calcBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && calcBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && calcBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && calcBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}
/*
Tnode *deleteNode(Tnode *root, int key){
	if(root == NULL){
		return NULL;
	}
	if(key < root->key){
		root->left = deleteNode(root->left, key);
	}
	else if(key > root->key){
		root->right = deleteNode(root->right, key);
	}
	else{
		Tnode *prev = root;
		Tnode *curr = root;
		curr = curr->left;
		if(curr == NULL){
			prev = prev->right;
			free(root);
			return(prev);
		}	
		while(curr->right != NULL){
			prev = curr;
			curr = curr->right;
		}
		if(prev->left == curr){
			prev->left = curr->left;
		}
		else{
			prev->right = curr->right;
		}
		curr->left = root->left;
		curr->right = root->right;
		free(root);
		return(curr);
	}
}
*/
