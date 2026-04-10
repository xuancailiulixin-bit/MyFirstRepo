#include<stdio.h>
#include<string.h>

//函数原型：char * strcat(char *dest,const char *source)，返回dest
/*
将源字符串追加到目标字符串的末尾，它会找到目标字符串的结束符'\0'的位置，并从该位置开始复制源字符串的每一个字符，包括源字符串里的'\0'，所以目标字符串必须有'\0'作为结尾
目标字符串必须有足够的空间容纳拼接后的结果，所以必须是可以修改的，不能是字符串字面量
*/

//函数原型：char * strcpy(char *dest,const char *src)，返回dest
/*
从源字符串的首字符开始复制，一直复制直到遇到'\0'
会覆盖目标字符串原有的内容
目标字符串必须有足够的空间，否则会造成溢出
源字符串必须以'\0'结尾，否则会一直复制，直到遇到'\0'

strlen()返回的是字符串中字符的个数，不包含结尾的'\0'；dest是字符数组，sizeof(dest)返回的是这个数组的大小

strncpy()更安全，可以预设复制的字符数量n，但是如果n大于目标缓冲区大小就会发生溢出，
因为无论strlen(src)有多大，strncpy都会复制n个字符到目标缓冲区，哪怕目标缓冲区的大小不足以缓存这么多字符
当strlen(src) < n，会在复制完src后继续写入'\0'，直到写满n个字符；当strlen(src) > n，strncpy()只会复制src的前n个字符，并且不会在后面添加'\0'

char dest[5];
char src[] = "hello world!";
strncpy(dest,src,4);        //dest = {'h','e','l','l'}，不会在结尾添加'\0'

*/
int main()
{   
    char dest[20] = "hello ";
    char src[] = "world!";
    puts(strcat(dest,src));
    
    char str_dest[10];      //strcpy()和strncpy()都会覆盖目标字符串原有内容
    char str_src[] = "hello world!";
    strncpy(str_dest,str_src,sizeof(str_dest) - 1);     //sizeof(str_dest) - 1，因为要预留一个位置给'\0'，所以-1
    str_dest[sizeof(str_dest) - 1] = '\0';      //手动添加结束符'\0'
    puts(str_dest);         //预计输出：hello wor
    
    //strlcpy()是BSD/Linux系统的扩展函数，不是C标准库函数
    /*
    函数原型：size_t strlcpy(char * restrict dest,const char * restrict src,size_t size),返回值是strlen(src)
    restrict一种编译器扩展关键字，用于告诉编译器这个指针是访问数据的唯一方式，没有其他指针指向同一块内存
    src所指向的源字符串必须以'\0'结尾
    size是dest指向的目标缓冲区的总大小，建议使用sizeof(dest)作为size的大小，
    因为如果size > 0，strlcpy()会从src复制最多size - 1个字符到dest，并且总是会把dest[sizeof(dest) - 1]的字符设置成'\0'，以确保是一个以'\0'结尾的字符串
    如果size = 0，函数不会执行任何复制，直接返回strlen(src)
    strlcpy()不会像strncpy()那样用'\0'填充，也就是说如果size = sizeof(dest) && size > strlen(src)，那么dest[0]到dest[strlen(src)]之外的部分都会保持原样

    */
    char text[22] = "hello "; 
    char name[] = "xuancailiulixin";
    strlcpy(dest,name,sizeof(dest));
    puts(dest);
    puts(strcat(text,name));


    return 0;
}
