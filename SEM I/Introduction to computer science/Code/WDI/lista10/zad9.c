#include <stdlib.h>
#include <stdio.h>
struct elem {
    int val;
    struct elem *next;
    struct elem *tail;
    struct elem *head;
};
struct elem* utworz(int wart);
struct elem* remove_first(struct elem* list);
void append_last(struct elem* list, int value);
void print(struct elem *element);
struct elem* remove_last(struct elem* list);
int main(void){
    struct elem* element = utworz(5);
    append_last(element,3);
    append_last(element,2);
    remove_last(element);
    print(element);
    return 0;
}
struct elem *utworz(int wart)
{ //utworzenie nowej jednoelementowej listy
    struct elem *pom;
    pom=calloc(1,sizeof(struct elem));
    pom->val = wart;
    pom->tail = pom;
    pom->head = pom;
    pom->next = NULL;
    return pom;
}
struct elem* remove_first(struct elem* list) {
    if (list->tail == list) return NULL;
    struct elem* list1 = list->next;
    list1->tail = list->tail;
    list1->head = list1;
    free(list);
    return list1;
}
struct elem* remove_last(struct elem* list) {
    if (list == NULL) {
        return NULL;
    }
    if (list->next == NULL) {
        free(list);
        return NULL;
    }
    struct elem* last = list;
    while (last->next != NULL) {
        last = last->next;
    }
    last->tail->next = NULL;
    last->tail = NULL;
    free(last);
    return list;
}
void append_last(struct elem* list, int value) {
    struct elem* list1 = utworz(value);
    while (list->next!=NULL){
        list = list->next;
    }
    list1->tail = list->head;
    list->next = list1;
}
void print(struct elem *element) {
    while (element != NULL) {
        printf("%d ", element->val);
        element = element->next;
    }
}
