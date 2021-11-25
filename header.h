#pragma once

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#define CHECK 0

#if CHECK >= 2
    #define STACK_USE_HASH
    #define STACK_USE_CANARY
    #define DATA_USE_CANARY
#elif CHECK >= 1
    #define STACK_USE_CANARY
    #define DATA_USE_CANARY
#endif // CHECK

#define CHECKSTACK(reason)\
    if(!stack_ok(stack1)){\
    fprintf(stack1->file_with_errors, "Called from %s() at %s(%d),\n", __FUNCTION__, __FILE__, __LINE__);\
    stack_dump(stack1, reason);\
}

static int CHANGE = 2;
static const int POISON = 666;
static int* POINTER_13 = (int*)13;
static const int CANARY_VALUE = 0xBADDED;
static int previous_hash_value;
static int hash_value;

typedef enum comands{
    OUT  = 0,
    HLT  = 1,
    PUSH = 17,
    POP  = 18,
    ADD  = 2,
    SUB  = 3,
    MUL  = 4,
    IN   = 7,
}comands_t;

static const char *comands_names[] = {
        "out",
        "hlt",
        "add",
        "sub",
        "mul",  //4
        "",
        "",
        "in",
        "",
        "",
        "",
        "",     //11
        "",
        "",
        "",
        "",
        "",
        "push", //17
        "pop",
};

struct Stack
{
    #ifdef STACK_USE_CANARY
    int begin_canary = CANARY_VALUE;
    #endif

    size_t capacity = 0; //��������� ������ �������
    size_t current_size = 0;//������� ������ �������
    int *data = POINTER_13; //����� ������� data[capacity]

    FILE* file_with_errors = NULL;

    #ifdef STACK_USE_CANARY
    int end_canary = CANARY_VALUE;
    #endif
};


typedef struct processor{
    int regs[4];
    struct Stack stack1 = {};
    int* code;
    long int size_code = 0;
    FILE* code_bin = NULL;
}Processor;


