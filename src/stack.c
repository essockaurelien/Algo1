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

#include "stack_private.h"
#include <stdio.h>
#include <stdlib.h>

upo_stack_node_t* upo_stack_node_create(void *data){
    upo_stack_node_t *node = malloc(sizeof(upo_stack_node_t));
    if (node == NULL)
    {
        perror("Unable to create a node stack");
        abort();
    }

    node->data = data;
    node->next = NULL;

    return node;
}

upo_stack_t upo_stack_create(){
    upo_stack_t stack = malloc(sizeof(struct upo_stack_s));
    if (stack == NULL)
    {
        perror("Unable to create a stack");
        abort();
    }

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void upo_stack_destroy(upo_stack_t stack, int destroy_data){
    if (stack != NULL)
    {
        upo_stack_clear(stack, destroy_data);
        free(stack);
    }
}


void upo_stack_push(upo_stack_t stack, void *data){
    if(stack == NULL || data == NULL) return;
       upo_stack_node_t* tmp = upo_stack_node_create(data);
       tmp->next = stack->top;
       stack->top = tmp; 
       stack->size++;
}


//Rimuove l'elemento in cima a s
void upo_stack_pop(upo_stack_t stack, int destroy_data){
    
    if (stack == NULL || stack->top == NULL) return;
    upo_stack_node_t* tmp = stack->top;
    stack->top = stack->top->next;
    if (destroy_data)
    {
        free(tmp->data);
    }
    free(tmp);
    stack->size--; 
}


void* upo_stack_top(const upo_stack_t stack){
    if(upo_stack_is_empty(stack)){
        return NULL;
    }    
    return stack->top->data; 
}   

int upo_stack_is_empty(const upo_stack_t stack){
    if(stack == NULL || stack->top == NULL ){  
        return 1;
    }
    else{
        return 0;
    }
}

size_t upo_stack_size(const upo_stack_t stack){
    if(stack != NULL){
        return stack->size;
    }
    else
    {
        return 0;
    }
    
}

void upo_stack_clear(upo_stack_t stack, int destroy_data){
    /* HINT:
     * 1. For each node of the list stored in "stack":
     *  1.1 Save the node pointed by "top" to a temporary variable "node"
     *  1.2 Advance the "top" pointer by one node
     *  1.3 If "destroy_data" != 0, destroy user data stored in "node" by invoking "free(node->data)"
     *  1.4 Destroy "node" by invoking "free(node)"
     * 2. Update stack size.
     */
    if(stack == NULL)
    return ;
    
    while(stack->top != NULL){

        upo_stack_node_t* node = stack->top;

        stack->top = node->next;

        if(destroy_data != 0){
            free(node->data);
        }

        free(node);

        stack->size--;
    }
}
