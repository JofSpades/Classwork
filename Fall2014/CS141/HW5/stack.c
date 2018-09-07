#include "stack.h"


struct stack_struct {
    ElemType items[CAPACITY];
    int top;
};


StackPtr stk_create(){
    StackPtr s = malloc(sizeof(struct stack_struct));

    s->top = -1;  // stack initially empty
    return s;
}

void stk_free(StackPtr s) {
    free(s);
}

int stk_push(StackPtr s, ElemType val){
    if(s->top == CAPACITY - 1)
	return 0;
    s->top++;
    s->items[s->top] = val;
    return 1;
}

ElemType stk_pop(StackPtr s){
    if(s->top == -1)
        abort();  // library function which terminates program!!!
    s->top--;
    return s->items[s->top+1];
}

int stk_is_full(StackPtr s){
    return s->top == CAPACITY-1;
}

int stk_is_empty(StackPtr s){
    return s->top == -1;
}

int stk_size(StackPtr s) {
    return s->top+1;
}

void stk_clear(StackPtr s){
    s->top = -1;
}

void stk_print(StackPtr s) {
    int i;
    printf("\n----TOP-----\n");

    for(i=s->top; i>=0; i--) {
        printf(FORMAT_STRING, s->items[i]);
    }
    printf("---BOTTOM---\n");
}
