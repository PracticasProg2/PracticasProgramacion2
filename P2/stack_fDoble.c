#define INIT_CAPACITY 2 //init stack capacity
#define FCT_CAPACITY 2 //multiply the stack capacity

#include "stack_fDoble.h"
#include <stdlib.h>


struct _Stack{
	void **item;/*!<Static array of elements*/
	int top;/*!<index of the top element in the stack*/
	int capacity;/*!<xcapacity of the stack*/
};




Stack * stack_init (){

  Stack *s=NULL;
  int i;
  
  s=(Stack*)malloc((INIT_CAPACITY)*sizeof(Stack));
  if(s==NULL) return NULL;
  
  s->capacity=INIT_CAPACITY;
  for(i=0;i<s->capacity;i++){
    s->item[i]=NULL;
  }
  
  s->top=-1;  
  
  return s;
}

void stack_free (Stack *s){
  if(!s) return ;
  
  free(s);
}

Status stack_push (Stack *s, void *ele){
  if(!s || !ele) return ERROR;
  
  if(stack_isFull(s)==TRUE){
    s->capacity=s->capacity*FCT_CAPACITY;
    s=(Stack*)realloc(s,(s->capacity)*sizeof(Stack));
    s->top++;
    s->item[s->top]=ele;
    return OK;
  }
  else{
    s->top++;
    s->item[s->top]=ele;
    return OK;
  }  
}

void * stack_pop (Stack *s){
  if(!s) return NULL;
  if(stack_isEmpty(s)==TRUE) return NULL;
  void *e;
  
  e=s->item[s->top];
  s->item[s->top]=NULL;
  s->top --;
  return e;
}

void * stack_top (const Stack *s){
  if(!s) return NULL;
  if(stack_isEmpty(s)==TRUE) return NULL;
  
  return s->item[s->top];
}

Bool stack_isEmpty (const Stack *s){
  if(!s) return FALSE;
  
  if(s->top==-1) return TRUE;
  
  return FALSE;
}

Bool stack_isFull (const Stack *s){
  if(!s) return FALSE;
  
  if(s->top==s->capacity-1) return TRUE;
  
  return FALSE;
}

size_t stack_size (const Stack *s){
  if(!s) return -1;
  
  return s->top;
}

int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f){
  if(!fp || !s || !f) return -1;

  int a, n=0, i;
  a=stack_size(s);

  n+=fprintf(fp,"SIZE: %d\n",a);

  for(i=a-1;i>=0;i--){
   n+=fprintf(fp,s->item[i],f);
  }

return n;
}