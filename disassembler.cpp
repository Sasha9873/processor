#include "header.h"

typedef enum errors{
    ALL_OK         =  0,
    NOT_MEMORY     = -1,
    BAD_REG        = -2,
    NO_SUCH_COMAND = -3,
}errors_t;


errors_t disassembler(FILE*code_bin, FILE* disasm_code_txt);
int listing(FILE* file_lst, int* code);

int main()
{
    FILE* code_bin = fopen("code.bin", "r");
    FILE* disasm_code_txt = fopen("disasm_code.txt", "w");

    errors_t error;
    disassembler(code_bin, disasm_code_txt);

    fclose(disasm_code_txt);
    fclose(code_bin);

    return 0;
}

errors_t disassembler(FILE* code_bin, FILE* disasm_code_txt)
{
    fseek(code_bin, 0, SEEK_END);
    int size_code = ftell(code_bin)/sizeof(int);
    fseek(code_bin, 0, SEEK_SET);

    int* code = (int*)calloc(size_code, sizeof(int));

    printf("size = %d\n", size_code);

    fread(code, sizeof(int), size_code, code_bin);

    int position = 0;
    while(position < size_code){
        int cmd = 0;
        cmd = code[position];
        printf("cmd = %d\n", cmd);
        switch(cmd)
        {
            case PUSH:
            {
                position++;
                int val = 0;
                val = code[position];
                fprintf(disasm_code_txt, "push %d\n", val);

                position++;

                break;
            }

            case POP:
            {
                position++;
                fprintf(disasm_code_txt, "pop\n");
                break;
            }
            case MUL:
            {
                position++;
                fprintf(disasm_code_txt, "mul\n");
                break;
            }
            case ADD:
            {
                position++;
                fprintf(disasm_code_txt, "add\n");
                break;
            }
            case SUB:
            {
                position++;
                fprintf(disasm_code_txt, "sub\n");
                break;
            }
            case HLT:
            {
                position++;
                fprintf(disasm_code_txt, "hlt\n");
                break;
            }
            case OUT:
            {
                position++;
                fprintf(disasm_code_txt, "out\n");
                break;
            }
            case IN:
            {
                position++;
                fprintf(disasm_code_txt, "in\n");
                break;
            }
            case RPUSH:
            {
                position++;
                fprintf(disasm_code_txt, "push ");

                int reg = 0;
                reg = code[position];

                if(reg == 1)
                    fprintf(disasm_code_txt, "rax\n");
                else if(reg == 2)
                    fprintf(disasm_code_txt, "rbx\n");
                else if(reg == 3)
                    fprintf(disasm_code_txt, "rcx\n");
                else if(reg ==4)
                    fprintf(disasm_code_txt, "rdx\n");
                else
                    return BAD_REG;

                position++;

                break;
            }
            case RPOP:
            {
                position++;
                fprintf(disasm_code_txt, "pop ");

                int reg = 0;
                reg = code[position];

                if(reg == 1)
                    fprintf(disasm_code_txt, "rax\n");
                else if(reg == 2)
                    fprintf(disasm_code_txt, "rbx\n");
                else if(reg == 3)
                    fprintf(disasm_code_txt, "rcx\n");
                else if(reg ==4)
                    fprintf(disasm_code_txt, "rdx\n");
                else{
                    return BAD_REG;
                }

                position++;

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

int listing(FILE* file_lst, int* code)
{
    //fprintf("%p ", )
}
