#include <stdio.h>
#include "list.h"

// very incomplete small test program...

int main() {
    LIST *lst1;
    LIST *lst2;
    LIST *lst3;
    LIST *lst4;
    LIST *lst5;
    int i;
    
    ElemType a[] = {2, 5, 10, 20, 500, 99999};

    ElemType b[] = {1, 3, 6,  8,  99, 244};
    //change his value for the slow remove and fas remoe functions
    int n = 20;
    
    lst1 = lst_create();
    lst4 = lst_create();
    lst5 = lst_create();
    
    for(i=0; i<5; i++) {
        lst_push_front(lst1, i);
    }
    for(i=0; i<5; i++) {
        lst_push_back(lst1, i);
    }
    for(i=0; i<6; i++) {
        lst_push_back(lst4, a[i]);
        lst_push_back(lst5, b[i]);
    }
    printf("lst4:");
    lst_print(lst4);
    if(lst_is_sorted(lst4)){
        printf("IS SORTED\n");
    }
    printf("lst5:");
    lst_print(lst5);
    
    //fills list of size n with elements of (n-1)->1
    lst2 = lst_sra_bad_case(n);
    printf("lst2:");
    lst_print(lst2);
    //goes through and one element at a time 1->(n-1)
    
    for(int i = 0; i < n; i++){
        lst_remove_all_slow(lst2, i);
    }
    
    lst3 = lst_create();
    printf("lst3:");
    
    for(i=0; i<5; i++) {
        lst_push_front(lst3, i);
    }
    for(i=0; i<5; i++) {
        lst_push_back(lst3, i);
    }
    lst_print(lst3);
    
    for(int i = 0; i < n; i++){
        lst_remove_all_fast(lst3, i);
    }
    
    /*if(!lst_sanity1(lst1)){
     
     printf("BROKEN FAILED SANITY CHECK 1\n");
     return 0;
     
     } else if(!lst_sanity2(lst1)){
     
     printf("BROKEN FAILED SANITY CHECK 2\n");
     return 0;
     
     } else if(!lst_sanity3(lst1)){
     
     printf("BROKEN FAILED SANITY CHECK 3\n");
     return 0;
     
     }*/
     
     printf("lst_len(lst1) : %i\n", lst_len(lst1));
     printf("lst1 contents: ");
     lst_print(lst1);
     
     
     lst_pop_front(lst1);
     lst_pop_front(lst1);
     printf("lst1 contents after two pops: ");
     lst_print(lst1);
     
     
     
     /** TODO:  test code here! **/
    
    
    lst_pop_back(lst1);
    lst_pop_back(lst1);
    printf("lst1 contents after two pops back: ");
    lst_print(lst1);
    
    
    /** test code for lst_count **/
    
    printf("number of 3's = %i\n", lst_count(lst1, 3));
    printf("number of 0's = %i\n", lst_count(lst1, 0));
    
    
    /** test code for lst_print_rev **/
    
    for(i=0; i<8; i++) {
        lst_push_front(lst1, i);
    }
    for(i=0; i<3; i++) {
        lst_push_back(lst1, i);
    }
    
    printf("PRINTING REVERSED\n");
    lst_print_rev(lst1);
    printf("THIS IS THE ARRAY ONCE IT IS REVERSED\n");
    lst_reverse(lst1);
    lst_print(lst1);
    
    
    /** test code for lst_push_back **/
    
    lst_insert_sorted(lst4, 9);
    printf("lst4 after inserting a 9:");
    lst_print(lst4);
    
    lst_merge_sorted(lst4, lst5);
    printf("lst5 into lst4:");
    lst_print(lst4);
    
    lst_free(lst1);
    lst_free(lst2);
    lst_free(lst3);
    lst_free(lst4);
    lst_free(lst5);
}