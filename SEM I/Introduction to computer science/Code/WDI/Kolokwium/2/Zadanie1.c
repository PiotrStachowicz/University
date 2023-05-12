#include <stdio.h>
#include "stdlib.h"
int m;
struct elem {
    int val;
    struct elem *next;
};
struct elem *usunMax(struct elem *lista);
int gdzieMax(struct elem *lista);
struct elem *usuwaj(struct elem *lista);
int monoton(struct elem *lista);
struct elem *usunOstPar(struct elem *lista);
int parzyste(struct elem *lista);
int main(void){
    struct elem *lista = malloc(sizeof(lista));
    lista->val = 4;
    lista->next = malloc(sizeof(lista));
    lista->next->val = 2;
    lista->next->next = malloc(sizeof(lista));
    lista->next->next->val = 4;
    lista->next->next->next = NULL;
    printf("%d\n", parzyste(lista));

    return 0;
}
struct elem *usunMax(struct elem *lista){
    m = 0;
    struct elem *pomoc = lista;
    while (lista!=NULL){
        if(lista->val > m) m = lista->val;
        lista = lista->next;
    }
    lista = pomoc;
    if(lista->val==m){
        lista = lista->next;
        return lista;
    }else {
        while (lista->next->val != m) {
            lista = lista->next;
        }
        if (lista->next->next != NULL) {
            lista->next = lista->next->next;
        } else {
            lista->next = NULL;
        }
        return pomoc;
    }
}
int gdzieMax(struct elem *lista){
    m = 0;
    struct elem *pomoc = lista;
    while (lista!=NULL){
        if(lista->val > m){
            m = lista->val;
        }
        lista = lista->next;
    }
    lista = pomoc;
    if(lista->val == m) return 1;
    while (lista->next!=NULL){
        lista = lista->next;
    }
    if(lista->val == m) return 1;
    return 0;
}
struct elem *usuwaj(struct elem *lista){
    struct  elem *pomoc = lista;
    if(lista->val % 2 == 0){
        lista = lista->next;
        pomoc = lista;
    }
    while (lista->next!=NULL){
        if(lista->next->val % 2 == 0){
            lista->next = lista->next->next;
        }else{
            lista = lista->next;
        }
    }
    return pomoc;
}
int monoton(struct elem *lista){
    while (lista->next!=NULL){
        if(lista->val<=lista->next->val){
            lista = lista->next;
        } else{
            return 0;
        }
    }
    return 1;
}
struct elem *usunOstPar(struct elem *lista){
    struct elem *pomoc = lista;
    int index = -1;
    int z = 0;
    while (lista!=NULL){
        if(lista->val % 2 == 0){
            index = z;
        }
        z++;
        lista = lista->next;
    }
    z = 0;
    lista = pomoc;
    if(index==0){
        lista = lista->next;
        return lista;
    }else{
        while (z+1!=index){
            lista = lista->next;
            z++;
        }
        lista->next = lista->next->next;
        return pomoc;
    }
}
int parzyste(struct elem *lista){
    int result = 0;
    while(lista!=NULL){
        if(lista->val % 2 == 0) result += lista->val;
        lista = lista->next;
    }
    return result;
}