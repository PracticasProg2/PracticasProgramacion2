/**
 * @file graph.c
 * @author Alberto Vicente y Pablo Villegas
 * @date Created on March 04, 2021
 * @version 1.0
 * @brief Library to manage the Graph ADT
 */

#include "graph.h"
#include "stack_fDoble.h"

#include <stdlib.h>
#include <string.h>

#define MAX_VTX 4096
#define LINES 1000
#define MAX_DESC 64

struct _Graph{
  Vertex *vertices[MAX_VTX];	/*!<Array with the graph vertices*/
  Bool connections[MAX_VTX][MAX_VTX];	/*!<Adjacency matrix*/
  int num_vertices;		/*!<Total number of vertices*/
  int num_edges;		/*!<Total number of edges*/  
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

int _graph_findVertexById (const Graph *g, long id);
int _graph_findVertexByTag (const Graph *g, char *tag);
Bool graph_isFull(Graph *g);
Bool graph_containsFromTag(const Graph *g, char *tag);
Bool graph_containsFromIx(const Graph *g, int ix);
int _graph_getNumConnections(const Graph *g, int ix);
int *_graph_getConnectionsIndex(const Graph *g, int ix);

int _graph_findVertexById (const Graph *g, long id){
  int i;
  if (!g || !id) return -1;
  
  for (i=0;i<g->num_vertices;i++){
    if (id==vertex_getId (g->vertices[i]))
      break;
  }
  return i;
}

int _graph_findVertexByTag (const Graph *g, char *tag){
  int i;
  if (!g || !tag) return -1;
  
  for (i=0;i<g->num_vertices;i++){
    if (strcmp(tag,vertex_getTag (g->vertices[i]))==0)
      break;
  }
  return i;
}

Bool graph_isFull(Graph *g){
  if(!g) return FALSE;
  if (g->num_vertices==MAX_VTX) return TRUE;
  return FALSE;
}

Bool graph_containsFromTag(const Graph *g, char *tag){
  if(!g||!tag) return FALSE;
  if(strlen(tag)==0) return FALSE;
  int i;
  for (i=0;i<g->num_vertices;i++){
    if (tag==vertex_getTag(g->vertices[i]))
      return TRUE;
  }
  return FALSE;
}

Bool graph_containsFromIx(const Graph *g, int ix){
  if(!g||!ix) return FALSE;
  if(ix<0) return FALSE;
  int i;
  for (i=0;i<g->num_vertices;i++){
    if (ix==i)
      return TRUE;
  }
  return FALSE;
}

int _graph_getNumConnections(const Graph *g, int ix){
  if(!g || !ix) return -1;
  if(graph_containsFromIx(g,ix)==FALSE) return -1;
  int i, n;
  
  for (i=n=0;i<g->num_vertices;i++){
    if (g->connections[ix][i]==TRUE)
      n++;
  }
 return n;
}

int *_graph_getConnectionsIndex(const Graph *g, int ix){

  if(!g || !ix) return NULL;
  int i,j,n;
  n=_graph_getNumConnections(g,ix);
  int *vertices=(int*)malloc(n*sizeof(int));
  if (vertices==NULL) return NULL;
  
  for (i=j=0;i<g->num_vertices;i++){
    if (g->connections[ix][i]==TRUE){
      vertices[j]=i;
      j++;
    }
  }

  return vertices;
  
  
}

/*----------------------------------------------------------------------------------------*/


Graph * graph_init(){
  int i,j;
  Graph * g;
  g=(Graph*) malloc(sizeof(Graph));

  if (g == NULL) return NULL;

  g->num_edges=0;
  g->num_vertices=0;
  for(i=0;i<MAX_VTX;i++){
    g->vertices[i]=NULL;
    for(j=0;j<MAX_VTX;j++){
      g->connections[i][j]=FALSE;
    }
  }    

  return g;
}

void graph_free(Graph *g){
  if (!g) return;
  int i;
  for(i=0;i<g->num_vertices;i++){
    vertex_free(g->vertices[i]);
  }
  free(g);
}

Status graph_newVertex(Graph *g, char *desc){
  if (!g || !desc) return ERROR;
  if (graph_isFull(g)==TRUE) return ERROR;
  int i,id;
  Vertex *v;
  v=vertex_initFromString(desc);
  id=vertex_getId(v);
  for(i=0;i<g->num_vertices;i++){
    if(vertex_getId(g->vertices[i])==id){
      vertex_free(v);
      return OK;
    }
  }
  g->vertices[g->num_vertices]=v;
  vertex_setIndex(g->vertices[g->num_vertices],g->num_vertices);
  g->num_vertices++;
  return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest){
  if(!g || !orig || !dest) return ERROR;
  int i,j;
  
  if (graph_contains(g,orig)==FALSE) return ERROR;
  if (graph_contains(g,dest)==FALSE) return ERROR;
  
  i = _graph_findVertexById (g,orig);
  j = _graph_findVertexById (g,dest);
  
   g->connections[i][j]=TRUE;
   g->num_edges++;
   return OK;
}

Bool graph_contains(const Graph *g, long id){
  if(!g || !id) return FALSE;
  int i;
  for(i=0;i<g->num_vertices;i++){
    if(id==vertex_getId(g->vertices[i]))
      return TRUE;
  }
  return FALSE;
}

int graph_getNumberOfVertices(const Graph *g){
  if(!g) return -1;

  return g->num_vertices;


}

int graph_getNumberOfEdges(const Graph *g){
  if(!g) return -1;

  return g->num_edges;


}

Bool graph_connectionExists(const Graph *g, long orig, long dest){
  if(!g || !orig || !dest) return FALSE;
  int i, j;
  
  i = _graph_findVertexById (g,orig);
  j = _graph_findVertexById (g,dest);
  
  if(g->connections[i][j]==TRUE)
    return TRUE;
  return FALSE;
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
  if(!g || !id) return -1;
  if(graph_contains(g,id)==FALSE) return -1;
  int i, j, n;
  i=_graph_findVertexById (g,id);
  
  for (j=n=0;j<g->num_vertices;j++){
    if (g->connections[i][j]==TRUE)
      n++;
  }
 return n;
}

long *graph_getConnectionsFromId(const Graph *g, long id){
  if(!g || !id) return NULL;
  int i,j,n;
  n=graph_getNumberOfConnectionsFromId(g,id);
  long *vertices=(long*)malloc(n*sizeof(long));
  if (vertices==NULL) return NULL;
  for(i=0;i<g->num_vertices;i++){
    for(j=0;j<g->num_vertices;j++){
       if(graph_connectionExists(g,id,vertex_getId(g->vertices[i])==TRUE)){
         vertices[j]=vertex_getId(g->vertices[i]);
       } 
       else{
         j--;
       } 
    }
  }  

  return vertices;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
  if (!g || !tag) return -1;
  if (graph_containsFromTag(g,tag)==FALSE) return -1;
  int i, j, n;
  i=_graph_findVertexByTag (g,tag);
  
  for (j=n=0;j<g->num_vertices;j++){
    if (g->connections[i][j]==TRUE)
      n++;
  }
 return n;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag){
  if (!g || !tag) return NULL;
  int i,k,l,n;
  n=graph_getNumberOfConnectionsFromTag(g,tag);
  long *vertices=(long*)malloc(n*sizeof(long));
  if (vertices==NULL) return NULL;
  
  for(i=0;i<g->num_vertices;i++){
    if (strcmp(tag,vertex_getTag(g->vertices[i]))==0){
      l=i;
      break;
    }
  }
  
  for(i=k=0;i<g->num_vertices;i++){
    if(g->connections[l][i]==TRUE){
      vertices[k]=vertex_getId(g->vertices[i]);
      k++;
    }
  }
  
  return vertices;
}

int graph_print (FILE *pf, const Graph *g){
  if (!pf || !g) return -1;
  int i,j,n;
  long id1, id2;
  
  for(i=n=0;i<g->num_vertices;i++){
    n+=vertex_print(pf,g->vertices[i]);
    printf(": ");
    id1=vertex_getId(g->vertices[i]);
    for(j=0;j<g->num_vertices;j++){
      id2=vertex_getId(g->vertices[j]);
      if(graph_connectionExists(g,id1,id2)==TRUE){
        n+=vertex_print(pf,g->vertices[j]);
        printf(" ");
      }
    }  
    n+=fprintf(pf,"\n");
  }
  return n;
}

Status graph_readFromFile (FILE *fin, Graph *g){
  if (!fin || !g) return ERROR;
  
  long v1, v2;
  int i, j;
  char desc[MAX_DESC];
  fscanf(fin,"%d\n",&i);
  
  for(j=0;j<i;j++){
    fgets(desc,MAX_DESC,fin);
    graph_newVertex(g,desc);
  }
  
  while(fscanf(fin,"%ld %ld",&v1,&v2)==2){
    graph_newEdge(g,v1,v2);
  }

  return OK;
}

Status graph_depthSearch(Graph *g, long from_id, long to_id){

  if (!g || !from_id || !to_id) return ERROR;

  int i;

  Vertex *v;
  Stack *s=stack_init();
  if (!s) return ERROR;

  for (i=0;i<g->num_vertices;i++)
    vertex_setState(g->vertices[i],WHITE);
  
  vertex_setState(g->vertices[_graph_findVertexById(g,from_id)],BLACK);
  
  stack_push(s,g->vertices[_graph_findVertexById(g,from_id)]);
  
  while (stack_isEmpty(s)==FALSE){
    v=stack_pop(s);
    vertex_print(stdout,v);
    printf("\n");
    if (vertex_getId(v)==to_id){
      stack_free(s);
      return OK;
    }
    else if (graph_getNumberOfConnectionsFromId(g,vertex_getId(v))==0){
      printf("Error in graph search algorithm.\n");
      stack_free(s);
      return ERROR;
    }
    else{
      for(i=0;i<g->num_vertices;i++){
        if(g->connections[vertex_getIndex(v)][i]==TRUE){
          if(vertex_getState(g->vertices[i])==WHITE) {
            vertex_setState(g->vertices[i],BLACK);
            stack_push(s,g->vertices[i]);
          }
        }
      }
    }
  }
  
  stack_free(s);
  
  return OK;
}
