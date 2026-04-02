#include<stdio.h>

/*
    16进制数0x12345678的存储
    
    大端序：高字节存储在低地址  地址0x00:12 0x01:34 0x02:56 0x04:78
    小端序：低字节存储在低地址  地址0x00:78 0x01:56 0x02:34 0x04:12

*/

//C语言允许联合体写入一种成员，读出另一种

int Judge_Endian()
{
    union
    {
        int a;
        char c;
    }u = {.a=1};    //0x00000001 = 1 x 16^0 = 1,一个字节8位，4位二进制用一位16进制表示，一个字节用2个16进制数表示，int是4个字节，所以用4x2=8位16进制数表示
    return u.c == 1;  //返回值为1就是小端序
    /*
    字符类型变量存储的是一个整数值（字符的ASCII码）
    字符类型与整数类型比较的时候,编译器将字符类型提升为int，然后比较两个整数值
    比如：char c = '1'; '1'的ASCII码是0x31,整数值为：3 x 16^1 + 1 x 16^0 = 49

    */
}

int Judge_Endian_pv()
{
    short a = 0x1000;
    char *p = (char *)&a;
    return p[0] == 1;

}

int main()
{
    if(Judge_Endian())
        {
            printf("小端序\n");
        }else
        {
            printf("大端序\n");
        }
    if (Judge_Endian_pv())
    {
        printf("大端序\n");
    }else
    {
        printf("小端序\n");
    }
    
    return 0;
}

