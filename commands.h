typedef enum comands{
    OUT   = 0,
    HLT   = 1,
    PUSH  = 17,
    POP   = 18,
    ADD   = 2,
    SUB   = 3,
    MUL   = 4,
    IN    = 5,
    RPOP  = 33,
    RPUSH = 34,
}comands_t;

DEFCMD(PUSH, 17, 1,{
	val = processor->code[processor->ip + 1];
    stack_push(processor->stk, val);
})

DEFCMD(POP, 18, 0,{
	int del = stack_pop(processor->stk);
})

DEFCMD(ADD, 2, 0,{
	int a = stack_pop(processor->stk);
	int b = stack_pop(processor->stk);
	stack_push(processor->stk, a + b);
})

DEFCMD(SUB, 3, 0,{
	int a = stack_pop(processor->stk);
	int b = stack_pop(processor->stk);
	stack_push(processor->stk, a - b);
})

DEFCMD(MUL, 4, 0,{
	int a = stack_pop(processor->stk), b = stack_pop(processor->stk);
	stack_push(processor->stk, a + b);
})