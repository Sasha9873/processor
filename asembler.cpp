#include "header.h"

typedef enum errors{
    ALL_OK     =  0,
    NOT_MEMORY = -1,
}errors_t;


int* asembler(FILE* file_asm, FILE* code_txt, FILE* file_lst, errors_t* error);
int listing(FILE* file_lst, int* code);

int main()
{
    processor proc = {};

    FILE* file_asm = fopen("asm.txt", "r");
    FILE* code_txt = fopen("code", "w+");
    FILE* file_lst = fopen("file.lst", "w+");
    printf("%p\n", file_asm);

    errors_t error;
    printf("%p\n", proc.code);
    proc.code = asembler(file_asm, code_txt, file_lst, &error);

    printf("%s", proc.code);

    fclose(file_asm);
    fclose(code_txt);

    return 0;
}

int* asembler(FILE* file_asm, FILE* code_txt, FILE* file_lst, errors_t* error)
{
    char str[10];
    int len = 0;
    char sym = '\0';
    int index = 0;
    int capacity = 10;
    int* code = (int*)calloc(capacity, sizeof(int));
    int* new_memory = NULL;

    while( !feof(file_asm) ){
        len = 0;

        if(capacity <= index + 2){   //+ max length of comand (+ 2)
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
            }
            index++;
        for(len = 0; len < index; len++)
            printf(":%d " ,code[len]);
        printf("\n");
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
            }
            index++;
        }

        else if(strcmp(str, comands_names[MUL]) == 0){
            code[index] = MUL;
            index++;
        }
        else if(strcmp(str, comands_names[SUB]) == 0){
            code[index] = SUB;
            index++;
        }
        else if(strcmp(str, comands_names[ADD]) == 0){
            code[index] = ADD;
            index++;
        }
        else if(strcmp(str, comands_names[OUT]) == 0){
            code[index] = OUT;
            index++;
        }
        else if(strcmp(str, comands_names[HLT]) == 0){
            code[index] = HLT;
            index++;
        }

        /*while((sym = getc(file_asm)) == ' ' || sym == '\n')
            ;

        if(sym == EOF)
            break;

        str[len] = sym;
        len = 1;

        while((sym = getc(file_asm)) != ' ' && (sym) != '\n'){
            str[len] = sym;
            len++;
        }
        str[len] = '\0';
        //printf("s = %s push = %s %d\n", str, comands_names[PUSH], strcmp(str, comands_names[PUSH]));
        if(strcmp(str, comands_names[PUSH]) == 0){
            sym = getc(file_asm);
            if(sym == '-')
                fprintf(code_txt,"%d -%d\n", PUSH, getc(file_asm) - '0');
            else
                fprintf(code_txt,"%d %d\n", PUSH, sym - '0');
        }
        else if(strcmp(str, comands_names[POP]) == 0){
            sym = getc(file_asm);
            if(sym == '-')
                fprintf(code_txt,"%d -%d\n", POP, getc(file_asm) - '0');
            else
                fprintf(code_txt,"%d %d\n", POP, sym - '0');
        }
        else if(strcmp(str, comands_names[MUL]) == 0){
            fprintf(code_txt,"%d\n", MUL);
        }
        else if(strcmp(str, comands_names[SUB]) == 0){
            fprintf(code_txt,"%d\n", SUB);
        }
        else if(strcmp(str, comands_names[ADD]) == 0){
            fprintf(code_txt,"%d\n", ADD);
        }
        else if(strcmp(str, comands_names[OUT]) == 0){
            fprintf(code_txt,"%d\n", OUT);
        }
        else if(strcmp(str, comands_names[HLT]) == 0){
            fprintf(code_txt,"%d\n", HLT);
        }*/

    }

    code[index] = '\0';


    for(len = 0; len <= index; len++)
            fprintf(code_txt, "%d" ,code[len]);

    fprintf(code_txt, "\n");

    /*fwrite(code, sizeof(code[0]), index, code_txt);*/

    return code;
}

int listing(FILE* file_lst, int* code)
{
    //fprintf("%p ", )
}
