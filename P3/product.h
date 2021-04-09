/**
 * @file  product.h
 * @author Profesores Programación 2
 * @date 2 April 2021
 * @version 1.0
 * @brief Library to manage ADT Product
 *
 * @details 
 * 
 * @see
 */
#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include "vertex.h"
#include "types.h"

/** 
 * @brief Data structure to implement the ADT Product. 
 *
 **/
/* START [Product] */
typedef struct _Product Product;
/* END [Product] */


/**
 * @brief Constructor. Initializes a product with a vertex. It stores the reference of that vertex.
 * 
 * @return Return the initialized product if it was done correctly, 
 * otherwise return NULL.
*/
Product * product_init (Vertex* v);


/**
 * @brief Destructor. Frees the dynamic memory reserved for a product, including the vertex.
 *
 * @param p Product to free
 */
void product_free (void * p);


/**
 * @brief  Gets the number of products.
 *
 * @param p Product pointer
 *
 * @return  Returns the amount of products of the given product, or -1 in case of error.
 */
int product_getAmount (const Product * p);


/**
 * @brief Gets the vertex of a product.
 *
 * @param p Product pointer
 *
 * @return Returns a pointer to the vertex in the product, or NULL in 
 * case of error.
 */
const Vertex* product_getVertex (const Product * p);


/**
 * @brief Modifies the number of products of a given product.
 *
 * @param p Product pointer
 * @param n New amount, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status product_setAmount (Product * p, const int amount);


/**
 * @brief Compares two products.
 *
 * @param p1,p2 Products to compare.
 *
 * @return It returns an integer less than, equal, or greater than zero
 * if p1 is considered smaller, equal, or larger than p2.
 */
int product_cmp (const void * p1, const void * p2);


/**
 * @brief Allocates memory for a product where it copies the data from
 * the product in src.
 * 
 * @param src Original product pointer
 *
 * @return Returns the pointer of the copied product if everything 
 * went well, or NULL otherwise.
 */
void * product_copy (const void * src);


/** 
 * @brief Prints in pf the data of a product.
 * 
 * @param pf File descriptor
 * @param p Product to be printed
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int product_print (FILE * pf, const void * p);

#endif