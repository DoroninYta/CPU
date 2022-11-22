#include "CPU_functions.cpp"

 // НУЖНО ПРОВЕРИТЬ РАБОТОСПОСОБНОСТЬ ФУНКЦИИ dup
#define DEF_CMD(name, num,...) CMD_##name = num,

enum command_number
{
    #include "CMD.h"
};

#undef DEF_CMD

/*
Команды для процессора:
in
условные переходы
je
jne
jae
jbe
ja
jb

написать программы:
1) вводит с клавиатуры 2 числа, выводит сумму

как сделаешь условные переходы
2) написать программу, которая считает факториал

если будет добавлена поддержка float (c фиксированной точностью -- 2 знака после запятой)
3*) написать программу, которая решает квадртное уравнение
*/

push 10
push 20
jae gain_than    // jump if stack.top() > stack.top()[-1]

print "20 < 10"
jmp exit

gain_than:
print "20 > 10"
exit:

struct storage {
    Elem_t Regs[10] = {0};
    Elem_t RAM[200] = {0};
};

int cpu_work(char * array, Stack * stk);
int file_info_checking(char * code, int * count_symbols);
int cpu(char * code, Stack * stk, storage * Memory);

int main()
{
    Stack stk1 = {};
    storage Memory = {};
    StackCtor(&stk1, 5) ASSERTED_OK;

    FILE * stream = fopen("code.txt", "rb"); // TODO: наверное, лучше использовать расширение .bin

    char * array = ft_create_array_text(stream, "code.txt");

    fclose(stream);
    cpu(array, &stk1, &Memory);

    for(int i = 0; i < 10; i++)
        printf("Regs <%d>\n", Memory.Regs[i]);

    int i = 0;
    while(i < 25)
        printf("RAM <%d>\n", Memory.RAM[i++]);

    return 0;
}


int cpu(char * code, Stack * stk, storage * Memory)
{
    VERIFICATOR(stk)


    int count_symbols = -1;

    file_info_checking(code, &count_symbols);

    int pc = 0;
    code += sizeof(file_info); // надо бы проверить, что sizeof(file_info) == 10

    //printf("count symbols = %d", count_symbols);
    char cmd = 0;
    int arg = -1;

    #define DEF_CMD(name, num, argv, codd)       \
    case num:                            \
        codd                            \
        pc++;                            \
        break;
    printf("count_of_symvols = %d pc = %d", count_symbols, pc);
    while (pc < count_symbols)
    {
        //printf("switch worcking");
        //printf("\n\n%d\n\n", code[pc]);
        switch (code[pc] & 0x0F)
        {
            #include "CMD.h"

            default:
                printf("uncorrect command %d", code[pc]);
        }
        //StackStatus(stk);
        //printf("\n\ncode = %d pc = %d\n", code[pc], pc);
    }
    return 0;
}

 #undef DEF_CMD
/*
int cpu_work(char * code, Stack * stk)
{
    VERIFICATOR(stk)

    int count_symbols = -3;

    file_info_checking(code, &count_symbols);
    code+=10;
    int pc = 0 ;
    printf("%d\n", count_symbols);

    while (pc < count_symbols )
    {
        //printf("\n<<<%d>>\n", pc);
        //StackStatus(stk);
        switch (code[pc]) {
            case CMD_push:
                StackPush(stk, code[pc + 1]);
                pc++;
                break;

            case CMD_add:
                StackAdd(stk);
                break;

            case CMD_sub:
                StackSub(stk);
                break;

            case CMD_mul:
                StackMul(stk);
                break;

            case CMD_div:
                StackDiv(stk);
                break;

            case CMD_jump:
                pc = code[++pc];
                break;

            case CMD_out:
                printf("StackOut  = %d\n", StackOut(stk));
                break;

            case CMD_hlt:
                printf("hlt\n");
                return Normal_exit;

            default:
                printf("uncorrect command pc =%d, FUNCTION %s\n", pc, __FUNCTION__);
            }

            pc++;
        }

    return 1;
}

*/
int file_info_checking(char * code, int * count_symbols)
{

    if (code[0] == 'C' && code[1] == 'D' && code[2] == 2)
        *count_symbols = code[6];

    else
        return 1;

    return 0;
}





