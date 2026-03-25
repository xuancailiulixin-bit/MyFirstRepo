#include<stdarg.h>      //C语言通过这个头文件提供的宏来定义变长参数函数
#include<stdio.h>

void PRINTLNF(const char *format,...)
{
    va_list ap;
    va_start(ap,format);
    while(*format)
    {
        if(*format == '%')
        {
            format = ++format;
            switch(*format)
               {
                    case 'd':
                    {
                        int val = va_arg(ap,int);
                        printf("%d",val);
                        break;
                    }
                    case 'c':
                    {
                        int val = va_arg(ap,int);       //在可变参数中，会发生默认参数提升：char、short->int,float->double
                        printf("%c",val);
                        break;
                    }
                    case 's':
                    {
                        char *val = va_arg(ap,char *);
                        printf("%s",val);
                        break;
                    }
                    case 'f':
                    {
                        double val = va_arg(ap,double);
                        printf("%f",val);
                        break;
                    }
                    default:putchar(*format);
               }

        }
        else
        {
            putchar(*format);
        }
        format += 1;
    }
    va_end(ap);
}

/*
va_list ap：定义变量，用于存储参数列表信息
va_start(ap,last)：初始化，last是最后一个固定参数
va_arg(ap,type)：获取当前参数，并移动指针到下一个参数
va_end(ap)：清理工作，结束变长参数遍历
*/

int main()
{
    PRINTLNF("整数：%d,字符：%c,字符串：%s,浮点型：%f\n",10,'A',"hello world",3.14);
    return 0;
}

