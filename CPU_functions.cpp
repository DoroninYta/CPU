#ifndef CPU_functions
#define CPU_functions


#include "CPU_comments.h"


int StackAdd(Stack * stk)
{
    VERIFICATOR(stk)

    CHECKING_COUNT_SYMBOLS(stk)

    StackPush(stk, (StackPop(stk) + StackPop(stk)));

    return 0;
}

int StackSub(Stack * stk)
{
    VERIFICATOR(stk)

    CHECKING_COUNT_SYMBOLS(stk)

    StackPush(stk, (-StackPop(stk) + StackPop(stk)));

    return 0;
}

int StackMul(Stack * stk)
{

    VERIFICATOR(stk)

    CHECKING_COUNT_SYMBOLS(stk)

    StackPush(stk, (StackPop(stk) * StackPop(stk)));

    return 0;
}

int StackDiv(Stack * stk)
{

    VERIFICATOR(stk)

    CHECKING_COUNT_SYMBOLS(stk)
    int a = StackPop(stk);
    if (a == 0)
        printf("division on 0");

    int b = StackPop(stk);
    StackPush(stk, b/a);

    return 0;
}


Elem_t StackOut(Stack * stk)
{
    VERIFICATOR(stk)

    return StackPop(stk);
}

int StackDup(Stack * stk)
{
    VERIFICATOR(stk)

    Elem_t val = StackPop(stk);

    StackPush(stk, val);
    StackPush(stk, val);

    return 0;
}


char * ft_create_array_text_count_symbols(FILE * stream, const char * file_name, int * count_symbols)
{
    assert(stream);

    int file_size = ft_file_size(file_name);

	char * array_with_text = (char *)calloc(file_size + 1, sizeof(array_with_text[0]));
	assert(array_with_text);

	int normal_size = fread(array_with_text, sizeof(array_with_text[0]), file_size, stream);	// Доставить нулевой симво

	char * string_checker = (char *)realloc(array_with_text, sizeof(string_checker[0]) * (normal_size + 1));  //
	assert(string_checker);

	array_with_text = string_checker;

	*count_symbols = normal_size;

	array_with_text[normal_size] = '\0';   //избавление от мусора при печати

	return array_with_text;
}

int dump(const char * func, int line, int number, char * array, int count_of_symbols)
{
    printf("%d function %s %d \n",number, func, line);
    int i = 0;
    while (i < count_of_symbols)
    {
        printf("%d <%x>\n", i, array[i]);
        i++;
    }
    return 0;
}

int dump_min(int line, const char * func)
{
    printf("%s line = %d\n",func, line);
    return 0;
}

#endif






