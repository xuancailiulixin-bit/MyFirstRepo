#include<stdio.h>
#include<stdlib.h>
#include<string.h>      //函数memcpy()需要用到的头文件

int main()
{
    //函数原型：void *memcpy(void *dest,const void *src,size_t n)，返回dest
    //dest是指向目标内存地址的指针，src是源内存地址的指针，n是要复制的字节数
    
    char str[] = "hello";           //编译器会自动计算数组大小，并且这个大小在编译时就固定下来，不能再改变
    printf("%ld\n",sizeof(str));    
    strlcpy(str,"world!",sizeof(str));      //strlcpy()复制n - 1个字符
    printf("%ld\n",sizeof(str));    
    puts(str);
    //str = "world!";相当于是改变数组的地址，数组地址不可改，可以修改内容
    /*
    如果str的数据类型是char *，那么str = "world!";是合法的。
    （编译器会把字符串字面量当成数组，相当于char *ptr = (char *)&"world!"[0];可以说字符串字面量的值就是它所在内存的首地址）
    所有的字符串字面量，无论是全局的、局域的还是静态的都会被编译器收集，然后以连续字节流的形式存储在只读存储区，并计算偏移量，给每个字符串创建标签（地址），生命周期是整个程序运行期间
    */
    
    char dest[10];
    memcpy(str,(char[]){"hello"},sizeof(str));      //复合字面量，允许直接创建没有名字的变量，可以像写字面量一样，直接写一个数组或结构体的值；语法：(类型){初始化列表}
    memcpy(dest,str,sizeof(str));       //如果复制的字节数大于sizeof(str)或sizeof(dest)，会造成未定义行为
    puts(dest);                         //输出hello
    
    //函数原型：void *memmove(void *dest,const void *src,size_t)，返回dest
    //dest是目标内存地址，src是源内存地址，n是要复制的字节数
    //memmove()允许dest和src存在覆盖，根据地址大小选择复制方向，当dest < src时，从前往后复制src；当dest > src时，从后往前复制src
    memmove(dest + 1,dest +2,3);
    puts(dest);     //预计输出"hlloo" 

    
    return 0;
}
