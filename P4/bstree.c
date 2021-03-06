#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "vertex.h"
/* START [_BSTNode] */
typedef struct _BSTNode {
    void * info;
    struct _BSTNode * left;
    struct _BSTNode * right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
    BSTNode * root;
    P_tree_ele_print print_ele;
    P_tree_ele_cmp cmp_ele;
};
/* END [_BSTree] */


/*** BSTNode TAD private functions ***/
BSTNode * _bst_node_new(){
    BSTNode * pn = NULL;

    pn = malloc(sizeof(BSTNode));
    if (!pn) {
        return NULL;
    }

    pn->left = pn->right = NULL;
    pn->info = NULL;
    return pn;
}

void _bst_node_free (BSTNode * pn){
    if (!pn) return;

    free(pn);
}

void _bst_node_free_rec (BSTNode * pn){
    if (!pn) return;

    _bst_node_free_rec(pn->left);
    _bst_node_free_rec(pn->right);
    _bst_node_free(pn);

    return;
}

int _bst_depth_rec (BSTNode * pn) {
    int depthR, depthL;
    if (!pn) return 0;

    depthL = _bst_depth_rec(pn->left);
    depthR = _bst_depth_rec(pn->right);

    if (depthR > depthL) {
        return depthR + 1;
    } else {
        return depthL + 1;
    }
}

int _bst_size_rec(BSTNode * pn) {
    int count = 0;
    if (!pn) return count;

    count += _bst_size_rec(pn->left);
    count += _bst_size_rec(pn->right);

    return count + 1;
}

int _bst_preOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += print_ele(pf, pn->info);
    count += _bst_preOrder_rec(pn->left, pf, print_ele);
    count += _bst_preOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_inOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_inOrder_rec(pn->left, pf, print_ele);
    count += print_ele(pf, pn->info);
    count += _bst_inOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_postOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_postOrder_rec(pn->left, pf, print_ele);
    count += _bst_postOrder_rec(pn->right, pf, print_ele);
    count += print_ele(pf, pn->info);

    return count;
}

BSTNode * _bst_find_max_rec(BSTNode *pn){
    if (!pn->right) return pn;

    return _bst_find_max_rec(pn->right);
}

BSTNode * _bst_find_min_rec(BSTNode *pn){
    if (!pn->left) return pn;

    return _bst_find_min_rec(pn->left);
}

Bool _bst_contains_rec (BSTNode *pn, const void *e, P_tree_ele_cmp cmp_ele){
    if(!pn) return FALSE;

    if(cmp_ele(pn->info,e)==0) return TRUE;

    if(cmp_ele(pn->info,e)>0){
        return _bst_contains_rec (pn->left,e,cmp_ele);
    }
    else
        return _bst_contains_rec (pn->right,e,cmp_ele);
}

BSTNode * _bst_insert_rec (BSTNode *pn, const void *e, P_tree_ele_cmp cmp_ele){

    if(!pn){
        pn=_bst_node_new();
        if (!pn) return NULL;
        pn->info = (void *) e;
        return pn;
    }

    if(cmp_ele(pn->info,e)>0){
        pn->left = _bst_insert_rec (pn->left,e,cmp_ele);
    }

    else if (cmp_ele(pn->info,e)<0){
        pn->right = _bst_insert_rec (pn->right,e,cmp_ele);
    }

    else if (cmp_ele(pn->info,e)==0){
        return pn;
    }

    return pn;
}

BSTNode * _bst_remove_rec (BSTNode *pn, const void *e, P_tree_ele_cmp cmp_ele){

    if(!pn) return NULL;

    if(cmp_ele(pn->info,e)>0)
        pn->left=_bst_remove_rec (pn->left,e,cmp_ele);

    else if(cmp_ele(pn->info,e)<0)
        pn->right=_bst_remove_rec (pn->right,e,cmp_ele);

    else if(cmp_ele(pn->info,e)==0){
        BSTNode *n;
        if(!pn->left && !pn->right){
            _bst_node_free(pn);
            return NULL;
        }
        else if (!pn->left && pn->right !=NULL){
            n=pn->right;
            _bst_node_free(pn);
            return n;
        }
        else if (!pn->right && pn->left !=NULL){
            n=pn->left;
            _bst_node_free(pn);
            return n;
        }
        else if (pn->left !=NULL && pn->right !=NULL) {
            BSTNode *aux_node;
            aux_node = _bst_find_min_rec(pn->right);
            pn->info = aux_node->info;
            pn->right = _bst_remove_rec(pn->right,aux_node->info,cmp_ele);
        }
    }
    return pn;
}

/*** BSTree TAD functions ***/
BSTree * tree_init(P_tree_ele_print print_ele, P_tree_ele_cmp cmp_ele){
    if (!print_ele || !cmp_ele) return NULL;

    BSTree * tree = malloc (sizeof(BSTree));
    if (!tree) {
        return NULL;
    }

    tree->root = NULL;
    tree->print_ele = print_ele;
    tree->cmp_ele = cmp_ele;

    return tree;
}

void tree_destroy (BSTree * tree) {
    if (!tree) return;

    _bst_node_free_rec(tree->root);

    free(tree);
    return;
}

Bool tree_isEmpty( const BSTree * tree){
    if (!tree || !tree->root) return TRUE;
    return FALSE;
}

int tree_depth (const BSTree * tree){
    if (!tree) return -1;

    return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree * tree) {
    if (!tree) return -1;

    return _bst_size_rec(tree->root);
}

int tree_preOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

void * tree_find_min(BSTree * tree){
    if(!tree || tree_isEmpty(tree)==TRUE) return NULL;

    BSTNode *n = _bst_find_min_rec(tree->root);
    if(!n) return NULL;

    return n->info;
}

void * tree_find_max (BSTree * tree){
    if(!tree || tree_isEmpty(tree)==TRUE) return NULL;
    
    BSTNode *n = _bst_find_max_rec(tree->root);
    if(!n) return NULL;

    return n->info;
}

Bool tree_contains (BSTree * tree, const void * elem){
    if (!tree || !elem) return FALSE;

    return _bst_contains_rec (tree->root,elem,tree->cmp_ele);
}

Status tree_insert (BSTree * tree, const void * elem){

    BSTNode *n;
    if(!tree || !elem) return ERROR;

    n= _bst_insert_rec(tree->root,elem,tree->cmp_ele);
    if(!n)return ERROR;
    tree->root=n;

    return OK;
}

Status tree_remove (BSTree * tree, const void * elem){
    BSTNode *n;
    if(!tree || !elem) return ERROR;

    if(tree_isEmpty(tree)==TRUE) return ERROR;

    n=_bst_remove_rec(tree->root,elem,tree->cmp_ele);

    tree->root=n;

    return OK;
}



/**** TODO: find_min, find_max, insert, contains, remove ****/