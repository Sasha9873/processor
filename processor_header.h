#pragma once

#include "header.h"
#include <cmath>
//#include "C:\Users\lenovo\Desktop\infa\C\summer_school\stack\stack.cpp"

static const char *error_names[] = {
    "All is ok",
    "Not enough memory",
    "Two ctors",
    "Not pointer to error",
    "Bad stack pointer",
    "Negative capacity",
    "Negative size",
    "Wrong begin stack canary",
    "Wrong end stack canary",
    "Wrong begin data canary",
    "Wrong end data canary",
    "Bad data pointer",
    "Capacity smaller then size",    //12
    "Wrong hash",
    "This command does not exist",
    "Pop in empty stack",
    "You wrote not a number",       //16
};

typedef enum errors{ALL_OK            = 0,
                    NOT_MEMORY        = -1,
                    TWO_CTOR          = -2,
                    NOT_POINT_ERROR   = -3,
                    STACK_POINTER     = -4,
                    NEGATIVE_CAPASITY = -5,
                    NEGATIVE_SIZE     = -6,
                    BEGIN_CANARY      = -7,
                    END_CANARY        = -8,
                    DATA_BEGIN_CANARY = -9,
                    DATA_END_CANARY   = -10,
                    DATA_POINTER      = -11,
                    CAP_SMALLER_SIZE  = -12,
                    WRONG_HASH        = -13,
                    NO_SUCH_COMAND    = -14,
                    POP_EMPTY_STACK   = -15,
                    WRONG_VALUE       = -16,}
errors_t;

int execute(Stack* stk, processor* processor);
int stack_push(Stack* stack1, int value);
int stack_pop(Stack* stack1);
int stack_dtor(Stack* stack1);
errors_t stack_ok(Stack* stack1);    //enum errors stack_ok
int stack_dump(Stack* stack1, errors_t reason = ALL_OK);
int stack_hash(Stack* stack1, errors_t reason = ALL_OK);
int stack_print(Stack* stack1);

int processor(Stack* stack1, processor* processor);
