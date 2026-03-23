#include<stdio.h>

int main()
{
    /*
    函数指针的定义：
    函数返回值类型 (*函数指针名)(参数类型的列表)
    */
    //int *func(int,double)等价于int *(func(int,double))，相当于是一个返回值类型是int *的函数
    //int (*func)(int,double中，func是一个函数指针，函数返回值类型是int
    //int *(*func)(int,double)中，func是一个函数指针，函数返回值类型是int *
    //int (*func[])(int,double)中，func是一个数组，数组里元素的数据类型是函数指针

    //typedef关键字可以给一个数据类型起别名
    typedef int (*Func)(int,double);    //Func就是函数指针类型的别名
    int (*(*foo)(void))[];              //foo是一个函数指针，函数返回值类型是int (*)[]，是一个指向数组的指针

    //int (*p)[];可以把(*p)看成是数组名，p是这个数组的地址，也就是指向这个数组的指针，p的数据类型是指向整型数组的指针
    //int *p[];[]的优先级高，p先与[]结合，所以p是数组，数组元素的数据类型是int *,所以加不加括号区别很大
}
