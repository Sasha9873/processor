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

int execute()
{
    while(1){
        int cmd = 0;
        fscanf(processor->code, "%d", &cmd);
        switch(cmd)
        {
            case PUSH:
            {
                int val = 0;
                fscanf(processor->code, "%d", &val);
                stack_push(&stk, val);
                break;
            }

            case POP:
            {
                int del = stack_pop(&stk);
                break;
            }
            case MUL:
            {
                stack_push(&stk, stack_pop(&stk) * stack_pop(&stk));
                break;
            }
            case ADD:
            {
                stack_push(&stk, stack_pop(&stk) + stack_pop(&stk));
                break;
            }
            case SUB:
            {
                int x1 = 0, x2 = 0;
                x1 = stack_pop(&stk);
                x2 = stack_pop(&stk);
                stack_push(&stk, x1 - x2);
                break;
            }
        }
    }
}

int processor(Stack* stack1)
{
    int pc = 0;

    while()
}
