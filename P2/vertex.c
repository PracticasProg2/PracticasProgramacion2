#include "vertex.h"
#include <string.h>

#define TAG_LENGTH 64
struct _Vertex {
  long id;
  char tag[TAG_LENGTH];
  Label state;
  int index;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/

Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

Vertex * vertex_init (){
  Vertex *v;
  v=(Vertex*)malloc(sizeof(Vertex));
  if(v==NULL){
    return NULL;
  }
  
  v->id=0;
  v->tag[0] = '\0';
  v->state=WHITE;
  v->index=0;
  return v;
}

void vertex_free(void *v){
  free(v);
}

long vertex_getId (const Vertex * v){
  if(v==NULL)
    return -1;
  return v->id;
}

const char* vertex_getTag (const Vertex * v){
  if(v==NULL)
    return NULL;
  return v->tag;
}

Label vertex_getState (const Vertex * v){
  if(v==NULL)
    return ERROR_VERTEX;
  return v->state;
}

int vertex_getIndex(const Vertex *v){
  if (!v) return -1;
  return v->index;
}

Status vertex_setId (Vertex * v, const long id){
  if(v==NULL || id < 0)
    return ERROR;

  v->id=id;
  return OK;
}

Status vertex_setTag (Vertex * v, const char * tag){
  if(!v || strlen(tag)>65 || !tag)
    return ERROR;

  strcpy(v->tag,tag);
  return OK;
}

Status vertex_setState (Vertex * v, const Label state){
  if(v==NULL)
    return ERROR;
  v->state=state;
  return OK;
}

Status vertex_setIndex(Vertex *v, const int index){
  if(!v || !index) return ERROR;
  v->index=index;
  return OK;
}

int vertex_cmp (const void * v1, const void * v2){
  if(v1 == NULL || v2 == NULL)
    return ERROR;
  if(vertex_getId(v1)==vertex_getId(v2))
    return strcmp(vertex_getTag(v1),vertex_getTag(v2));
  else if(vertex_getId(v1) < vertex_getId(v2))
    return -1;
  return 1;
}

void * vertex_copy (const void * src){
  Vertex *new = NULL;
  if(src == NULL)
    return ERROR;

  new=vertex_init();
  if(!new)
    return NULL;
  
  vertex_setId(new,vertex_getId(src));
  vertex_setTag(new,vertex_getTag(src));
  
  return new;
}

int vertex_print (FILE * pf, const void * v){
  int i=0;
  if(!pf || !v)
    return -1;
    
  i+=fprintf(pf, "[%ld, %s, %d, %d]", vertex_getId(v), vertex_getTag(v), vertex_getState(v), vertex_getIndex(v));
  
  return i;
}

