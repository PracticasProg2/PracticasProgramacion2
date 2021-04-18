#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "delivery.h"
#include "product.h"
#include "vertex.h"

#define MAX_DESC 32
#define MAX_WORD 32

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

Delivery* build_delivery(FILE * pf);

Status delivery_add(Delivery* d, Product* p){
    if(!d || !p) return ERROR;

    if(!queue_push(delivery_getPlan(d),p)) return ERROR;

    return OK;
}

Status delivery_run_plan(FILE * pf, Delivery* d){
    if(!pf || !d) return ERROR;
    int c, i;
    char *tag;
    Product *p;
    Queue *q;
    Vertex *v;

    q=delivery_getPlan(d);
    if(!q) return ERROR;

    c=queue_size(q);

    for(i=0;i<c;i++){
        p=queue_pop(q);
        if(!p) return ERROR;
        v= (Vertex*) product_getVertex(p);
        tag= (char *) vertex_getTag(v);
        fprintf(stdout,"Delivering %s requested by %s to %s\n", delivery_getProductName(d), delivery_getName(d), tag);
        product_free(p);
    }
    
    return OK;
}

Delivery* build_delivery(FILE * pf){
    if(!pf) return NULL;
    char *name=NULL, *nameP=NULL, *desc=NULL;
    int c, n, i, p;
    Product *pr=NULL;
    Vertex *v=NULL;
    Delivery *d=NULL;

    name=(char *) malloc (MAX_WORD*sizeof(char));
    if(!name) return NULL;

    nameP=(char *) malloc (MAX_WORD*sizeof(char));
    if(!nameP) {
        free(name);
        return NULL;
    }

    desc=(char *) malloc (MAX_DESC*sizeof(char));
    if(!desc) {
        free(name);
        free(nameP);
        return NULL;
    }
    
    fscanf(pf,"%s %s %d\n", name, nameP, &c);
    fscanf(pf,"%d\n", &n);

    d=delivery_init(name,nameP);
    if(!d){
        free(name);
        free(nameP);
        free(desc);
        return NULL;
    }

    delivery_setCapacity(d,c);

    for(i=0;i<n;i++){
        fscanf(pf,"%d\n", &p);
        fgets(desc,MAX_DESC,pf);

        v=vertex_initFromString(desc);
        pr=product_init(v);
        if(!pr){
            vertex_free(v);
            return NULL;
        }
        product_setAmount(pr,p);
        if (!delivery_add(d,pr)) product_free(pr);
    }

    free(name);
    free(nameP);
    free(desc);
    return d;
}

/*----------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]){
    FILE *f;
    Delivery *d=NULL;

    if (argc!=2){
        return -1;
    }

    f=fopen(argv[1],"r");
    if(!f) return -1;

    d=build_delivery(f);
    if (!d){
        fclose(f);
        return 0;
    }

    delivery_run_plan(stdout,d);

    delivery_free(d);

    fclose(f);

    return 0;
}