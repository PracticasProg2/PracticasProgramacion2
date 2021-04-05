#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_utils.h"
#include "stack_fDoble.h"

int main (){

    Stack *s =stack_init();
    int *e=NULL,i;

    e=(int*) malloc(5*sizeof(int));

    for(i=0;i<5;i++){
        e=&i;
        stack_push(s,e);
    }
    

    stack_free(s);
    free(e);
    return 0;
}