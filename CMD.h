DEF_CMD(add, 2 ,0, StackAdd(stk);)
DEF_CMD(sub, 3, 0, StackSub(stk);)
DEF_CMD(mul, 4, 0, StackMul(stk);)
DEF_CMD(div, 5, 0, StackDiv(stk);)
DEF_CMD(out, 6, 0, printf("%d\n", StackPop(stk));)


DEF_CMD(hlt, 0, 0, return 0;)


DEF_CMD(push, 1, 1,
{
    arg = 0;
    cmd = code[pc];

    if ((cmd & 0x10) == 0x10)
        arg+= code[++pc];

    if ((cmd & 0x20) == 0x20)
        arg+= Memory->Regs[code[++pc]];

    if ((cmd & 0x40) == 0x40)
        arg = Memory->RAM[arg];

    StackPush(stk, arg);
})


DEF_CMD(jump, 7, 1, pc = code[++pc];)
DEF_CMD(dup, 8, 0, StackDup(stk);)
DEF_CMD(pop, 9, 1,
{
    arg = 0;
    cmd = code[pc];
    printf("POP worcking!!!\n\n\n\n");
    if ((cmd & 0x40) == 0x40)
    {
        if ((cmd & 0x10) == 0x10)
            arg+= code[++pc];
        if ((cmd & 0x20) == 0x20)
            arg+= Memory->Regs[++pc];

         Memory->RAM[arg] = StackPop(stk);
    }

    else if ((cmd & 0x20) == 0x20)
        Memory->Regs[code[++pc]] = StackPop(stk);

    else
    {
        printf("uncorrect command for pop \n");
        printf("<%x>    ", cmd);
        DUMP_MIN
    }})
