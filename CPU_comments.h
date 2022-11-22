#ifndef CPU_comments
#define CPU_comments

#include "D:\visual_strudio\old_projects\Stack\Stack_functions.cpp"
#include "D:\visual_strudio\old_projectsStack\Onegin\Onegin_functions.cpp"

#define DUMP(i, array, count_of_symbols) dump(__PRETTY_FUNCTION__, __LINE__, i, array, count_of_symbols);
#define LBLS 50
#define DUMP_MIN dump_min(__LINE__, __PRETTY_FUNCTION__);

#define print(array) int xxx = 0;\
                    while (array[xxx] != '\0')   \
                    {   printf("\n%d <<%s>>\n", array[xxx]);      \
                        xxx++;                   \
                    }



#define CHECKING_COUNT_SYMBOLS(stk) if (stk->size < 1) \
    {                                                                         \
        printf("not enough symbols in stack %s\n", __FUNCTION__);                                \
        return 1;                                                             \
    }                                                                         \



enum registers_name {
    rax = 0,
    rbx = 1,
    rcx = 2,
    rdx = 4
};

int dump_min(int line, const char * func);
int dump(const char * func, int line, int number, char * array, int count_of_symbols);
int StackAdd(Stack * stk);
int StackSub(Stack * stk);
int StackDiv(Stack * stk);
int StackMul(Stack * stk);
char * ft_create_array_text_count_symbols(FILE * stream, const char * file_name, int * count_symbols);
int StackDup(Stack * stk);
//int writing_args_push_pop(char * retranslator, char * code, int * i, int * pc, int num);

#endif
