#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "delivery.h"

/*----------------------------------------------------------------------------------------*/

Status delivery_add(Delivery* d, Product* p){
    if(!d || !p) return ERROR;

    Queue *q = queue_new();
    if (!q) return ERROR;

    q=delivery_getPlan(d);

    queue_push(q,p);




}

Status delivery_run_plan(FILE * pf, Delivery* d){
    if(!pf || !d) return ERROR;





}

