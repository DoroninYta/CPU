#include "D:\visual_strudio\old_projects\CPU\CPU_functions.cpp"


#pragma pack (push, 1)

struct file_info
{
    char signature[2];
    int version;
    int count;
};

#pragma pack (pop)

#define DEF_CMD(name,num, ...) CMD_##name = num,

enum command_number
{
    #include "CMD.h";
};

#undef DEF.CMD

int cpu_assembling(char ** array_pointers, int count_of_strings, FILE * stream, file_info * file, int * labels);
int ft_checker_push(char * array, int space, int * val, int * register_number);
int ft_check_register(char * cmd, int * register_number);
int ft_checking_jump(char ** array_pointers, int * labels, int * line, int * count_labels);
int get_args(char  * array,char * translator, int * i, int command, int space, int * labels);
int compile(char ** array_pointers, int count_of_strings, FILE * stream, file_info * file, int * labels);
int ft_checking_args(char * cmd, char * translator, int * i);
int args_put_translator(char * translator,char * array, int space, int * i, int command);



int main()
{

    int labels[LBLS] = {-1};
    char * text = NULL;
    int count_of_strings = 0;


    DUMP_MIN
    struct file_info file1 = {{'C', 'D'}, 2, 0};

    char ** array_pointers = open_work_with_file_array_pointers("command1.txt", text, &count_of_strings, '\n');
    DUMP_MIN
    FILE *   = fopen("code.txt", "wb");
    DUMP_MIN
    //printf("\n\nreturn    %d\n\n", cpu_assembling(array_pointers, count_of_strings, file, &file1, labels));

    compile(array_pointers, count_of_strings, file, &file1, labels);
    DUMP_MIN
    return 0;
}

int compile(char ** array_pointers, int count_of_strings, FILE * stream, file_info * file, int * labels)
{
    char cmd[10] = {0};
    int line  = 0;
    int i = 0;
    int count_labels = 0;

    char * translator = (char *)calloc(count_of_strings * 2, sizeof(translator[0]));

    while(line < count_of_strings)
    {
        if (ft_checking_jump(array_pointers, labels, &line, &count_labels))
            continue;

        int space = 0;
        sscanf(array_pointers[line], "%s%n", cmd, &space);

        #define DEF_CMD(name, num, arg, ...) \
            if (stricmp(cmd, #name) == 0)    \
            {               \
                translator[i++] = num;\
                if (arg) \
                    get_args(array_pointers[line], translator, &i, num, space, labels);   \
            }       \
            else


        #include "CMD.h"

        printf("ERROR %d\n", __LINE__);

        line++;
    }
     //DUMP_MIN
    file->count = i;

    DUMP(2, translator, count_of_strings * 2);
    fwrite(file, sizeof(file_info), 1, stream);
    fwrite(translator, sizeof(char), i, stream);

    fclose(stream);

    return 0;

}

 #undef DEF_CMD



/*int cpu_assembling(char ** array_pointers, int count_of_strings, FILE * stream, file_info * file, int * labels)
{
    char cmd[10] = {0};
    int line  = 0;
    int space = 0;
    int val = 0;
    int i = 0;
    int count_labels = 0;
    int ret_val = 0;
    int register_number = -1;

    DUMP_MIN
    char * translator = (char *)calloc(count_of_strings * 2, sizeof(translator[0]));
    assert(translator);
    //printf("count_strings = %d\n", count_of_strings);

    while (line < count_of_strings)
    {
        //DUMP_MIN

        if (ft_checking_jump(array_pointers, labels, &line, &count_labels))
            continue;

        sscanf(array_pointers[line], "%s%n", cmd, &space);
        //DUMP_MIN
        if (stricmp(cmd, "push") == 0)
        {
           translator[i++] = CMD_push;

           get_args(array_pointers[line], translator, &i, CMD_push, space, labels);
        }
        else if (stricmp(cmd, "jump") == 0)
        {
            translator[i++] = CMD_jump;

            get_args(array_pointers[line], translator, &i, CMD_jump, space, labels);
        }

        else if (stricmp(cmd, "add") == 0)
            translator[i++] = CMD_add;

        else if (stricmp(cmd, "sub") == 0)
            translator[i++] = CMD_sub;

        else if (stricmp(cmd, "mul") == 0)
            translator[i++] = CMD_mul;

        else if (stricmp(cmd, "div") == 0)
            translator[i++] = CMD_div;

        else if(stricmp(cmd, "dup") == 0)
            translator[i++] = CMD_dup;

        else if (stricmp(cmd, "out") == 0)
            translator[i++] = CMD_out;

        else if (stricmp(cmd, "hlt") == 0)
            translator[i++] = CMD_hlt;

        else
        {
            printf("%s", cmd);
            return -1;
        }
        line++;
    }
    //DUMP_MIN
    file->count = i;

    DUMP(2, translator, count_of_strings * 2);
    fwrite(file, sizeof(file_info), 1, stream);
    fwrite(translator, sizeof(char), i, stream);

    fclose(stream);

    return 0;

}
  */

int args_put_translator(char * translator,char * array, int space, int * i, int command)
{

    int register_number = 0;
    int val = 0;
    int code_number = -1;
    int command_code = -1;

    code_number = *i - 1;

    command_code = ft_checking_args(array + space, translator, i);
    if ( command_code == -1)
    {
        printf("cannot check args: array = <%s>", array + space);
        DUMP_MIN
        return -1;
    }

    translator[code_number] = command | command_code;

    return 0;
}




int get_args(char  * array, char * translator, int * i, int command, int space, int * labels)
{
    int register_number = 0;
    int val = 0;
    int code_number = -1;
    int command_code = -1;

    if (command == CMD_push)
    {
        args_put_translator(translator, array, space, i, CMD_push);
    }

    else if (command == CMD_pop)
    {
        args_put_translator(translator, array, space, i, CMD_pop);
    }


    else if(command == CMD_jump)
    {
            //printf("command jump\n\n\n");
            if (int ret_val = sscanf(array + space, " :%d", &val) != 0)
                translator[(*i)++] = labels[val];

            else if (ret_val = sscanf(array + space, " %d", &val) != 0)
                translator[(*i)++] = val;

            else
                printf("cant read this jump on line \n");

            return 0;
    }


    printf("uncorect command\n\n");
    return 1;

}


int ft_check_register(char * cmd, int * register_number)
{
    int i = 0;
    if (stricmp(cmd, "rax") == 0)
    {
        *register_number = 0;
        return 0;
    }
    else if (stricmp(cmd, "rbx") == 0)
    {
        *register_number = 1;
        return 0;
    }
    else if (stricmp(cmd, "rcx") == 0)
    {
        *register_number = 3;
        return 0;
    }
    else if (stricmp(cmd, "rdx") == 0)
    {
        *register_number = 3;
        return 0;
    }

    return -1;

}



int ft_checker_push(char * array, int space, int * val, int * register_number)
{

    int ret_val = -1;
    char cmd[10] = {0};
    int push_code = -1;
    if (sscanf(array + space, " %d", val) == 1)
        return (0 | 0x10);

    else if (ret_val = sscanf(array + space, " [%d]", val) == 1)
        return (0 | 0x50);

    else if (sscanf(array + space, " [%d + %s]", val, cmd) == 2)
    {
        push_code = ft_check_register(cmd, register_number);
        if (push_code != -1)
            return (push_code | 0x50);
    }

    else
    {
        sscanf(array + space, " %s", cmd);
        if(cmd[0] != '[')
        {
            push_code = ft_check_register(cmd, register_number);
            if (push_code != -1)
                return push_code;
        }

        else if (cmd[0] == '[')
        {
            cmd[4] = '\0';
            push_code = ft_check_register(cmd + 1, register_number);
            //printf("push code = %d, register = %d", push_code, *register_number);
            if (push_code >= 0)
                return (push_code | 0x40);
        }

        else
            printf("uncorrect_command cmd = <%s>", cmd);


    }
    return -2;
}


int ft_checking_jump(char ** array_pointers, int * labels, int * line, int * count_labels)
{
    int val = 0;

    if (sscanf(array_pointers[*line], "%d:", &val))
    {
        labels[val] = *line - *count_labels;
        *count_labels++;
        (*line)++;
        return 1;
    }

    return 0;
}

// TODO: ������� ����� ������ ���������� ����� �� ���� 0x10 0x60 0x70
 enum
 {
    IMM_ARG = 0x10
 };

//! cmd - only args whithout command
int ft_checking_args(char * cmd, char * translator, int * i)
{
    int val = -1;
    int register_number = -1;
    char array[20] = {0};
    int space = 0;
    DUMP_MIN
    if (sscanf(cmd, "%d", &val) == 1)
    {
        translator[(*i)++] = val;
        return IMM_ARG;//(0 | 0x10);
    }

    sscanf(cmd, "%s/n", array, & space);

    if (array[0] == '[')
    {

        if (sscanf(cmd," [%s + %d]", array, &val) == 2)
        {
            translator[(*i)++] = val;
            DUMP_MIN
            if (ft_check_register(array, &register_number) == 0)
            {
                translator[(*i)++] = register_number;
                return (0 | 0x60);
            }

            printf("uncorrect register name <%s> ", array);
            DUMP_MIN
            return -1;
        }

        else if (sscanf(cmd," [%d + %s]", &val, array) == 2)
        {
            translator[(*i)++] = val;
            //DUMP_MIN
            array[strlen(array) - 1] = '\0';
            if (ft_check_register(array, &register_number) == 0)
            {
                translator[(*i)++] = register_number;
                return (0 | 0x70);
            }

            printf("uncorrect register name <%s> ", array);
            DUMP_MIN
            return -1;

        }

        else if (sscanf(cmd, " [%d]", &val) == 1)
        {
            translator[(*i)++] = val;
            return (0 | 0x50);
        }


        else if (sscanf(cmd, " [%s]", array) == 1)
        {
            array[strlen(array) - 1] = '\0';
            if (ft_check_register(array, &register_number) == 0)
            {
                translator[(*i)++] = register_number;

                return (0 | 0x60);
            }
            printf("uncorrect register name <%s> ", array);
            DUMP_MIN
            return -1;

        }


        else
        {
            printf("--------------uncorrect command %s\n", cmd);
            //DUMP_MIN
            return -1;
        }
    }


    if (ft_check_register(array, &register_number) == 0)
    {
        translator[(*i)++] = register_number;
        return (0 | 0x20);
    }

    printf("uncorrect command for pop %s \n", array);
    return 0;
}
