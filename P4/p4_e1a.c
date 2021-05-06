#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "vertex.h"
#include "bstree.h"

int main () {

    BSTree *tree=NULL;
    void *min;
    void *max;
    Vertex **v;
    int i, n;

    v= (Vertex **) malloc (10*sizeof(Vertex *));

    tree=tree_init(vertex_print,vertex_cmp);

    if(!tree) return -1;


    v[0]=vertex_initFromString("id:100 tag:Madrid");
    if(tree_insert(tree,v[0])==ERROR)
        tree_destroy(tree);
    
    v[1]=vertex_initFromString("id:300 tag:Barcelona");
    if(tree_insert(tree,v[1])==ERROR)
        tree_destroy(tree);
    
    v[2]=vertex_initFromString("id:900 tag:Salamanca");    
    if(tree_insert(tree,v[2])==ERROR)
        tree_destroy(tree);

    v[3]=vertex_initFromString("id:400 tag:Huelva");
    if(tree_insert(tree,v[3])==ERROR)
        tree_destroy(tree);

    v[4]=vertex_initFromString("id:700 tag:Oviedo");
    if(tree_insert(tree,v[4])==ERROR)
        tree_destroy(tree);

    v[5]=vertex_initFromString("id:200 tag:Valencia");
    if(tree_insert(tree,v[5])==ERROR)
        tree_destroy(tree);

    v[6]=vertex_initFromString("id:600 tag:Lugo");
    if(tree_insert(tree,v[6])==ERROR)
        tree_destroy(tree);

    v[7]=vertex_initFromString("id:500 tag:Sevilla");
    if(tree_insert(tree,v[7])==ERROR)
        tree_destroy(tree);

    v[8]=vertex_initFromString("id:800 tag:Murcia");
    if(tree_insert(tree,v[8])==ERROR)
        tree_destroy(tree);

    n=tree_size(tree);

    min=tree_find_min(tree);

    max=tree_find_max(tree);

    fprintf(stdout,"El menor elemento del arbol es: ");
    vertex_print(stdout,min);
    fprintf(stdout,"\n");

    fprintf(stdout,"El mayor elemento del arbol es: ");
    vertex_print(stdout,max);
    fprintf(stdout,"\n");

    if(tree_contains(tree,v[6])==TRUE){
        fprintf(stdout,"El elemento ");
        vertex_print(stdout,v[6]);
        fprintf(stdout,"está dentro del árbol.\n");
    }

    else {
        fprintf(stdout,"El elemento ");
        vertex_print(stdout,v[6]);
        fprintf(stdout,"no está contenido del árbol.\n");
    }

    v[9]=vertex_initFromString("id:1000 tag:Pamplona");

    if(tree_contains(tree,v[9])==TRUE){
        fprintf(stdout,"El elemento ");
        vertex_print(stdout,v[9]);
        fprintf(stdout," está dentro del árbol.\n");
    }

    else {
        fprintf(stdout,"El elemento ");
        vertex_print(stdout,v[9]);
        fprintf(stdout," no está contenido del árbol.\n");
    }

    for(i=0;i<n+1;i++)
        vertex_free(v[i]);

    free(v);

    tree_destroy(tree);

    return 0;
}