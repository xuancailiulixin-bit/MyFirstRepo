#include<stdio.h>
#include<stdlib.h>

//atoi()把字符串转换成整型，如果字符串开头没有数字就会返回0,只能转化开头数字，中间隔着字母之后的数字不会被转换

//long int strtol(const char *nptr,char **endptr,int base)
//nptr是要被转换的字符串（输入），endptr是转换结束后的位置，base是进制，被转换的字符以这种进制识别，并转换成long int类型
//参数可以是：const char *,char *,char arr[],字符串字面量，单个字符变量的地址

//errno需要包含头文件errno.h
//errno是一个全局变量（实际上是宏）
//errno是系统维护的一个全局错误码，函数执行出错时会设置errno为具体对应的错误码
//函数执行成功时，errno不会被清零，值会保持不变，所以需要调用前手动清零
//不同的错误码代表不同的错误类型

void FNIS(const char *str)      //found number in string
{
    char *endptr;
    const char *nptr = str;
    while(*nptr)
    {
        long value = strtol(nptr,&endptr,10);
        if(endptr == nptr)
        {
            ++nptr;   
        }else
        {
            printf("找到数字：%ld\n",value);
            nptr = endptr;
        }
    }
}


int main()
{
    char str[] = "hello2026";
    const char *str1 = "2026hi";
    //char *str = {'h','e','l','l','o','\0'};   不能这样初始化
    //char *str = "hello";                      只读
    //char *str = (char[]){"hello"};            可修改，等价于：char *str = (char[]){'h','e','l','l','o','\0'};
    //char arr[] = "hello"; char *str = arr;    可修改
    //char *str = (char *)malloc(6); strcpy(str,"hello");   可修改

    FNIS(str);
    FNIS(str1);
    
    char a = '1';
    char b = 'a';
    char *p = &a;
    int c = atoi(p);
    printf("%d\n",c);
    printf("%d\n",atoi(&b));



    return 0;

}

