#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct node {
	ElemType val;
	struct node *next;
} NODE;


struct list_struct {
	NODE *front;
	NODE *back;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
	LIST *l = malloc(sizeof(LIST));

	l->front = NULL;
	l->back = NULL;
	return l;
}

void lst_free(LIST *l) {
	NODE *p = l->front;
	NODE *pnext;

	while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
}
  	// now free the LIST 
free(l);
}

void lst_print(LIST *l) {
	NODE *p = l->front;

	printf("[");
		while(p != NULL) {
			printf(FORMAT, p->val);
			p = p->next;
		}
		printf("]\n");
	}

/**
* TODO:  print in reverse order 
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/

void printLastRecus(NODE *n){

	if(n != NULL){

		printLastRecus(n->next);

		printf(FORMAT, n->val);

		return;
		
	}

}

void lst_print_rev(LIST *l) {

	NODE *p = l->front;

	printf("[");

    printLastRecus(p);

    printf("]\n");

	}

void lst_push_front(LIST *l, ElemType val) {
    NODE *p = malloc(sizeof(NODE));

	p->val = val;
	p->next = l->front;

	l->front = p;
    if(l->back == NULL)   // was empty, now one elem
        l->back = p;
}

void lst_push_back(LIST *l, ElemType val) {
	NODE *p;

  if(l->back == NULL)   // list empty - same as push_front
  	lst_push_front(l, val);
  else {  // at least one element before push
  	p = malloc(sizeof(NODE));
  	p->val = val;
  	p->next = NULL;
  	l->back->next = p;

  	l->back = p;  
  }
}

int lst_len(LIST *l) {
	NODE *p = l->front;
	int n=0;

	while(p != NULL) {
		n++;
		p = p->next;
	}
	return n;
}

int lst_is_empty(LIST *l) {
	return l->front == NULL;
}


/** TODO
 *    function:  lst_count
*     description:  Counts number of occurrences 
*     		of x in the list and returns 
*     		that value.
*/
int lst_count(LIST *l, ElemType x) {

	int count = 0;
	NODE *n = l->front;

	while(n != NULL){

		if(n->val == x){

			count++;

		}

		n = n->next;
	}

	return count;
}


/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/

int lst_sanity1(LIST *l) {
	if(l->front == NULL && l->back != NULL){
		fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
		return 0;
	}
	if(l->back == NULL && l->front != NULL){
		fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
		return 0;
	}
	return 1;
}

int lst_sanity2(LIST *l) {
	if(l->back != NULL && l->back->next != NULL) {
		fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
		return 0;
	}
	return 1;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int lst_sanity3(LIST *l) {

	NODE *n = l->front;

	while(n != NULL){

		n = n->next;

	}

	if(l->back != n){

		return 1;

	}

	return 0;
}



ElemType lst_pop_front(LIST *l) {
	ElemType ret;
	NODE *p;


	if(lst_is_empty(l))
	return DEFAULT;   // no-op

	ret = l->front->val;

  	if(l->front == l->back) {  // one element
  		free(l->front);
  		l->front = NULL;
  		l->back = NULL;
  	}
  	else {
		p = l->front;  // don't lose node being deleted
		l->front = l->front->next;  // hop over
		free(p);
	}
	return ret;
}





/* TODO 
*    
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*
*/
ElemType lst_pop_back(LIST *l) {

	ElemType ret;
	NODE *p = NULL;
	NODE *n = l->front;

	if(lst_is_empty(l))
	return DEFAULT;

	while(n->next->next != NULL){

		n = n->next;

	}

	ret = l->back->val;

  	if(l->front == l->back) {  // one element

  		free(l->front);

  		l->front = NULL;
  		l->back = NULL;
  	}
  	else {
		p = l->back;  // don't lose node being deleted
		l->back = n;  // hop over
        n->next = NULL;
		free(p);
	}
	return ret;

}

/* TODO
*  For full credit, you cannot allocate any new memory!
*
* description:  self-evident
*/
void lst_reverse(LIST *l) {
    
    NODE *n;
    NODE *c;
    NODE *p;
    
    c = l->front;
    l->back = l->front;
    p = NULL;
    
    while (c!= NULL) {
        
        n = c->next;
        
        c->next = p;
        
        p = c;
        
        c = n;
    }
    
    l->front = p;

}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/
int lst_remove_first(LIST *l, ElemType x) {
	NODE *p;
	NODE *tmp;

	if(l->front == NULL) return 0;
	if(l->front->val == x) {
		lst_pop_front(l);
		return 1;
	}
  // lst non-empty; no match on 1st elem
	p = l->front;

	while(p->next != NULL) {
		if(x == p->next->val) {
			tmp = p->next;
			p->next = tmp->next;
			if(tmp == l->back) 
				l->back = p;
			free(tmp);
			return 1;
		}
		p = p->next;
	}
	return 0;
}


int lst_remove_all_slow(LIST *l, ElemType x) {
	int n=0;
	while(lst_remove_first(l, x))
		n++;
	return n;
}

/** TODO
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that 
 * the above function takes quadratic time to remove
 * all occurrences of a specified value. 
 *
 * By convention, the specified value will be 0
 */
 LIST *lst_sra_bad_case(ElemType n) {
     
     LIST *out = malloc(sizeof(LIST));
     
     for(int i = 0; i < n; i++){
         
         lst_push_front(out, i);
     }
     
     return out;

 }

// TODO
// desc:  see header file
 int lst_remove_all_fast(LIST *l, ElemType x) {
     
     NODE *n = l->front;
     NODE *dntfrgt = NULL;
     int cnt = 0;
     
     if(l->front == NULL) return 0;
     
     while(n != NULL){
         
         if(n->val == x){
         
             dntfrgt = n->next;
             n->next = dntfrgt->next;
             
             if(dntfrgt == l->back){
                 
                 l->back = n;
                 
             }
             
             free(dntfrgt);
             cnt++;
             
         }
         
         n = n->next;
         
     }
     
     if(cnt >= 1){
         
         return cnt;
         
     } else {
         
         return 0;
     }
     
 }

// TODO
 int lst_is_sorted(LIST *l){
     
     NODE *n = l->front;
     
     while(n->next != NULL){
         
         if (n->next->val < n->val) {
             
             //notsorted in the proper form
             return 0;
             
         }

         n = n->next;
         
     }

     return 1;

 }



/** TODO
 
 
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x) {
    
    NODE *n = l->front;
    NODE *i = malloc(sizeof(NODE));
    
    i->val = x;
    
    while(n->next != NULL){
        
        if (x > n->val && x <= n->next->val) {
            
            i->next = n->next;
            n->next = i;
            
            return;
            
        }
        
        n = n->next;
        
    }

}

NODE * mergSortedRecrs(NODE *n, NODE *m){
    
    NODE *retn;
    if(n == NULL){
        
        return m;
    
    } else if (m == NULL){
        
        return n;
        
    }
    
    if(n->val < m->val){
        
        retn = n;
        
        retn->next = mergSortedRecrs(n->next, m);
        
    } else if(m->val < n->val){
        
        retn = m;
        
        retn->next = mergSortedRecrs(n, m->next);
        
    }
    
    return retn;
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.  
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted, 
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 * 
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */
 void lst_merge_sorted(LIST *a, LIST *b){
     
     NODE *n = a->front;
     NODE *m = b->front;
     
     a->front = mergSortedRecrs(n, m);
     
     b->front = NULL;
     b->back = NULL;

 }

