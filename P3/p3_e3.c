#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "vertex.h"

#define MAX_DESC 32

int main (int argc, char *argv[]) {
    if (argc != 2) return -1;

    FILE *f;
    List *l=NULL;
    Vertex *v=NULL;
    int i, n, s;
    char desc[MAX_DESC];

    f=fopen(argv[1],"r");
    if(f==NULL) return -1;

    l=list_new();
    if(l==NULL){
        fclose(f);
        return -1;
    }

    fscanf(f,"%d\n",&n);
  
    for(i=1;i<=n;i++){
        fgets(desc,MAX_DESC,f);
        v=vertex_initFromString(desc);
        if(!v){
            while(list_isEmpty(l)==FALSE)
                vertex_free(list_popFront(l));
            list_free(l);
            fclose(f);
        }
        if(i%2==1){
            list_pushBack(l,v);
        }
        else{
            list_pushFront(l,v);
        }
    }

    list_print(stdout,l,vertex_print);

    s=list_size(l);

    printf("Finished inserting. Now we extract from the beginning:\n");

    for(i=0;i<s/2;i++){
        v=list_popFront(l);
        vertex_print(stdout,v);
        vertex_free(v);
    }

    printf("\nNow we extract from the end:\n");

    while(list_isEmpty(l)==FALSE){
        v=list_popBack(l);
        vertex_print(stdout,v);
        vertex_free(v);
    }

    printf("\n");

    list_free(l);
    fclose(f);

    return 0;
}