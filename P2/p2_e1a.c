#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_utils.h"
#include "stack_fDoble.h"

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout){
  if (!sin1 || !sin2 || !sout) return ERROR;
  float *nota=NULL;
  Stack *aux;
  
  while (stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
    if(float_cmp(stack_top(sin1),stack_top(sin2))>0)
      nota=stack_pop(sin1);
    else
      nota=stack_pop(sin2);
    stack_push(sout,nota);
  }
  
  if(stack_isEmpty(sin1)==TRUE)
    aux=sin2;
  else
    aux=sin1;
  
  while (stack_isEmpty(aux)==FALSE){
    nota=stack_pop(aux);
    stack_push(sout,nota);
  }
  
  
  return OK;
}

/*----------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]){
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
  int i, size1, size2;
  float *e=NULL, *h=NULL;
  FILE *f2;
  FILE *f1;
  
  if(argc!=3){
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    return -1;
  }
  
  f1=fopen(argv[1], "r");
  if(!f1){
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    return -1;
  }
  
  fscanf(f1, "%d", &size1);
  
  f2=fopen(argv[2], "r");
  if(!f2){
    fclose(f1);
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    return -1;
  }
  
  fscanf(f2, "%d", &size2);
  
  e = (float*) malloc ((size1)*sizeof(float));
  if(!e){
    fclose(f1);
    fclose(f2);
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    return -1;
  }
  
  h = (float*) malloc ((size2)*sizeof(float));
  if(!h){
    fclose(f1);
    fclose(f2);
    free(e);
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);
    return -1;
  }
  
  
  for(i=0; i<size1; i++){
     fscanf(f1, "%f", &e[i]);
     stack_push(sin1,&e[i]);
  }
  
  for(i=0; i<size2; i++){
    fscanf(f2, "%f", &h[i]);
    stack_push(sin2,&h[i]);
  }
  
  stack_print(stdout, sin1, float_print);
  stack_print(stdout, sin2, float_print);
  mergeStacks(sin1,sin2,sout);
  stack_print(stdout, sout, float_print);
  
  fclose(f1);
  fclose(f2);
  
  free(e);
  free(h);
  stack_free(sin1);
  stack_free(sin2);
  stack_free(sout);
  
  return 0;
}
