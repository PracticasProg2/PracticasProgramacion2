#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_utils.h"
#include "stack_fDoble.h"
#include "vertex.h"

#define MAX_DESCR 1024

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout){
  if (!sin1 || !sin2 || !sout) return ERROR;
  Vertex *v=NULL;
  Stack *aux;
  
  while (stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
    if (stack_top(sin1)==NULL || stack_top(sin2) ==NULL) return ERROR;
    if(vertex_cmp(stack_top(sin1),stack_top(sin2))>0)
      v=stack_pop(sin1);
    else
      v=stack_pop(sin2);
    stack_push(sout,v);
  }
  
  if(stack_isEmpty(sin1)==TRUE)
    aux=sin2;
  else
    aux=sin1;
  
  while (stack_isEmpty(aux)==FALSE){
    v=stack_pop(aux);
    stack_push(sout,v);
  }
  
  return OK;
}

/*----------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]){

  if(argc!=3) return -1;
  
  char *aux=NULL;
  int i, size1, size2;
  Vertex **e=NULL, **h=NULL;
  FILE *f2;
  FILE *f1;
  
  Stack *sin1 = stack_init();
  if(!sin1) return -1;
  Stack *sin2 = stack_init();
  if(!sin2){
    stack_free(sin1);
    return -1;
  }
  Stack *sout = stack_init();
  if(!sout){
    stack_free(sin1);
    stack_free(sin2);
    return -1;
  }
  
  aux=(char*)malloc(MAX_DESCR*sizeof(char));
  if(!aux){
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
  }
  
  f1=fopen(argv[1], "r");
  if(!f1){
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    free(aux);
    return -1;
  }
  
  f2=fopen(argv[2], "r");
  if(!f2){
    fclose(f1);
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    free(aux);
    return -1;
  }
  
  fscanf(f1, "%d\n", &size1);
  
  fscanf(f2, "%d\n", &size2);
  
  e = (Vertex**) malloc ((size1)*sizeof(Vertex*));
  if(!e){
    fclose(f1);
    fclose(f2);
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    free(aux);
    return -1;
  }
  
  h = (Vertex**) malloc ((size2)*sizeof(Vertex*));
  
  if(!h){
    fclose(f1);
    fclose(f2);
    free(e);
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    free(aux);
    return -1;
  }
  
  for(i=0;i<size1;i++){
    fgets(aux,MAX_DESCR,f1);
    e[i]=vertex_initFromString(aux);
    stack_push(sin1,e[i]);
  }
  
  for(i=0;i<size2;i++){
    fgets(aux,MAX_DESCR,f2);
    h[i]=vertex_initFromString(aux);
    stack_push(sin2,h[i]);
  }
  
  printf("Ranking 0:\n");
  stack_print(stdout, sin1, vertex_print);
  printf("Ranking 1:\n");
  stack_print(stdout, sin2, vertex_print);
  mergeStacks(sin1,sin2,sout);
  printf("Joint Ranking:\n");
  stack_print(stdout, sout, vertex_print);
  
  fclose(f1);
  fclose(f2);
  for(i=0;i<size1;i++)
    vertex_free(e[i]);
  for(i=0;i<size2;i++)
    vertex_free(h[i]);
  free(e);
  free(h);
  stack_free(sin1);
  stack_free(sin2);
  stack_free(sout);
  free(aux);
  
  return 0;
} 