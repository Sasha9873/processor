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
    int* new_memory = NULL;
    int position = 0;

    while( !feof(file_asm) ){
        len = 0;
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

        while((sym = getc(file_asm)) == ' ' || sym == '\n')
            ;

        if(sym == EOF)
            break;

        str[len] = sym;
        len++;

        while((sym = getc(file_asm)) != ' ' && (sym) != '\n'){
            str[len] = sym;
            len++;
        }
        str[len] = '\0';

        if(strcmp(str, comands_names[PUSH]) == 0){
            code[index] = PUSH;
            printf("%d ", code[index]);
            index++;

            while((sym = getc(file_asm)) == ' ' || sym == '\n')
                ;

            if(sym == '-'){
                len = 0;
                while((sym = getc(file_asm)) != ' ' && (sym) != '\n'){
                    str[len] = sym;
                    len++;
                }
                str[len] = '\0';
                code[index] = -atoi(str);
                fprintf(code_txt,"%04d   %02x %02x   PUSH %d\n", position, PUSH, -atoi(str), -atoi(str));
            }
            else{
                len = 0;
                str[len] = sym;
                printf("sym = %d ", sym - '0');
                len++;
                while((sym = getc(file_asm)) != ' ' && (sym) != '\n'){
                    str[len] = sym;
                    len++;
                }

                str[len] = '\0';
                code[index] = atoi(str);
                printf("%d\n", code[index]);
                fprintf(code_txt,"%04d   %02x %02x\t\t PUSH %d\n", position, PUSH, atoi(str), atoi(str));
            }
            index++;
            for(len = 0; len < index; len++)
                printf(":%d " ,code[len]);
            printf("\n");

            position +=2;
        }

        else if(strcmp(str, comands_names[POP]) == 0){
            code[index] = POP;
            index++;

            while((sym = getc(file_asm)) == ' ' || sym == '\n')
                ;

            if(sym == '-'){
                len = 0;
                while((sym = getc(file_asm)) != ' ' && (sym) != '\n'){
                    str[len] = sym;
                    len++;
                }
                str[len] = '\0';
                code[index] = -atoi(str);
                fprintf(code_txt,"%04d   %02x %02x   POP  %d\n", position, POP, -atoi(str), -atoi(str));
            }

            else{
                len = 0;
                str[len] = sym;
                printf("sym = %d ", sym - '0');
                len++;
                while((sym = getc(file_asm)) != ' ' && (sym) != '\n'){
                    str[len] = sym;
                    len++;
                }

                str[len] = '\0';
                code[index] = atoi(str);
                printf("%d\n", code[len]);
                fprintf(code_txt,"%04d   %02x %02x\t\t POP  %d\n", position, POP, atoi(str), atoi(str));
            }
            index++;

            position +=2;
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
        }/**/

    }

    code[index] = '\0';

    proc->size_code = index;

    for(len = 0; len < index; len++)
            fprintf(code_txt, "%d" ,code[len]);

    fprintf(code_txt, "\n");

    fwrite(code, sizeof(code[0]), index, proc->code_bin);/**/

    return code;
}

int listing(FILE* file_lst, int* code)
{
    //fprintf("%p ", )
}
