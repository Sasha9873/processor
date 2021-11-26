#include "processor_header.h"
#include "processor.cpp"


int main()
{
    Processor proc = {};
    Stack stk = {};

    FILE* code_txt = fopen("code.txt", "r");
    proc.code_bin = fopen("code.bin", "r");
    stk.file_with_errors = fopen("listing.txt", "w+");

    stack_ctor(&stk);

    printf("\n    %d\n", proc.size_code);

    fseek(proc.code_bin, 0, SEEK_END);
    proc.size_code = ftell(proc.code_bin)/sizeof(int);
    fseek(proc.code_bin, 0, SEEK_SET);

    proc.code = (int*)calloc(proc.size_code, sizeof(int));

    printf("size = %d\n", proc.size_code);

    fread(proc.code, sizeof(int), proc.size_code, proc.code_bin);

    for(int len = 0; len < proc.size_code; len++)
            printf("%d" ,proc.code[len]);
    printf("\n");

    execute(&stk, &proc);

    fclose(code_txt);

    return 0;
}
