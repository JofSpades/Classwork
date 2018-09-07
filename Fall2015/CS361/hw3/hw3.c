
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct memory_region{
    size_t * start;
    size_t * end;
};

struct memory_region global_mem;
struct memory_region heap_mem;
struct memory_region stack_mem;

// grabbing the address and size of the global memory region from
// proc 
void init_global_range(){
    char file[100];
    char * line=NULL;
    size_t n=0;
    size_t read_bytes=0;
    size_t start, end;
    
    sprintf(file, "/proc/%d/maps", getpid());
    FILE * mapfile  = fopen(file, "r");
    if (mapfile==NULL){
        perror("opening maps file failed\n");
        exit(-1);
    }
    
    int counter=0;
    while ((read_bytes = getline(&line, &n, mapfile)) != -1) {
        if (strstr(line, "hw3")!=NULL){
            ++counter;
            if (counter==3){
                sscanf(line, "%lx-%lx", &start, &end);
                global_mem.start=(size_t*)start;
                global_mem.end=(size_t*)end;
            }
        }
        else if (read_bytes > 0 && counter==3){
            //if the globals are larger than a page, it seems to create a separate mapping
            sscanf(line, "%lx-%lx", &start, &end);
            if (start==global_mem.end){
                global_mem.end=(size_t*)end;
            }
            break;
        }
    }
    fclose(mapfile);
}

void init_gc() {
    init_global_range();
    heap_mem.start=malloc(512);
    char stack_start = 'm';
    stack_mem.end = ((size_t*) &stack_start);
}

// The following funtions are the implamentations of functions found
// in psuedo code on page 840 and 841 in the book.

int blockAllocated(size_t* p){
    // Returning the "Previous inuse bit" from next chunk passing in
    // the "mem" pointer
    size_t size = (((*(p - 1)) & ~(size_t)7) / 8);
    size_t *nextP = (p + size);
    if(nextP > (size_t*)sbrk(0)){
	return 1;
    } 
    return ((*(nextP - 1)) & 1);
}

size_t* foundChunk(size_t *p){
    // Searching the heap in order to find the proper point in the
    // heap to return 
    size_t* iter = heap_mem.start;
    size_t size = 0;
    size_t header;
    while(iter < heap_mem.end){
	    // Getting the header for the current chunk
	    header = *(iter - 1);
        // Getting size of current chunk
        size = (header & ~(size_t)7) / 8;

        if((iter + size) > heap_mem.end){
            return NULL;
        }

        // If the given pointer resides in the current chunk then
        // return the mem pointer to the current chunk
        if(((size_t*)*((iter - 1)) <= (p)) && (((size_t*)*((iter + size) - 1)) > (p))){
	    // if(((iter - 1) <= (p)) && ((iter + size) > (p))){
            return iter;
        }
        iter += size;
    }
    return NULL;
}

size_t* isPtr(size_t *p){
    // Check to see if the provided pointer is actually a pointer or
    // just really big or a negitive varable
    if(p == 0x0){
        return NULL;
    } else if((heap_mem.start <= ((size_t*)*p)) && (heap_mem.end > ((size_t*)*p))){

        // If the pointer is actually in the range of heap addresses
        // look for its mem pointer
        return foundChunk(p);

    // Else the value is not in the heap so return NULL
    } else {
        return NULL;
    }
}

// Mark portion of the "Mark n'Sweep" algorithm for the garbage
// collector
void mark (size_t *p){
    // Check for the input being an actual pointer

    size_t* usablePointer = isPtr(p);
    if(usablePointer == NULL){
        return;
    }

    // Getting the header for the chunk
    size_t header = *(usablePointer - 1);

    // Checking for if the block of memory is already marked if so
    // then no need to continue with this block
    if ((header & 4)){
        return;
    }

    // Getting the size of the chunk 
    size_t sizeOfChunk = (header & ~(size_t)7) / 8;

    // At this point it can be proven that the block is still in use
    // and so we mark the 3rd LSB as proof
    header = header | 4;

    // Then we repeate for every possible memory address in the
    // chunk's payload
    for(int i = 0; i < (sizeOfChunk - 1); i++){
        mark((size_t*)usablePointer[i]);
    }
    return;
}

void gc() {
    // Obtaining the address for where the stack is currently in
    // memory
    char stack_var = 'm';
    stack_mem.start = (size_t*) &stack_var;

    // Setting the end of the heap
    heap_mem.end=sbrk(0);

    // Setting where I will start with the heap stack and global
    // areas of memory
    size_t *heapIter = heap_mem.start;
    size_t *stackIter =(size_t*)((size_t)(stack_mem.start) & ~(size_t)7);
    size_t *globalIter = global_mem.start;

    // Initlizing the variable used to get the header information
    size_t header = *(heapIter - 1);
    size_t size = 0;

    // Walking though the the stack to find all values and send
    // them to see if its a pointer
    while(stackIter < stack_mem.end){
        mark(stackIter);
        ++stackIter;
    }
    // Walkingthrough the global variable range to find all values
    // and send them to see if its a pointer to the heap
    while(globalIter < global_mem.end){
        mark(globalIter);
	    ++globalIter;
    }
    // Sweeping the entire heap looking for unmarked chunks and
    // freeing them
    while(heapIter < (size_t*)sbrk(0)){
        // Obtaining the header fo the current heap chunk and
        // generating the size
        header = *(heapIter - 1);
        size = (header & (~((size_t)7))) / 8;
        if((heapIter + size) > (size_t*)sbrk(0)){
            break;
        }

        // Checking if the block is marked and if it is just unmark
        // it if it is not marked free the block of memory
        if(header & (size_t)4){
            header = header & ~(size_t)4;
	        heapIter += size;

        // Only free the memory if its not the first element of the
        // heap
        } else if (blockAllocated(heapIter)){
	        size_t* currentChunk = heapIter;
	        heapIter += size;
            free(currentChunk);
        } else {
        // Once freed or unmarked jump to the next chunk and
	    // repeat
	    heapIter += size;
    	}
    }
}
