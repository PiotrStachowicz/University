#include <stdio.h>
#include <stdlib.h>
struct elem {
    int val;
    struct elem* next;
    struct elem* head;
    struct elem* tail;
};


struct elem* create(int value);
void append(struct elem* list, int value);
void append_list(struct elem* list1, struct elem* list2);
struct elem* remove_first(struct elem* list);
struct elem* append_first(struct elem* list, int value);
void print(struct elem *element, int i);

int main(void) {
    struct elem* list = create(5),*list2 = create(35);
    append(list,5);
    append(list,25);
    append(list,25);
    append_list(list,list2);
    append(list,25);
    append(list,25);
    append(list,25);
    append(list,25);
    list = remove_first(list);
    list = append_first(list,5);
    print(list);
}

struct elem* create(int value) {
    struct elem* list = calloc(1,sizeof(struct elem));
    if (list == NULL) exit(1);
    list->val = value;
    list->head = list;
    list->tail = list;
    return list;
}
void append(struct elem* list, int value) {
    struct elem* list1 = list;
    list1 = list1->tail;
    list1->next = calloc(1,sizeof(struct elem));
    if (list1->next == NULL) exit(1);
    list1 = list1->next;
    list->tail = list1;
    list1->val = value;
}
void append_list(struct elem* list1, struct elem* list2) {
    struct elem* list3 = list1;
    list3 = list3->tail;
    list3->next = list2;
    list3 = list3->next;
    list3->head = NULL;
    list1->tail = list3->tail;
    list3->tail = NULL;
}
struct elem* remove_first(struct elem* list) {
    if (list->tail == list) return NULL;
    struct elem* list1 = list->next;
    list1->tail = list->tail;
    list1->head = list1;
    free(list);
    return list1;
}
struct elem* append_first(struct elem* list, int value) {
    struct elem* list1 = create(value);
    list1->head = list1;
    list1->tail = list->tail;
    list1->next = list;
    list->head = NULL;
    list->tail = NULL;
    return list1;
}
void print(struct elem *element, int i) {
    while (element != NULL) {
        printf("%d ", element->val);
        element = element->next;
    }
}
