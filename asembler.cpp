//failed if do push 10

#include "header.h"

typedef enum errors{
    ALL_OK     =  0,
    NOT_MEMORY = -1,
}errors_t;


int* asembler(FILE* file_asm, FILE* code_txt, errors_t* error, struct processor* proc);
int listing(FILE* file_lst, int* code);

int main()
{
    struct processor proc = {};

    FILE* file_asm = fopen("asm.txt", "r");
    FILE* code_txt = fopen("code.txt", "w+");
    proc.code_bin = fopen("code.bin", "w+");
    printf("%p\n", file_asm);

    errors_t error;
    printf("%p\n", proc.code);
    proc.code = asembler(file_asm, code_txt, &error, &proc);

    printf("\n \n \n%s", proc.code);
    printf("\n    %d\n", proc.size_code);

    fclose(file_asm);
    fclose(code_txt);
    fclose(proc.code_bin);
    free(proc.code);

    return 0;
}

int* asembler(FILE* file_asm, FILE* code_txt, errors_t* error, struct processor* proc)
{
    char str[10];
    int len = 0;
    char sym = '\0';
    int index = 0;
    int capacity = 10;
    int* code = (int*)calloc(capacity, sizeof(int));
    printf("memory = %p\n", code);
    int* new_memory = NULL;
    int position = 0;
    int value = 0;

    while(!feof(file_asm) ){
        len = 0;
        if(capacity > 0){
            if(capacity <= index + 3){   //+ max length of comand + 1 (+ 3)
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

        if(fscanf(file_asm, "%s", str) != 1)
            break;

        if(strcmp(str, comands_names[PUSH]) == 0){
            code[index] = PUSH;
            printf("%d ", code[index]);
            index++;

            while(fscanf(file_asm, "%d", &value) != 1)
                getc(file_asm);

            code[index] = value;

            printf("%d\n", code[index]);
            fprintf(code_txt,"%04d   %02x %02x\t\t PUSH %d\n", position, PUSH, value, value);
        }

        else if(strcmp(str, comands_names[POP]) == 0){
            code[index] = POP;
            printf("%d ", code[index]);
            index++;

            fprintf(code_txt,"%04d   %02x\t\t\t POP\n", position, POP);
        }

        else if(strcmp(str, comands_names[MUL]) == 0){
            code[index] = MUL;
            index++;
            fprintf(code_txt,"%04d   %02x\t\t\t MUL\n", position, MUL);

            position++;
        }
        else if(strcmp(str, comands_names[SUB]) == 0){
            code[index] = SUB;
            index++;
            fprintf(code_txt,"%04d   %02x\t\t\t SUB\n", position, SUB);

            position++;
        }
        else if(strcmp(str, comands_names[ADD]) == 0){
            code[index] = ADD;
            index++;
            fprintf(code_txt,"%04d   %02x\t\t\t ADD\n", position, ADD);

            position++;
        }
        else if(strcmp(str, comands_names[OUT]) == 0){
            code[index] = OUT;
            index++;
            fprintf(code_txt,"%04d   %02x\t\t\t OUT\n", position, OUT);

            position++;
        }
        else if(strcmp(str, comands_names[HLT]) == 0){
            code[index] = HLT;
            index++;
            fprintf(code_txt,"%04d   %02x\t\t\t HLT\n", position, HLT);

            position++;
        }
        else if(strcmp(str, comands_names[IN]) == 0){
            code[index] = IN;
            index++;
            fprintf(code_txt,"%04d   %02x\t\t\t IN\n", position, IN);

            position++;
        }/**/

    }

    code[index] = '\0';

    proc->size_code = index;

    for(len = 0; len < index; len++)
            fprintf(code_txt, "%d" ,code[len]);

    fprintf(code_txt, "\n");

    fwrite(code, sizeof(code[0]), index, proc->code_bin);/**/

    free(code);
    code = NULL;

    return code;
}

int listing(FILE* file_lst, int* code)
{
    //fprintf("%p ", )
}
