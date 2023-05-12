#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
typedef struct node *pnode;
typedef struct node{
    int val;
    pnode left;
    pnode right;
} snode;
bool czyKopiec(pnode drzewo);
int main(void){
    snode *tree = malloc(sizeof(snode));
    tree->val = 5;
    tree->left = malloc(sizeof(snode));
    tree->left->val = 6;
    tree->right = malloc(sizeof(snode));
    tree->right->val = 6;
    tree->right->left = NULL;
    tree->right->right = NULL;
    tree->left->left = NULL;
    tree->left->right = NULL;
    if(czyKopiec(tree)==true){
        printf("Kopiec!");
    } else{
        printf("Nie kopiec!");
    }
    return 0;
}
bool czyKopiec(pnode drzewo){
    if(drzewo==NULL) return true;
    if(drzewo->left != NULL && drzewo->right == NULL) return false;
    if(drzewo->left == NULL && drzewo->right != NULL) return false;
    if(drzewo->left !=NULL && drzewo->val >= drzewo->left->val) return false;
    if(drzewo->right !=NULL && drzewo->val >= drzewo->right->val) return false;
    return czyKopiec(drzewo->left) && czyKopiec(drzewo->right);
}
