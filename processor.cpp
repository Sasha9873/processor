#include "header.h"
#include "processor_header.h"

int execute(struct processor* processor)
{
    verify(processor);

    int k = 0;
    processor->ip = 0;

    while(k == 0){
        int cmd = 0;
        cmd = processor->code[processor->ip];
        printf("cmd = %d\n", cmd);
        switch(cmd)
        {
            case PUSH:
            {
                processor->ip++;
                int val = 0;
                val = processor->code[processor->ip];
                printf("val = %d\n", val);
                stack_push(processor->stk, val);
                processor->ip++;
                break;
            }

            case POP:
            {
                int del = stack_pop(processor->stk);
                processor->ip++;
                break;
            }
            case MUL:
            {
                stack_push(processor->stk, stack_pop(processor->stk) * stack_pop(processor->stk));
                processor->ip++;
                break;
            }
            case ADD:
            {
                stack_push(processor->stk, stack_pop(processor->stk) + stack_pop(processor->stk));
                processor->ip++;
                break;
            }
            case SUB:
            {
                int x1 = 0, x2 = 0;
                x2 = stack_pop(processor->stk);
                x1 = stack_pop(processor->stk);
                stack_push(processor->stk, x1 - x2);
                processor->ip++;
                break;
            }
            case HLT:
            {
                k++;
                processor->ip++;
                break;
            }
            case OUT:
            {
                stack_print(processor->stk);
                processor->ip++;
                break;
            }
            case IN:
            {
                processor->ip++;
                int val = 0;
                printf("Write value:\n");
                if(scanf("%d", &val) != 1)
                    return WRONG_VALUE;

                printf("val = %d\n", val);
                stack_push(processor->stk, val);
                break;
            }
            case RPUSH:
            {
                processor->ip++;
                stack_push(processor->stk, processor->regs[processor->code[processor->ip] - 1]);

                processor->ip++;
                break;
            }
            case RPOP:
            {
                processor->ip++;
                processor->regs[processor->code[processor->ip] - 1] = stack_pop(processor->stk);

                processor->ip++;
                break;
            }

            default:
            {
                printf("default\n");
                return NO_SUCH_COMAND;
            }

        }
    }
    return ALL_OK;
}


errors_t verify(struct processor* proc)
{
    errors_t error = ALL_OK;

    if((error = stack_ok(proc->stk)) != ALL_OK)
        return error;

    if(!proc)
        return BAD_PROC_POINTER;

    if(proc->code_bin == NULL)
        return NULL_CODE_BIN;

    if(proc->code == NULL)
        return NULL_CODE;

    if(proc->ip < 0)
        return BAD_INSTRACTION_POINTER;

    if(proc->size_code < 0)
        return NEGATIVE_CODE_SIZE;

    return ALL_OK;

}


/*int execute(Stack* stk, struct processor* processor)
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
}*/

