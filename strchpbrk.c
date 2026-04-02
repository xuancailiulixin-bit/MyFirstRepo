#include<stdio.h>
#include<string.h>      //调用strchr()和strpbrk()用到的头文件


int main()
{
    //char *strpbrk(const char *s,const char *accept)
    //在字符串s中查找第一个出现在accept字符串中的任意字符
    //如果找到，返回指向该字符的指针；如果没找到，返回NULL
    char str[] = "hello,nihao!";
    char *remain;
    remain = strpbrk(str,",!");
    if(remain != NULL)      //如果没找到，strpbrk的返回值是NULL
    {
        printf("找到字符：%c\n",*remain);
        printf("找到位置：%ld\n",remain-str);
        printf("剩余字符串：%s\n",remain);
    }
    //strpbrk()就是查找字符串多个字符中的任意一个，并返回其第一次出现的位置


    //strchr()查找单个字符，返回其第一次出现的位置
    char *str1 = "hello";
    remain = strchr(str1,'l');
    printf("%ld\n",remain-str1);
    printf("%s\n",remain);

    //strrchr()从后往前查找单个字符，返回其第一次出现的位置
    remain = strrchr(str1,'l');
    printf("%ld\n",remain-str1);
    printf("%s\n",remain);


    //查找字串strstr(const char *_Str,const char *_SubStr)
    //返回子串第一次出现的位置
    remain = strstr(str,"nihao");
    printf("%ld\n",remain-str);
    printf("%s\n",remain);
    return 0;
}
