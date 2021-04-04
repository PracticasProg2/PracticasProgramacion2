#include<stdio.h>
#include<stdlib.h>
#include "vertex.h"

int main(){
  Vertex *v1 = NULL, *v2 = NULL;
  v1=vertex_init();
  if(v1 == NULL)
    return -1;

  v2=vertex_init();
  if(v2 == NULL)
    return -1;

  if(vertex_setId(v1, 10) == ERROR)
    return -1;

  if(vertex_setTag(v1, "one") == ERROR)
    return -1;

  if(vertex_setState(v1, WHITE) == ERROR)
    return -1;

  if(vertex_setId(v2, 20) == ERROR)
    return -1;

  if(vertex_setTag(v2, "two") == ERROR)
    return -1;

  if(vertex_setState(v2, BLACK) == ERROR)
    return -1;

  if(vertex_print(stdout, v1) == -1)
    return -1;

  if(vertex_print(stdout, v2) == -1)
    return -1;

  fprintf(stdout, "\n");

  fprintf(stdout, "Equals? ");
  if(vertex_cmp(v1,v2) == 0){
    fprintf(stdout, "Yes");
  }
  else
    fprintf(stdout, "No");

  fprintf(stdout, "\n");

  fprintf(stdout, "Vertex 2 tag: %s\n",vertex_getTag(v2));

  vertex_free(v2);
  v2=vertex_copy(v1);
 
  fprintf(stdout, "Vertex 3 id: %ld\n",vertex_getId(v2));

  if(vertex_print(stdout, v1) == -1)
    return -1;

  if(vertex_print(stdout, v2) == -1)
    return -1;
    
  fprintf(stdout, "\n");
  
  fprintf(stdout, "Equals? ");

  if(vertex_cmp(v1,v2) == 0){
    fprintf(stdout, "Yes\n");
  }
  else
    fprintf(stdout, "No\n");

  vertex_free(v1);
  vertex_free(v2);
return 0;
}

