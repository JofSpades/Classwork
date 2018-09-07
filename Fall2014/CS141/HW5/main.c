#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {

    StackPtr sptr;

    sptr = stk_create();
    
    stk_push(sptr, 1.7);
    stk_push(sptr, 3.14);
    stk_print(sptr);

    stk_pop(sptr);

    stk_print(sptr);

    stk_free(sptr);

}
