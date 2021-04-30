#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "list.h"


typedef struct _NodeList {
    void* data;
    struct _NodeList *next;
} NodeList;

struct _List {
    NodeList *last;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

NodeList *node_new();

NodeList *node_new() {
    NodeList *pn = NULL;

    pn = (NodeList *)malloc(sizeof(NodeList));

    if (!pn) {
        return NULL;
    }

    pn->data = NULL;
    pn->next = NULL;

    return pn;
}


/*----------------------------------------------------------------------------------------*/
List *list_new(){
    List *pl = NULL;

    pl = (List *)malloc(sizeof(List));

    if (pl == NULL) {
        return NULL;
    }

    pl->last = NULL;

    return pl;
}

Bool list_isEmpty(const List *pl){
    if(!pl) return TRUE;

    if (pl->last == NULL){
        return TRUE;
    }

    return FALSE;
}


Status list_pushFront(List *pl, void *e){

    NodeList *pn = NULL;

    if (pl == NULL || e == NULL) {
        return ERROR;
    }

    pn = node_new();

    if (pn == NULL) {
        return ERROR;
    }

    pn->data = e;

    if (list_isEmpty(pl)) {
        pn->next = pn;
        pl->last = pn;
    }

    else {
        pn->next = pl->last->next;
        pl->last->next = pn;
    }

    return OK;
}

Status list_pushBack(List *pl, void *e){
    NodeList *pn = NULL;

    if (pl == NULL || e == NULL) {
        return ERROR;
    }
    pn = node_new();
    if (pn == NULL) {
        return ERROR;
    }

    pn->data = e;

    if (list_isEmpty(pl) == TRUE) {
        pn->next = pn;
        pl->last = pn;
    }

    else {
        pn->next = pl->last->next;
        pl->last->next = pn;
        pl->last = pn;
    }

    return OK;
}

Status list_pushInOrder (List *pl, void *e, P_ele_cmp f, int order) {
    
    if (!pl || !e || f==NULL || order==0) return ERROR;

    NodeList *n=NULL, *n2=NULL;
    int i, s;

    n2=node_new();
    if(n2 == NULL) return ERROR;
    
    n2->data=e;

    if(list_isEmpty(pl)==TRUE){
        pl->last=n2;

        return OK;
    }
    
    s=list_size(pl);

    n=pl->last->next;

    if (order > 0){
        for (i=0;i<s;i++){
            if(s==1){
                if(f(pl->last->data,e)>=0){
                    list_pushBack(pl,e);
                    return OK;
                }
                else{
                    list_pushFront(pl,e);
                    return OK;
                }
            }
            if (f(n->data,e)>=0){
                n2->next=n->next;
                n->next=n2;
                return OK;
            }
            else
                n=n->next;
        }
    }

    else {
        for (i=0;i<s;i++){
            if (f(n->data,e)>=0){
                n2->next=n->next;
                n->next=n2;
                return OK;
            }
            else
                n=n->next;
        }
    }

    return OK;
}

void *list_popFront (List *pl) {
    NodeList *pn = NULL;
    void *pe = NULL;

    if (pl == NULL || list_isEmpty(pl) == TRUE)
        return NULL;

    pn = pl->last->next;
    pe = pn->data;

    if (pl->last->next == pl->last)
        pl->last = NULL;

    else
        pl->last->next = pn->next;

    free(pn);
    return pe;
}

void *list_popBack(List *pl){
    NodeList *pn = NULL;
    void *pe = NULL;
    if (pl == NULL || list_isEmpty(pl) == TRUE)
        return NULL;

    if (pl->last->next == pl->last) {
        pe = pl->last->data;
        free(pl->last);
        pl->last = NULL;
        return pe;
    }

    pn = pl->last;

    while (pn->next != pl->last)
        pn = pn->next;

    pe = pl->last->data;
    pn->next = pl->last->next;
    free(pl->last);
    pl->last = pn;

    return pe;
}

void list_free(List *pl){
    if (pl == NULL) {
        return;
    }

    while (list_isEmpty(pl) == FALSE) {
        list_popFront(pl);
    }

    free(pl);
}

size_t list_size(const List *pl){
    if (!pl) return 0;
    if(list_isEmpty(pl) == TRUE) return 0;

    NodeList *n;
    n=pl->last;
    size_t s;

    for(s=1;n->next!=pl->last;s++){
        if(s==1 && n->next==NULL) return 1;
        n=n->next;
    }

    return s;
}

int list_print(FILE *fp, const List *pl, P_ele_print f){
    if(!fp || !pl || f==NULL) return -1;
    NodeList *n;
    int i, s, l=0;

    s=list_size(pl);

    if(s==1){
        l+=fprintf(fp,"SIZE: %d\n",s);
        l+=f(fp,pl->last->data);
        l+=fprintf(fp,"\n");
        return l;
    }

    n=pl->last->next;
    l+=fprintf(fp,"SIZE: %d\n",s);

    for(i=0;i<s;i++){
        if(n->data==NULL) break;

        l+=f(fp,n->data);
        l+=fprintf(fp," ");

        n=n->next;
    }

    l+=fprintf(fp,"\n");

    return l;
}