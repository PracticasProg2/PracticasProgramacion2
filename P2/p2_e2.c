#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_utils.h"
#include "stack_fDoble.h"
#include "graph.h"


int main (int argc, char *argv[]){

  if (argc != 4) return -1;
  FILE *f;
  Graph *g;
  long id1, id2;
  
  id1=atol(argv[2]);
  id2=atol(argv[3]);
  
  f=fopen(argv[1],"r");
  if(!f) return -1;
  
  g=graph_init();
  if(!g){
    fclose(f);
    return -1;
  }
  graph_readFromFile(f,g);
  graph_print(stdout,g);
  
  graph_depthSearch(g,id1,id2);
  printf("\n\n\n\n\n\n\n\n\n");
  graph_print(stdout,g);
  
  fclose(f);
  graph_free(g);
  return 0;
}






