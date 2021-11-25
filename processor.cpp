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

int execute(Stack* stk, struct processor* processor)
{
    int k = 0;

    while(k == 0){
        int cmd = 0;
        fscanf(processor->code, "%d", &cmd);
        switch(cmd)
        {
            case PUSH:
            {
                int val = 0;
                fscanf(processor->code, "%d", &val);
                stack_push(stk, val);
                break;
            }

            case POP:
            {
                int del = stack_pop(stk);
                break;
            }
            case MUL:
            {
                stack_push(stk, stack_pop(stk) * stack_pop(stk));
                break;
            }
            case ADD:
            {
                stack_push(stk, stack_pop(stk) + stack_pop(stk));
                break;
            }
            case SUB:
            {
                int x1 = 0, x2 = 0;
                x1 = stack_pop(stk);
                x2 = stack_pop(stk);
                stack_push(stk, x1 - x2);
                break;
            }
            case HLT:
            {
                k++;
                break;
            }
            case OUT:
            {
                stack_print(stk);
                break;
            }
            case IN:
            {

            }
            default:
                return NO_SUCH_COMAND;
        }
    }
}

int stack_print(Stack* stack1)
{
    #ifdef STACK_USE_HASH
        previous_hash_value = hash_value;
        hash_value = stack_hash(stack1, ALL_OK);
        if(previous_hash_value == hash_value)
            fprintf(stack1->file_with_errors, "Hash is ok\n");
        else
            fprintf(stack1->file_with_errors, "Hash is not ok: previous hash was %d, current hash is %d\n", previous_hash_value, hash_value);
    #endif // STACK_USE_HASH

    printf("Stack[%p]", stack1);

    errors_t error = stack_ok(stack1);
    if(error == ALL_OK)
        printf("(ok)\n");
    else
        printf("ERROR %d %s", error, error_names[abs(error)]);

    printf("{\n");

    #ifdef STACK_USE_CANARY
        printf("   stack_begin_canary = %x\n", stack1->begin_canary);
    #endif // STACK_USE_CANARY

    printf("   capacity = %ld\n   current size = %ld\n", stack1->capacity, stack1->current_size);

    printf("   data[%p] = %p\n   {\n", &stack1->data, stack1->data);

    #ifdef DATA_USE_CANARY
        fprintf(stack1->file_with_errors, "      c[o](first canary) = %x\n", stack1->data[0]);

        for(int num = 1; num <= stack1->capacity; num++){
            if(num <= stack1->current_size)
                fprintf(stack1->file_with_errors, "      *");
            else
                fprintf(stack1->file_with_errors, "      ");
            fprintf(stack1->file_with_errors, "[%d] = %d\n", num, stack1->data[num]);
        }
        fprintf(stack1->file_with_errors, "      c[%d](second canary)(%p) = %x\n", stack1->capacity + 1, &stack1->data[stack1->capacity + 1], stack1->data[stack1->capacity + 1]);
    #else
        for(int num = 0; num < stack1->capacity; num++){
            if(num <= stack1->current_size - 1)
                printf("      *");
            else
                printf("      ");
            printf("[%d](%p, %p) = %d\n", num, &(stack1->data[num]), stack1->data + num, stack1->data[num]);
        }
    #endif // DATA_USE_CANARY

    printf("   }\n");

    printf("   file_with_errors[%p] = %p\n", &stack1->file_with_errors, stack1->file_with_errors);

    #ifdef STACK_USE_CANARY
        fprintf(stack1->file_with_errors, "   stack_end_canary = %x\n", stack1->end_canary);
    #endif // STACK_USE_CANARY

    fprintf(stack1->file_with_errors, "}\n\n");

   return 0;
}

