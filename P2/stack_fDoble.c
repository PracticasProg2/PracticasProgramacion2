#define INIT_CAPACITY 2 //init stack capacity
#define FCT_CAPACITY 2 //multiply the stack capacity

#include "stack_fDoble.h"
#include <stdlib.h>


struct _Stack{
	void **item;/*!<Static array of elements*/
	int top;/*!<index of the top element in the stack*/
	int capacity;/*!<xcapacity of the stack*/
};



Stack *stack_init () {

    Stack *s = NULL;
    int i;

    s = (Stack *) malloc (sizeof(Stack));
    if (s == NULL)
        return NULL;
    
    s->item = (void **) malloc (INIT_CAPACITY * sizeof(void*));

    if (s->item == NULL) 
        return NULL;
    
    for (i=0;i<INIT_CAPACITY;i++)
      s->item[i]=NULL;
    
    s->top = -1;
    s->capacity = INIT_CAPACITY;
    
    return s;
}

void stack_free (Stack *s){
  if(!s) return ;
  free(s->item);
  free(s);
}

Status stack_push (Stack *s,const void *ele){
  if(!s || !ele) return ERROR;
  
  if(stack_isFull(s)==TRUE){
    s->capacity=s->capacity*FCT_CAPACITY;
    s->item=(void**)realloc(s->item,(s->capacity)*sizeof(void*));
    s->top++;
    s->item[s->top]=(void*)ele;
    return OK;
  }
  else{
    s->top++;
    s->item[s->top]=(void*)ele;
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
  
  return s->top+1;
}

int stack_print(FILE* fp, const Stack *s, P_stack_ele_print f){
  if(!fp || !s || !f) return -1;

  int a, n=0, i;
  a=stack_size(s);

  n+=fprintf(fp,"SIZE: %d\n",a);

  for(i=a-1;i>=0;i--){
   n+=f(fp,s->item[i]);
   fprintf(fp,"\n");
  }

return n;
}
