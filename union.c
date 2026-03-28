#include<stdio.h>
//空指针的妙用：offsetof(s,m) ((size_t)&(((s *)0)->m))

#define INT_operator 1
#define STR_operator 2


    typedef union Operator
    {
        int int_operator;
        char *str_operator;

    }OPERATOR;          //联合体和结构体的定义方式很像，但是联合体里的成员共享一个内存空间，所以联合体的大小就是最大成员的大小
    
    typedef struct Instruction
    {
        int operator;
        OPERATOR operand;

    }INSTRUCTION;

void process(INSTRUCTION *ins)
{
    switch(ins->operator)
    {
        case INT_operator : 
        {
            printf("%d\n",ins->operand.int_operator);
            break;
        }
        case STR_operator :
        {
            printf("%s\n",ins->operand.str_operator);
            break;
        }
        default :
        fprintf(stderr,"Unsupported operator:%d\n",ins->operator);      //暂时还不知道什么意思

    }

}

int main()
{
    INSTRUCTION instru = {.operator=STR_operator,.operand={.str_operator="hello,world!"}};      //同时初始化结构体和里面的联合体
    process(&instru);
    return 0;
}
