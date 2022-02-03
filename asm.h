typedef enum errors{
    ALL_OK     =  0,
    NOT_MEMORY = -1,
    BAD_REG    = -2,
    BAD_ENTRY  = -3,
}errors_t;


int* asembler(FILE* file_asm, FILE* code_txt, errors_t* error, struct processor* proc);
int listing(FILE* file_lst, int* code);

/**
 * returns 0          if it is a number
 *         1, 2, 3, 4 if it is a register rax, rbx, rcx, rdx respectively 
 *        -1          if it is a fault.
 */
int what_arg(int k_str_num, int k_strs);

/**
 * 
 */
int arg(int* code, int k_str_num, int k_strs, FILE* code_txt, errors_t* error, struct processor* proc, char* name, int num);


#define DEFCMD(name, num, arg, ...)\
if (stricmp(cmd, #name) == 0){\
    code[proc->ip] = num;\
    if(arg){\
        if(arg(code, k1, k2, code_txt, error, proc, name, num)){\
            *error = BAD_ENTRY;\
            return code;\
        }\

        int arg_is = what_arg(k_str_num, k_strs);\

        if(arg_is == -1){\
            *error = BAD_ENTRY;\
            return code;\
        }\
        else if(arg_is == 0){
            proc->ip++;
            code[proc->ip] = value;
            
            printf("%d\n", code[proc->ip]);

            fprintf(code_txt,"%04d   %02x %02x\t\t ", proc->ip - 1, num, value);
            fprintf(code_txt,"%s %d\n", name, value);
        }
        else{
            proc->ip++;

            printf("%d ", code[proc->ip]);

            code[proc->ip] = arg_is;
            
            printf("%d\n", code[proc->ip]);

            fprintf(code_txt,"%04d   %02x ", proc->ip - 1, num);
            fprintf(code_txt,"%02x\t\t %s ", code[proc->ip], name);
            fprintf(code_txt,"%d\n", code[proc->ip]);

        }

    }
    else if(k2 != 1){
        *error = BAD_ENTRY;
        return code;
    }

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

