#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
int valuesc;
int levelsc;
typedef struct node{
    int val;
    struct node* left;
    struct node* right;
}node;
int levels(struct node* root, int level);
int values(struct node* root);
void print_positive(struct node* root);
bool check_BST(struct node* root, int min, int max);
bool insert_iter(struct node* root, int val);
node* create_node(int val);
int main(void){
    node* tree = create_node(5);
    if(insert_iter(tree, 4)!=true) exit(1);
    if(insert_iter(tree, 3)!=true) exit(1);
    if(insert_iter(tree, 2)!=true) exit(1);
    if(insert_iter(tree, 6)!=true) exit(1);
    if(insert_iter(tree, 7)!=true) exit(1);
    print_positive(tree);
    if(check_BST(tree, 1, 7)==true) printf("Gitara\n");
    return 0;
}
node* create_node(int val){
    struct node* new_node = malloc(sizeof(node));
    if(new_node!=NULL){
        new_node->val = val;
        new_node->right = NULL;
        new_node->left = NULL;
    }
    return new_node;
}
// Zadanie 1:
// Znajdujemy "środkową" wartość danego przedziału i insertujemy ją.
int values(struct node* root){
    if(root!=NULL){
        valuesc++;
    }
    if(root->left!=NULL) values(root->left);
    if(root->right!=NULL) values(root->right);
    return valuesc;
} // Zadanie 2
int levels(struct node* root, int level){
    level += 1;
    if(root->left!=NULL){
        root = root->left;
        levels(root, level);
    } else{
        if(level>levelsc){
            levelsc = level;
        }
    }
    if(root->right!=NULL){
        root = root->right;
        levels(root, level);
    } else{
        if(level>levelsc){
            levelsc = level;
        }
    }
    return levelsc;
} // Zadanie 3
void print_positive(struct node* root){
    if(root==NULL){
        return;
    }
    print_positive(root->left);
    if(root->val>0) {
        printf("%d\n", root->val);
    }
    print_positive(root->right);

} // Zadanie 4
bool check_BST(struct node* root, int min, int max){
    if(root==NULL) return true;
    if(root->left != NULL && root->left->val > root->val && root->val > max) return false;
    if(root->right != NULL && root->right->val < root->val && root->val < min) return false;
    return check_BST(root->left, root->val < min ? min = root->val : min, root->val > max ? max = root->val : max) && check_BST(root->right, root->val < min ? min = root->val : min, root->val > max ? max = root->val : max);
} // Zadanie 5
void merge(struct node* root, struct node* lisc){
    while (root->right!=NULL){
        root = root->right;
    }
    root->right = lisc;
} // Zadanie 6
bool insert_iter(struct node* root, int val){
    node *temp = root;
    if(temp==NULL){
        return false;
    }
    while (temp!=NULL){
        if(temp->val==val){
            return true;
        }
        if(val < temp->val){
            if(temp->left==NULL){
                temp->left = create_node(val);
                return true;
            } else{
                temp = temp->left;
            }
        } else if(val > temp->val){
            if(temp->right==NULL){
                temp->right = create_node(val);
                return true;
            } else{
                temp = temp->right;
            }
        }
    }
    return false;
} // Zadanie 7