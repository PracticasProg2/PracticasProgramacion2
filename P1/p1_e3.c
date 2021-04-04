/**
 * @file p1_e3.c
 * @author Alberto Vicente y Pablo Villegas
 * @date Created on March 09, 2021
 * @version 1.0
 * @brief Library to manage the Graph ADT
 */
 
#include "graph.h"

#include <stdlib.h>
#include <string.h>

int main (int argc,char *argv){

  if (!argc) return -1;
  int i;
  for(i=0;i<argc;i++)
    if(argv[i]==NULL) return -1;
  
  FILE *f;
  Graph *g=graph_init();
  
  
  
  f=fopen(argv[1],"r");
  
  graph_readFromFile (f,g);

  graph_print(stdout,g);
  
  fclose(f);

  return 0;
}
