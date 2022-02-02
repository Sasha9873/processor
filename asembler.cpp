#include "header.h"

typedef enum errors{
    ALL_OK     =  0,
    NOT_MEMORY = -1,
    BAD_REG    = -2,
    BAD_ENTRY  = -3,
}errors_t;


int* asembler(FILE* file_asm, FILE* code_txt, errors_t* error, struct processor* proc);
int listing(FILE* file_lst, int* code);

int main()
{
    struct processor proc = {};

    FILE* file_asm = fopen("asm.txt", "rb");
    FILE* code_txt = fopen("code.txt", "wb+");
    proc.code_bin = fopen("code.bin", "wb+");
    printf("%p\n", file_asm);

    errors_t error;
    printf("%p\n", proc.code);
    proc.code = asembler(file_asm, code_txt, &error, &proc);

    //printf("\n \n \n%n", proc.code);
    printf("\n    %ld\n", proc.size_code);

    fclose(file_asm);
    fclose(code_txt);
    fclose(proc.code_bin);
    //free(proc.code);

    return 0;
}

int* asembler(FILE* file_asm, FILE* code_txt, errors_t* error, struct processor* proc)
{
    char cmd[10];
    char reg[10];

    char str[40];
    char sym = '\0';
    int capacity = 10;
    int* code = (int*)calloc(capacity, sizeof(int));
    printf("memory = %p\n", code);
    int* new_memory = NULL;
    proc->ip = 0;
    int value = 0;
    int len = 0;
    int pop_cmd = 0;

    while(!feof(file_asm) ){
        len = 0;
        if(capacity > 0){
            if(capacity <= proc->ip + 3){   //+ max length of comand + 1 (+ 3)
                if((new_memory = (int*)realloc(code, (capacity * CHANGE + 3) * sizeof(int))) == NULL){
                    *error = NOT_MEMORY;
                    return code;
                }
                else{
                    code = new_memory;
                    capacity = capacity * CHANGE + 3;
                }
            }
        }
        else{
            capacity = 10;
            int* code = (int*)calloc(capacity, sizeof(int));
        }

        if(fgets(str, 40, file_asm) == NULL)
            break;

        char trash[10];

        int k1 = sscanf(str, "%s %d %s", cmd, &value, trash);
        int k2 = sscanf(str, "%s %s %s", cmd, reg, trash);
        printf("k1 = %d k2 = %d %s %s %s\n", k1, k2, cmd, reg, trash);


        if(strcmp(cmd, comands_names[PUSH]) == 0){

            if(k1 == 2){
                code[proc->ip] = PUSH;
                printf("%d ", code[proc->ip]);
                proc->ip++;

                code[proc->ip] = value;

                printf("%d\n", code[proc->ip]);
                fprintf(code_txt,"%04d   %02x %02x\t\t PUSH %d\n", proc->ip - 1, PUSH, value, value);
            }
            else{
                printf("reg\n");
                code[proc->ip] = RPUSH;
                printf("%d ", code[proc->ip]);
                proc->ip++;

                if(strcmp(reg, "rax") == 0)
                    code[proc->ip] = 1;
                else if(strcmp(reg, "rbx") == 0)
                    code[proc->ip] = 2;
                else if(strcmp(reg, "rcx") == 0)
                    code[proc->ip] = 3;
                else if(strcmp(reg, "rdx") == 0)
                    code[proc->ip] = 4;
                else{
                    *error = BAD_REG;
                    printf("BAD_REG");
                    return code;
                }


                printf("%d\n", code[proc->ip]);
                fprintf(code_txt,"%04d   %02x %02x\t\t RPUSH %d\n", proc->ip - 1, RPUSH, code[proc->ip], code[proc->ip]);
            }
            proc->ip++;

        }

        else if(strcmp(cmd, comands_names[POP]) == 0){
            proc->ip++;

            if(k2 == 2){
                if(strcmp(reg, "rax") == 0)
                    code[proc->ip] = 1;
                else if(strcmp(reg, "rbx") == 0)
                    code[proc->ip] = 2;
                else if(strcmp(reg, "rcx") == 0)
                    code[proc->ip] = 3;
                else if(strcmp(reg, "rdx") == 0)
                    code[proc->ip] = 4;
                else{
                    *error = BAD_REG;
                    return code;
                    }
                code[proc->ip - 1] = RPOP;

                printf("reg %d\n", code[proc->ip]);
                fprintf(code_txt,"%04d   %02x %02x\t\t RPOP %d\n", proc->ip - 1, RPOP, code[proc->ip], code[proc->ip]);

                proc->ip++;
            }
            else{
                code[proc->ip - 1] = POP;
                fprintf(code_txt,"%04d   %02x\t\t\t POP\n", proc->ip - 1, POP);
            }
            

        }

        else if(strcmp(cmd, comands_names[MUL]) == 0){
            code[proc->ip] = MUL;
            fprintf(code_txt,"%04d   %02x\t\t\t MUL\n", proc->ip, MUL);

            proc->ip++;
        }
        else if(strcmp(cmd, comands_names[SUB]) == 0){
            code[proc->ip] = SUB;
            fprintf(code_txt,"%04d   %02x\t\t\t SUB\n", proc->ip, SUB);

            proc->ip++;
        }
        else if(strcmp(cmd, comands_names[ADD]) == 0){
            code[proc->ip] = ADD;
            fprintf(code_txt,"%04d   %02x\t\t\t ADD\n", proc->ip, ADD);

            proc->ip++;
        }
        else if(strcmp(cmd, comands_names[OUT]) == 0){
            code[proc->ip] = OUT;
            fprintf(code_txt,"%04d   %02x\t\t\t OUT\n", proc->ip, OUT);

            proc->ip++;
        }
        else if(strcmp(cmd, comands_names[HLT]) == 0){
            code[proc->ip] = HLT;
            fprintf(code_txt,"%04d   %02x\t\t\t HLT\n", proc->ip, HLT);

            proc->ip++;
        }
        else if(strcmp(cmd, comands_names[IN]) == 0){
            code[proc->ip] = IN;
            fprintf(code_txt,"%04d   %02x\t\t\t IN\n", proc->ip, IN);

            proc->ip++;
        }

    }

    code[proc->ip] = '\0';

    proc->size_code = proc->ip;

    for(len = 0; len < proc->ip; len++)
            fprintf(code_txt, "%d" ,code[len]);

    fprintf(code_txt, "\n");

    fwrite(code, sizeof(code[0]), proc->ip, proc->code_bin);

    free(code);
    code = NULL;/**/

    return code;

}

/*int listing(FILE* file_lst, int* code)
{
    //fprintf("%p ", )
}*/
