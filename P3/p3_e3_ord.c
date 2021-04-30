#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "file_utils.h"

#define MAX_DESC 32

int main (int argc, char *argv[]) {
    if (argc != 3) return -1;

    FILE *f;
    List *l=NULL, *l2=NULL;
    int i, n, s, o;
    float *fl=NULL, *fl2=NULL;

    o=atoi(argv[2]);

    f=fopen(argv[1],"r");
    if(f==NULL) return -1;

    l=list_new();
    if(l==NULL){
        fclose(f);
        return -1;
    }

    l2=list_new();
    if(l==NULL){
        list_free(l);
        fclose(f);
        return -1;
    }

    fscanf(f,"%d\n",&n);

    fl= (float *) malloc(n*sizeof(float));
    if(!fl){
        list_free(l);
        list_free(l2);
        fclose(f);
        return -1;
    }
  
    for(i=1;i<=n;i++){
        fscanf(f,"%f",&fl[i-1]);
        if(!fl){
            free(fl);
            list_free(l2);
            list_free(l);
            fclose(f);
        }
        if(i%2==1){
            list_pushBack(l,&fl[i-1]);
        }
        else{
            list_pushFront(l,&fl[i-1]);
        }
    }

    fl2= (float *) malloc(n*sizeof(float));
    if(!fl2){
        free(fl);
        list_free(l);
        list_free(l2);
        fclose(f);
        return -1;
    }

    list_print(stdout,l,float_print);

    s=list_size(l);

    printf("Finished inserting. Now we extract from the beginningand insert in order:\n");

    for(i=0;i<s/2;i++){
        list_pushInOrder(l2,list_popFront(l),float_cmp,o);
        list_print(stdout,l2,float_print);
    }

    printf("\nNow we extract from the end:\n");
/*
    while(list_isEmpty(l)==FALSE){
        v=list_popBack(l);
        vertex_print(stdout,v);
        vertex_free(v);
    }

    printf("\n");
*/
    free(fl);
    list_free(l);
    fclose(f);

    return 0;
}