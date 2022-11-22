#include "CPU_functions.cpp"

#define DEF_CMD(name, num,...) CMD_##name = num,

enum command_number
{
    #include "CMD.h"
};
#undef DEF_CMD

//int writing_args_push_pop(char * retranslator, char * code, int * i, int * pc, int num);
//int disassembling(char * code, int count_symbols, FILE * stream_write);
int file_info_checking(char * code, int * count_symbols);
int sssprintf(char * array, const char * text, int * pc);
int writing_args(char * retranslator, char * code, int * pc, int * i, int command);
int ft_disassembling(char * code, FILE * stream);




int main()
{
    DUMP_MIN
    FILE * stream_read = fopen("code.txt", "rb");
    FILE * stream_write = fopen("disassembling.txt", "w");
    assert(stream_write);
    int count_symbols = 0;
    char * text = ft_create_array_text_count_symbols(stream_read, "code.txt", &count_symbols);
    //char * retranslator = (char *)calloc(count_symbols * 3, sizeof(retranslator[0]));
    DUMP_MIN
    ft_disassembling(text, stream_write);
    DUMP_MIN
    return 0;
}

int  ft_disassembling(char * code, FILE * stream)
{
    int count_of_symbols = 0;

    file_info_checking(code, &count_of_symbols);

    code+=10;
    printf("cod = %x\n\n", code[0]);
    int pc = 0;
    int i = 0;
    int count_strings = 0;
    int array_with_numbres[count_of_symbols];
    printf("count of symbols = %d\n", count_of_symbols);
    char * retranslator = (char *)calloc(count_of_symbols * 4, sizeof(char));
    //char retranslator[count_of_symbols * 3] ;
    //assert(retranslator);
    DUMP_MIN
    #define DEF_CMD(name, num, argv, ...)             \
        case num:                           \
            printf(" name = <%s> num = %d\n", #name, num);     \
            sssprintf(retranslator, #name , &i);            \
            sssprintf(retranslator, " ", &i);                                            \
            if (argv)                                 \
                writing_args(retranslator, code, &i, &pc, num);\
            count_strings++;                                     \
            sssprintf(retranslator, "\n", &i);                   \
            break;
    DUMP_MIN
    while (pc < count_of_symbols)
    {

        switch (code[pc] & 0xF)
        {

                #include "CMD.h"

            default:
                printf("uncorrect command in switch, %d", code[pc]);
                DUMP_MIN
        }
    }

    #undef DEF_CMD
    fwrite(retranslator, sizeof(retranslator[0]), i, stream);
    free(retranslator);
    DUMP_MIN
    return 0;
}

/*int ft_writing_text_in_file(char * retranslator,int * array_with_numbers, FILE * stream, int count_strings)
{


    while()
                            */

char *  regs_name(int arg)
{
    #define ret(name, num)   \
        if (arg == num)      \
            return #name;

    ret(rax, 0);
    ret(rbx, 1);
    ret(rcx, 2);
    ret(rdx, 3);

    printf("unccorrect register %d", arg);
    DUMP_MIN

    return NULL;
}


int writing_args_push_pop(char * retranslator, char * code, int * i, int * pc)
{
    int plus = 0;
    int pc_copy = *pc;
    int i_copy = *i;
    printf("code = <%x>\n",  code[pc_copy]);
    (*pc)+=1;
    if ((code[pc_copy] & 0x40) == 0x40)
    {
        DUMP_MIN
        retranslator[(*i)++] = '[';

        if ((code[pc_copy] & 0x10) == 0x10)
        {
        int delta = sprintf(&retranslator[*i], "%d", (int)code[(*pc)++]);
        *i += delta;
        plus = 1;
        }


        if ((code[pc_copy] & 0x20) == 0x20)
        {
            if (plus)
                sssprintf(retranslator, " + ", i);
            sssprintf(retranslator, regs_name(code[(*pc)++] & 0x0F), i);

        }
        retranslator[(*i)++] = ']';

    }

    else if ((code[pc_copy] & 0x10) == 0x10)
    {
        int delta = sprintf(&retranslator[*i], "%d", (int)code[(*pc)++]);
        *i += delta;
    }

    else if ((code[pc_copy] & 0x20) == 0x20)
        sssprintf(retranslator, regs_name(code[(*pc)++] & 0x0F), i);

    else
    {
        printf("error command code for %s  pc_copy = %d   ", code[pc_copy], pc_copy);
        DUMP_MIN
    }

    printf("end code %x\n",  code[pc_copy]);
    return 0;
}

int writing_args(char * retranslator, char * code, int * pc, int * i, int command)
{
    if (command == CMD_push || command == CMD_pop)
       writing_args_push_pop(retranslator, code, pc, i);

    else if (command == CMD_jump)
        retranslator[(*i)++] = code[(*pc)++];

    else
    {
        printf("error unknown command %d   ", command);
        DUMP_MIN
    }
    return 0;
}


int file_info_checking(char * code, int * count_symbols)
{

    if (code[0] == 'C' && code[1] == 'D' && code[2] == 2)
        *count_symbols = code[6];

    else
        return 1;

    return 0;
}

int sssprintf(char * array, const char * text, int * pc)
{
    int i = 0;
    while (text[i] != '\0')
        array[(*pc)++] = text[i++];

    return 0;
}

 /*

int disassembling(char * code, int count_symbols, FILE * stream_write)
{
    int pc = 0;

    while (pc < count_symbols)
    {
        switch (code[pc])
        {
            case CMD_PUSH:
                fprintf(stream_write, "push %d\n", code[++pc]);
                break;

            case CMD_ADD:
                fprintf(stream_write, "add\n");
                break;

            case CMD_SUB:
                fprintf(stream_write, "sub\n");
                break;

            case CMD_MUL:
                fprintf(stream_write, "mul\n");
                break;

            case CMD_DIV:
                fprintf(stream_write, "div\n");
                break;

            case CMD_OUT:
                fprintf(stream_write, "out\n");
                break;

            case CMD_HLT:

                fprintf(stream_write, "hlt\n");
                return 0;

            default:
                printf("uncorrect command pc =%d, FUNCTION %s", pc, __FUNCTION__);
            }

            pc++;
        }
    return -1;
}
*/
