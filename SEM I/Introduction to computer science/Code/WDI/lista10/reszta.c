#include <stdlib.h>
#include <stdio.h>
struct elem {
    int val;
    struct elem *next;
};
void print(struct elem *element);
struct elem *utworz(int wart);
void insert_to_end_z1(int value, struct elem *element);
void delete_last_z2(struct elem *element);
void append_two_lists_z3(struct elem *list1, struct elem *list2);
void delete_val_z4(struct elem *list, int val);
struct elem* reverse_z7(struct elem* list);
void print_reverse_z6(struct elem* list);
int main(void){
    struct elem *lista1 = utworz(1);
    insert_to_end_z1(3,lista1);
    insert_to_end_z1(3,lista1);
    insert_to_end_z1(4,lista1);
    print_reverse_z6(lista1);
    return 0;
}

void print(struct elem *element) {
    while (element!=NULL){
        printf("%d\n", element->val);
        element = element->next;
    }
}
struct elem *utworz(int wart)
{ //utworzenie nowej jednoelementowej listy
    struct elem *pom;
    pom=(struct elem *) malloc(sizeof(struct elem));
    pom->val = wart;
    pom->next = NULL;
    return pom;
}
void insert_to_end_z1(int value, struct elem *element){
    struct elem *temp = element;
    while (temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = utworz(value);
}
void delete_last_z2(struct elem *element){
    while (element->next->next!=NULL){
        element = element->next;
    }
    element->next = NULL;
}
void append_two_lists_z3(struct elem *list1, struct elem *list2){
    while (list1->next!=NULL){
        list1 = list1->next;
    }
    list1->next = list2;
}
void delete_val_z4(struct elem *list, int val){
    struct elem* list_copy1 = list,  *list_copy2 = list;
    while (list!=NULL){
        if (list_copy1->val == val) {
            list_copy1 = list_copy1->next;
            free(list);
            list = list_copy1;
            list_copy2 = list;
        }
        else if (list->val == val) {
            list_copy2->next  = list_copy2->next->next;
            free(list);
            list = list_copy2->next;
        }
        else {
            list_copy2 = list;
            list = list->next;
        }
    }
}
struct elem* reverse_z7(struct elem* list) {
    struct elem* list_copy = list, *remember = NULL;
    while (list != NULL) {
        list = list->next;
        list_copy->next = remember;
        remember = list_copy;
        list_copy = list;
    }
    return remember;
}
void print_reverse_z6(struct elem* list){
    struct elem* list_copy = list, *remember = NULL;
    while (list_copy!=remember){
        while (list->next!=remember){
            list = list->next;
        }
        printf("%d\n", list->val);
        remember = list;
        list = list_copy;
    }
}