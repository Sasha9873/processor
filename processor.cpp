#include "header.h"
#include "processor_header.h"


int stack_ctor(Stack* stack1)
{
    if(stack1->data == POINTER_13){

        #ifdef DATA_USE_CANARY
            stack1->data = (int*)calloc(stack1->capacity + 2, sizeof(int));
        #else
            stack1->data = (int*)calloc(stack1->capacity, sizeof(int));
        #endif  // DATA_USE_CANARY

        if(stack1->data == NULL){
                CHECKSTACK(NOT_MEMORY);
                return NOT_MEMORY;
        }

        #ifdef DATA_USE_CANARY
            stack1->data[0] = CANARY_VALUE;
            stack1->data[stack1->capacity + 1] = CANARY_VALUE;
        #endif  // DATA_USE_CANARY

        stack1->current_size = 0;
    }
    else{
        CHECKSTACK(TWO_CTOR);
        return TWO_CTOR;
    }

    CHECKSTACK(ALL_OK);

    return ALL_OK;
}

int processor(Stack* stack1)
{
    int pc = 0;

    while()
}
