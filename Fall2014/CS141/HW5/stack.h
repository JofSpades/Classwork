#include <stdio.h>
#include <stdlib.h>

// stack.h establishes the interface functions for stacks.


// maximum stack size
#define CAPACITY 128

// a Stack is a pointer to a structure
// where is this struct defined?

typedef struct stack_struct *StackPtr;

typedef struct stack_struct StackStruct;

// These two lines are for setting the type of objects the stack
//    stores and how to print them.
// They may be modified to create stacks of non-int types without
//     changing stack.c
// typedef double ElemType;
typedef int ElemType;

// #define FORMAT_STRING "  %lf\n"
#define FORMAT_STRING "  %c\n"

// initializes and returns an empty stack (as a pointer)
extern StackPtr stk_create();

// deallocates storage for stack
extern void stk_free(StackPtr s);

// pushes val onto stack.  returns 0 or 1
//   depending on success or failure (if already full)
extern int stk_push(StackPtr s, ElemType val);

// pops and returns top value from stack.
// if stack is empty, entire program aborts!  Caller's responsibility
// to make sure stack not empty.
extern ElemType stk_pop(StackPtr s);

// self-explanatory
extern int stk_is_full(StackPtr s);

// self-explanatory
extern int stk_is_empty(StackPtr s);

// returns number of elements on the stack
extern int stack_size(StackPtr s);

// empties stack
extern void stk_clear(StackPtr s);

// dumps stack contents
extern void stk_print(StackPtr s);
