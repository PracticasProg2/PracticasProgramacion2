/**
 * @file p1_e2.c
 * @author Alberto Vicente y Pablo Villegas
 * @date Created on March 04, 2021
 * @version 1.0
 * @brief Library to manage the Graph ADT
 */
 
#include "graph.h"

#include <stdlib.h>
#include <string.h>

int main () {

  Graph *g = graph_init();

  long id1=111, id2=222;

  char tag1[128]= "Madrid", tag2[128]= "Toledo";

  int i;

  /*FILE *f;*/
  
  printf("Inserting %s... result...: %d\n", tag1, graph_newVertex(g, "id:111 tag:Madrid state:1" ));

  printf("Inserting %s... result...: %d\n", tag2, graph_newVertex(g, "id:222 tag:Toledo state:1" ));
  
  graph_newEdge(g,id2,id1);
  
  printf("Inserting edge: %ld --> %ld\n",id2,id1);
  
  printf("%ld --> %ld?", id1, id2);
    if(graph_connectionExists(g, id1, id2))printf("Yes\n");
    else printf("No\n");
    printf("%ld --> %ld?", id2, id1);
    if(graph_connectionExists(g, id2, id1))printf("Yes\n");
    else printf("No\n");
    
  printf("Number of connections from %ld: %i\n", id1, graph_getNumberOfConnectionsFromId(g, id1));
  printf("Number of connections from %s: %i\n", tag2, graph_getNumberOfConnectionsFromTag(g, tag2));
    
  printf("Connections from %s:", tag2);
    for(i=0;i<graph_getNumberOfConnectionsFromTag(g, tag2);i++){
      printf(" %ln\n", graph_getConnectionsFromTag(g, tag2));
    }
  graph_print(stdout,g);
  graph_free(g);

  return 0;
}
