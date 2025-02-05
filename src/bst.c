/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>



void* upo_bst_getIMPL(upo_bst_node_t *node, void *key, upo_bst_comparator_t key_cmp);
void* putImpl(upo_bst_node_t* node, void* key, void* newValue, void* Vold, upo_bst_comparator_t key_cmp);
upo_bst_node_t* upo_bst_insertImpl(upo_bst_node_t* node, void *key, void *value, upo_bst_comparator_t key_cmp);
upo_bst_node_t* upo_bst_deleteImpl(upo_bst_node_t* node, const void *key, upo_bst_comparator_t key_cmp, int destroy_data);
upo_bst_node_t* upo_bst_deleteImpl1(upo_bst_node_t* node, int destroy_data);
upo_bst_node_t* upo_bst_deleteImpl2(upo_bst_node_t* node, int destroy_data);
size_t upo_bst_sizeImpl(upo_bst_node_t* node);
size_t upo_bst_heightImpl(upo_bst_node_t* node);
int isLeafImpl(upo_bst_node_t* node);


upo_bst_node_t* upo_bst_minImpl(upo_bst_node_t* node);
upo_bst_node_t* upo_bst_maxImpl(upo_bst_node_t* node);
void* upo_bst_floorImpl(upo_bst_node_t* node, void* key, upo_bst_comparator_t key_cmp);
void* upo_bst_ceilingImpl(upo_bst_node_t* node, void* key, upo_bst_comparator_t key_cmp);
//void aggiorna_list(void* nodeKey, const void* low_key, const void* high_key, upo_bst_key_list_t* list, upo_bst_comparator_t key_cmp);
//void insertToList(upo_bst_key_list_t *list, upo_bst_key_list_node_t* listNode);
//void upo_bst_keysImpl(upo_bst_node_t* node, upo_bst_key_list_t list);
//void upo_bst_keysImpl(upo_bst_node_t* node, upo_bst_key_list_t list);
//void upo_bst_keys_range_impl(const upo_bst_node_t *node, const void *low_key, const void *high_key, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list);
//int upo_bst_is_bstImpl(upo_bst_node_t* node, const void* min_key, const void* max_key, upo_bst_comparator_t key_cmp);
/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp){
   
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}


upo_bst_node_t* upo_bst_node_create(void *key, void *value){
        if(key == NULL || value == NULL){
           perror("Unable to create a node: keyOvalueNULL");
           abort(); 
        }
        upo_bst_node_t* corrent = malloc(sizeof(upo_bst_node_t));

        if(corrent == NULL){
          perror("Unable to create a node; mallocCorrentNULL");
          abort();
        }

        corrent->key = key;
        corrent->value = value;
        corrent->left = NULL;
        corrent->right = NULL;

        return corrent;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data){
    
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data){
    
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data){
    
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}



/************************ funzionamento_PUT ***********************************************************************/
//put(t,k,v)
//inserisce/sostituisce il valore v identificato da k in t e restituisce il valore precedente se presente
void* upo_bst_put(upo_bst_t tree, void *key, void *value){

    
    if(tree == NULL || key == NULL || value == NULL){
      fprintf(stderr, "parametri nulli in ingresso\n");
      return NULL;
    }
    
    void* Vold = NULL;

    tree->root = putImpl(tree->root, key, value, Vold, tree->key_cmp);
    return Vold;
}


void* putImpl(upo_bst_node_t* node, void* key, void* newValue, void* Vold, upo_bst_comparator_t key_cmp){
    
    //Vold = NULL;
       if (node == NULL){
        upo_bst_node_t* tmp = upo_bst_node_create(key, newValue);
       // printf("Inserito nuovo nodo con chiave: %d, valore: %d\n", *(int*)key, *(int*)newValue);
        return tmp;
       }
       if( key_cmp(key, node->key) > 0){
          node->right = putImpl(node->right, key, newValue, Vold, key_cmp);
        }else if(key_cmp(key, node->key) < 0){
          node->left = putImpl(node->left, key, newValue, Vold, key_cmp); 
         } else{
        Vold = node->value;
        node->value = newValue;
        //printf("Valore aggiornato per la chiave: %d, nuovo valore: %d\n", *(int*)key, *(int*)newValue);
        //return Vold;
       }
       return node;
}
/****************************************** funzionamento_INSERT **************************************************/
//insert(t,k,v)
//inserisce il valore v identificato da k in t solo se 
//non è un duplicato; Aiuto: l'insert si fa sempre in foglia. 
void upo_bst_insert(upo_bst_t tree, void *key, void *value){
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation.
     */
   if(tree == NULL) {
       return;  
    }
    tree->root = upo_bst_insertImpl(tree->root, key, value, tree->key_cmp);
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


upo_bst_node_t* upo_bst_insertImpl(upo_bst_node_t* node, void *key, void *value, upo_bst_comparator_t key_cmp){

   if (node == NULL) {
      return upo_bst_node_create(key, value);
    }

    int cmp_result = key_cmp(key, node->key);

    if (cmp_result > 0) {
       node->right =  upo_bst_insertImpl(node->right, key, value, key_cmp);
    } else if (cmp_result < 0) {
       node ->left = upo_bst_insertImpl(node->left, key, value, key_cmp);
    }
    return node;  
}
  
/**************************** funzionamento_GET *****************************************************/
//get(t,k)
//restituisce il valore v identificato da k in t
void* upo_bst_get(const upo_bst_t tree, const void *key){

    if(tree == NULL || key == NULL){
      return NULL;
    }
    return upo_bst_getIMPL(tree->root, key, tree->key_cmp);    
   
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}

void* upo_bst_getIMPL(upo_bst_node_t *node, void* key, upo_bst_comparator_t key_cmp){

    if(node == NULL){
     return NULL;
    }

    int cmp_result = key_cmp(node->key, key);
    //printf("key_cmp: %d\n", cmp_result);

    if( cmp_result > 0){
    return  upo_bst_getIMPL(node->left, key, key_cmp);
    }else if(cmp_result < 0){
    return upo_bst_getIMPL(node->right, key, key_cmp);
    } 
    /*
    if(node->value != NULL){
      return node->value;    
    }
    */
    else{
     // printf("Chiave trovata! Valore: %d\n", *((int*) node->value));
      return node->value;    
    }
    
}

/********************************* CONTAINS **************************************************/
//contains(t,k)
//indica se esiste un valore identificato da k in t
int upo_bst_contains(const upo_bst_t tree, const void *key){
    if(tree == NULL || key == NULL){
       return 0;
    }
    void* result = upo_bst_getIMPL(tree->root, key, tree->key_cmp);
    //printf("Risultato ricerca per chiave %d: %p\n", *((int*)key), result);
    if(result != NULL) {
        return 1;//contenuta.
    }else{
        return 0;
    }
    
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}
/*************************************** fuzionamento_Delete **************************************************/
//delete(t,k,d)
//rimuove la coppia chiave-valore identificata da k in t
void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data){

    if(tree->root == NULL || tree == NULL){
      return;
    }
    tree->root = upo_bst_deleteImpl(tree->root, key, tree->key_cmp, destroy_data);
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


upo_bst_node_t* upo_bst_deleteImpl(upo_bst_node_t* node, const void *key, upo_bst_comparator_t key_cmp, int destroy_data){
      
      if(node == NULL){
        return NULL;
      }
      if(key_cmp(key, node->key) <0){
       node->left = upo_bst_deleteImpl(node->left, key, key_cmp, destroy_data);
      }else if(key_cmp(key, node->key) >0){
        node->right = upo_bst_deleteImpl(node->right, key, key_cmp, destroy_data);  
      }else if(node->left != NULL && node->right != NULL){
        node = upo_bst_deleteImpl2(node, destroy_data);
      }else{
        node = upo_bst_deleteImpl1(node, destroy_data); 
      }
      return node;
}


upo_bst_node_t* upo_bst_deleteImpl1(upo_bst_node_t* node, int destroy_data){
   
   upo_bst_node_t* tmp = node;

   if(node->left != NULL){
      node = node->left;
   }else{
    node = node->right;
   }

   if(destroy_data == 1){
      free(tmp-> value);
   }
   free(tmp);
   return node;
}



upo_bst_node_t* upo_bst_deleteImpl2(upo_bst_node_t* node, int destroy_data){
     
    upo_bst_node_t* tmp = upo_bst_minImpl(node->right);
    
    node->key = tmp->key;
    node->value = tmp->value;
    node-> right = upo_bst_deleteImpl1(tmp, destroy_data);
    return node;
}

/*************************** SIZE *************************************/
//size(t)
//restituisce il numero di nodi in t
size_t upo_bst_size(const upo_bst_t tree){

    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if(tree == NULL){
       return 0;
    }
    return upo_bst_sizeImpl(tree->root);

    //fprintf(stderr, "To be implemented!\n");
    //abort();
}

size_t upo_bst_sizeImpl(upo_bst_node_t* node){
    if(node == NULL){
       return 0;
    }
    return 1 + upo_bst_sizeImpl(node->left) + upo_bst_sizeImpl(node->right);
}


/*************************** HEIGHT *************************************/
//height(t)
//restituisce l'altezza di t
size_t upo_bst_height(const upo_bst_t tree){

    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
     
     return upo_bst_heightImpl(tree->root);

    //fprintf(stderr, "To be implemented!\n");
    //abort();
}

int isLeafImpl(upo_bst_node_t* node){

    if(node->left == NULL && node->right == NULL){
         return 1;
    }
    return 0;
}

void* max(void* a, void* b){
  if(a<b){
    return b;
  }
  return a;
}

size_t upo_bst_heightImpl(upo_bst_node_t* node){
     
     if(node == NULL || isLeafImpl(node)){
        return 0;
     }
     return 1 + max(upo_bst_heightImpl(node->left), upo_bst_heightImpl(node->right));
}

/************************* funzionamento_TRAVERSE *******************************************************/
//traverse_in_order(t,f) 
//attraversa l'albero t in ordine (depth-first), 
//visitando ogni nodo con la funzione f
void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context){
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    
    if(tree == NULL || tree->root == NULL){return;}
    upo_bst_traverse_in_orderImpl(tree->root, visit, visit_context);

    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


void upo_bst_traverse_in_orderImpl(upo_bst_node_t* node, upo_bst_visitor_t visit, void* visit_context){
      
    if(node == NULL){
        return;
     }
     upo_bst_traverse_in_orderImpl(node->left, visit, visit_context);
     visit(node->key, node->value, visit_context);
     upo_bst_traverse_in_orderImpl(node->right, visit, visit_context);
} 

/************************ EMPTY **********************************************/
// is_empty(t): indica se t è un albero vuoto o meno
//Restituisce True se l'albero è vuoto, altrimenti False
int upo_bst_is_empty(const upo_bst_t tree){
    if(tree == NULL){
       return 1;
    }

    if(tree->root != NULL && tree->key_cmp != NULL){
        return 0;
    } else if(tree->root== NULL && tree->key_cmp != NULL){
        return 1;
    }else{
        return 1;
    }   

    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

/******************************* funzionamento_MIN *****************************************/
//min(t)
//restituisce la chiave più piccola
void* upo_bst_min(const upo_bst_t tree){
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if(tree == NULL || tree->root == NULL){
       return NULL;
    }

    upo_bst_node_t* tmp = upo_bst_minImpl(tree->root);

    if(tmp == NULL){
       return NULL;
    }
    return tmp->key;
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}

upo_bst_node_t* upo_bst_minImpl(upo_bst_node_t* node){
      if(node == NULL){
         return NULL;
      }
      if(node->left != NULL){
         return upo_bst_minImpl(node->left);
        } 
      return node; 
}


/**************************** funzionamento_MAX ******************************************************/
//max(t)
//restituisce la chiave più grande
void* upo_bst_max(const upo_bst_t tree){

    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if(tree == NULL || tree->root == NULL){
       return NULL;
    }
     
    upo_bst_node_t* tmp = upo_bst_maxImpl(tree->root);

    if(tmp == NULL){
       return NULL;
    }
    return tmp->key; 
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


upo_bst_node_t* upo_bst_maxImpl(upo_bst_node_t* node){
       
       if(node->right != NULL){
          return upo_bst_maxImpl(node->right);
       }
       return node; 
}


/************************** funzionamento_DeleteMIN **************************************************/
//delete_min(t)
//rimuove il nodo con la chiave più piccola
void upo_bst_delete_min(upo_bst_t tree, int destroy_data){

    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    
    //void* tmpKey = upo_bst_min(tree);
    upo_bst_delete(tree, upo_bst_min(tree), destroy_data);
    
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


/****************************** funzionamento_DeleteMAX ************************************************/
//delete_max(t)
//rimuove il nodo con la chiave più grande
void upo_bst_delete_max(upo_bst_t tree, int destroy_data){
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    
    //void* tmpKey = upo_bst_max(tree);    
    upo_bst_delete(tree, upo_bst_max(tree), destroy_data);

    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


/******************************* funzionamento_floor **********************************************************/
//floor(t,k)
//restituisce la più grande chiave  <=k
void* upo_bst_floor(const upo_bst_t tree, const void *key){

    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    
    if(tree == NULL || tree->root == NULL || key == NULL){
       return NULL;
    }
    void* tmpKey = upo_bst_floorImpl(tree->root, key, tree->key_cmp);
    return tmpKey;
    //fprintf(stderr, "To be implemented!\n");
    //abort();
}

void* upo_bst_floorImpl(upo_bst_node_t* node, void* key, upo_bst_comparator_t key_cmp){
        
  if(node == NULL){
   return NULL; 
  }

  int cmp_result = key_cmp(key, node->key); 
    
  if(cmp_result == 0) {
     return node->key;
    } else if (cmp_result < 0) {
        return upo_bst_floorImpl(node->left, key, key_cmp);
      } else {
         void* floor_in_right_subtree = upo_bst_floorImpl(node->right, key, key_cmp);
        if (floor_in_right_subtree != NULL) {
         return floor_in_right_subtree;
        }
        return node->key;
    }
}

/*********************************funzionamento_ceiling ********************************************************************/
//ceiling(t,k)
//Restituisce la più grande chiave >=k se esiste, altrimenti NULL
void* upo_bst_ceiling(const upo_bst_t tree, const void *key){
    
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    
    if(tree == NULL || tree->root == NULL){
       return NULL;
    }
    void* tmpKey = upo_bst_ceilingImpl(tree->root, key, tree->key_cmp);

    //fprintf(stderr, "To be implemented!\n");
    //abort();
}


void* upo_bst_ceilingImpl(upo_bst_node_t* node, void* key, upo_bst_comparator_t key_cmp){
    
    if(node == NULL){
       return NULL;
    }

    int cmp_result = key_cmp(key, node->key);

    if(cmp_result == 0){
       return node->key;
    }else if(cmp_result > 0){
      return upo_bst_ceilingImpl(node->right, key, key_cmp);
    }else{
      void* celing_in_left_subtree = upo_bst_ceilingImpl(node->left, key, key_cmp);
      if(celing_in_left_subtree != NULL){
         return celing_in_left_subtree;
      }
      return node->key;
    }
}



void upo_bst_keys_range_impl(const upo_bst_node_t *node, const void *low_key, const void *high_key, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list) {
    if(node != NULL) {
        upo_bst_keys_range_impl(node->left, low_key, high_key, key_cmp, list);
        upo_bst_key_list_node_t *list_node = NULL;
        list_node = malloc(sizeof(struct upo_bst_key_list_node_s));
        if(list_node == NULL) {
            perror("Unable to allocate node.\n");
            abort();
        }
        if((key_cmp(node->key, low_key) >= 0) && (key_cmp(node->key, high_key) <= 0)) {
            list_node->key = node->key;
            list_node->next = *list;
            *list = list_node;
        }
        upo_bst_keys_range_impl(node->right, low_key, high_key, key_cmp, list);
    }
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    if(tree == NULL) return NULL;
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_range_impl(tree->root, low_key, high_key, tree->key_cmp, &list);
    return list;
}

void upo_bst_keys_impl(const upo_bst_node_t *node, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list) {
    if(node != NULL) {
        upo_bst_keys_impl(node->left, key_cmp, list);
        upo_bst_key_list_node_t *list_node = NULL;
        list_node = malloc(sizeof(struct upo_bst_key_list_node_s));
        if(list_node == NULL) {
            perror("Unable to allocate node.\n");
            abort();
        }
        list_node->key = node->key;
        list_node->next = *list;
        *list = list_node;
        upo_bst_keys_impl(node->right, key_cmp, list);
    }
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    if(tree == NULL) return NULL;
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_impl(tree->root, tree->key_cmp, &list);
    return list;
}

int upo_bst_is_bst_impl(const upo_bst_node_t *node, const void *min_key, int min_key_changed, const void *max_key, int max_key_changed, upo_bst_comparator_t key_cmp) {
    if(node != NULL) {
        if(key_cmp(node->key, min_key) < 0 
        || (min_key_changed && key_cmp(node->key, min_key) == 0)
        || key_cmp(node->key, max_key) > 0
        || (max_key_changed && key_cmp(node->key, max_key) == 0)) {
            return 0;
        }
        return upo_bst_is_bst_impl(node->left, min_key, min_key_changed, node->key, 1, key_cmp) && upo_bst_is_bst_impl(node->right, node->key, 1, max_key, max_key_changed, key_cmp);
    }
    return 1;
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    if(tree == NULL) return 1;
    return upo_bst_is_bst_impl(tree->root, min_key, 0, max_key, 0, tree->key_cmp);
}
/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree){
    
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}