#include<stdio.h>
#include<string.h>                              //调用函数strlen()需要用到的头文件


int main()
{
    char *str = "hello";
    printf("%ld\n",strlen(str));                //strlen()返回值类型为size_t,aka long unsigned int，aka long unsigned int,aka是also known as 的缩写，意思是又名

    //使用strlen()不太安全，因为strlen()只是简单地从给定地址开始，一直计数直到遇到'\0'，完全不检查是否越界
    char str1[] = {'h','e','l','l','o'};        //没有'\0'
    //size_t len = strlen(str1);                //会一直读直到找到'\0',可能读到数组外
    

    //可以使用更安全的strnlen(const char*_String,size_t _MaxCount),限制最多读取的长度(_MaxCount)

    printf("%ld\n",strnlen(str1,sizeof(str1))); //家人们谁懂阿，打完这行代码整个人瞬间高潮了aaaaaaaaaaaaa；sizeof(数组变量)返回的是整个数组的字节数

    printf("%zu\n",sizeof(str));        //预计返回8
    int arr[10];
    printf("%zu\n",sizeof(arr));        //预计返回4x10=40    
    //数组是作为指针传入函数的，所以函数里sizeof(数组名)的返回值就是8,也就是指针类型的大小
    
    //字符串的比较
    //int strcmp(const char *lhs,const char *rhs);          逐个比较字符的ASCII码值，返回值是ASCII码差值
    char *str2 = "aba";     //'a' = 0x97
    char *str3 = "abA";     //'A' = 0x65
    printf("%d\n",strcmp(str2,str3));     //预计返回97-65=32
    
    //int strncmp(const char*lrs,const char *rhs,size_t count);
    //strncmp和strnlen一样，增加了一个size_t类型的参数作为长度限制
    
    char arr2[] = "hello world";
    char arr3[] = "hello";
    if(strncmp(arr2,arr3,5) == 0)
         {
            printf("这两个字符串前5个字符相同\n");
         }
    




    return 0;
}
