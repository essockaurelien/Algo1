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
 
#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/utility.h>
void MergeSortRec(void *base, size_t lo, size_t hi, size_t size, void  *aux, upo_sort_comparator_t cmp);
void Merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, void *aux, upo_sort_comparator_t cmp);
//void copyArray(void *dest, const void *src, size_t lo, size_t hi, size_t size);




void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char *baseVero = (unsigned char *)base;

    for (size_t i = 1; i < n; i++) {
        size_t j = i;
        while (j > 0) {
            void* current = baseVero + (j * size);
            void* previous = baseVero + ((j - 1) * size);

            if(cmp(previous, current) <= 0){
               break;     
            }
            upo_swap(previous, current, size);
            j--;
        }
    }
}
void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp){
    if(n<2) return;

    void *aux = malloc(n*size);
    if(aux == NULL) return;

        
    MergeSortRec(base, 0, n-1, size, aux, cmp);

    free(aux);
}

void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
     TO STUDENTS:
     *  Remove the following two lines and put here your implementation. 
    




    //fprintf(stderr, "To be implemented!\n");
    //abort();
}

void MergeSortRec(void *base,  size_t lo, size_t hi, size_t size, void  *aux, upo_sort_comparator_t cmp){
    
    if(lo >= hi) return;

    size_t mid = (lo +hi)/2;

MergeSortRec(base, lo, mid, size, aux,cmp);
MergeSortRec(base, mid+1, hi, size, aux,cmp);

Merge(base, lo, mid, hi, size, aux, cmp);
}

void Merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, void *aux, upo_sort_comparator_t cmp){
  size_t i = lo;
  size_t j = mid +1;
  size_t k = 0;

//copyArray(aux, base, lo, hi, size);

   memcpy(aux, (unsigned char *)base + lo*size, (hi-lo+1)*size);


//il mio nuovo
  while(i <= mid && j<=hi){
     if( cmp( (unsigned char *)aux + ((i-lo)*size) , (unsigned char *)aux + ((j-lo)*size) ) <= 0 ){
       memcpy((unsigned char *)base + k*size, ((unsigned char *)aux +(i-lo)*size), size);
       i++;
       //k++,
      }else{
        memcpy( ((unsigned char *)base+k*size), ( (unsigned char *)aux +(j-lo)*size ), size);
        j++;
       }
       k++;
    }

    while(i <= mid){
     memcpy((unsigned char *)base+k*size, (unsigned char *)aux +(i-lo)*size, size);
     i++;
     k++;
    }

    while(j <= hi){
     memcpy((unsigned char *)base+k*size, (unsigned char *)aux +(j-lo)*size, size);
     k++;
     j++;
    }

}

*/



#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/utility.h>
void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, void *temp, upo_sort_comparator_t cmp);
size_t Partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);





void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp){
    unsigned char* pc_base = (unsigned char*) base;

    size_t j;


    for(size_t i = 1; i < n; i++){
          j = i;
       while( j > 0 ){
       if( cmp( (void*) (pc_base + (j-1) * size ), (void*) (pc_base + j* size )) <= 0) {
            break;
       }
           upo_swap( (void*) (pc_base + (j-1) * size ) , (void*) (pc_base + j * size), size  );
            j--;
        
       }
    }
}


// Funzione ausiliaria per la fusione
void upo_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, void *temp, upo_sort_comparator_t cmp){

    size_t i = lo; 
    size_t j = mid + 1; 
    size_t k = 0; 

    memcpy(temp, (unsigned char *)base + lo * size, (hi - lo + 1) * size); 
    


    while (i <= mid && j <= hi) { 
        if (cmp((unsigned char *)temp + (i - lo) * size, (unsigned char *)temp + (j - lo) * size) <= 0) { 
            memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (i - lo) * size, size);
            i++;
        } else {
            memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (j - lo) * size, size);
            j++;
        }
        k++;
    }

    while (i <= mid) {
        memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (i - lo) * size, size);
        i++;
        k++;
    }

    while (j <= hi) {
        memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (j - lo) * size, size);
        j++;
        k++;
    }
}

// Funzione ricorsiva per Merge Sort
void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, void *temp, upo_sort_comparator_t cmp){ 
    if (lo >= hi)
        return;

    size_t mid = (lo + hi) / 2;

   
    upo_merge_sort_rec(base, lo, mid, size, temp, cmp);
    upo_merge_sort_rec(base, mid + 1, hi, size, temp, cmp);

  
    upo_merge(base, lo, mid, hi, size, temp, cmp);
}


void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp){
    if (n < 2) return; 

    void *temp = malloc(n * size);
    if (temp == NULL) return; 

    upo_merge_sort_rec(base, 0, n - 1, size, temp, cmp);

    free(temp);
}



/****************************************** Quick_sort *************************************************************/
//il mio quick_sort
void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp){
    if(n <= 1) return;
    quick_sort_rec(base, 0, n-1, size, cmp);
}


/******************************************* Quick_sort_ricorssivo *************************************************************/
//init_quick_sort_ricorssivo
void quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    if (lo >= hi) return;  
    size_t p = Partition(base, lo, hi, size, cmp);

  
    quick_sort_rec(base, lo, p - 1, size, cmp);  
    quick_sort_rec(base, p + 1, hi, size, cmp);  
}


/*************************************** Partition ********************************************************************/
//inizio_partition
size_t Partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    size_t p = lo; 
    size_t i = lo; 
    size_t j = hi; 

    while (1) {
        while (i <= hi && cmp((unsigned char *)base + i * size, (unsigned char *)base + p * size) < 0){
            i++;
        }

         while (cmp((unsigned char *)base + j * size, (unsigned char *)base + p * size) > 0){
            j--;
        }

        if (i >= j) {
            break; 
        }

     
        upo_swap((unsigned char *)base + i * size, (unsigned char *)base + j * size, size);
    }

   
    upo_swap((unsigned char *)base + p * size, (unsigned char *)base + j * size, size);
    return j;  
}



/*

function Partition(a,lo,hi)
    p <- lo
    i <- lo
    j <- hi + 1

    loop
       repeat
         i <- i +1
        until(i>=hi) or (a[i]>=a[p])
       repeat
         j<- j-1
        until (j<=lo) or (a[j]<=a[p])
        if i>=j then
           break
        end if
      swap(a,i,j)
      end loop
      swap(a,p,j)
      return j
end function        






void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp){
       
       size_t i=0, j=n+1, p=(n+1)/2, swap_wey = 0;
       size_t lo=0,hi=n;
     while(lo <= p && j >= p){
       if(cmp((unsigned char *)base+(i-lo)*size , (unsigned char *)base+(p-lo)*size) <= 0){
            swap_wey++;  //break;
        }else{
         i++;
       }
       if(cmp((unsigned char *)base+(j-hi)*size , (unsigned char *)base+(p-lo)*size) >= 0){
            swap_wey++;//break;
       }else{
          j--;
       }
           if(swap_wey == 2){
              swap((unsigned char *)base+(j-hi)*size, (unsigned char *)base+(p-lo)*size);
              i++;
              j--;
           }
     }
     upo_quick_sort(base, n, size,  cmp);
     upo_quick_sort(base, n, size,  cmp);
}



*/