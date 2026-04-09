#include<stdio.h>
#include<string.h>      //函数strtok()需要用到的头文件
#include<stdlib.h>

//char * strtok(char *str,const char *delim)

//第一次调用strtok()传入字符串str，和指定的分隔符delim，返回第一个token
//后续调用传入NULL，继续从上次的位置分割，返回下一个token
//如果没有更多token，返回NULL

//修改原字符串：将str里的分隔符全部替换成\0，破坏原字符串
//str必须是可以修改的，不能是字符串字面量

/*
实际上函数strtok()里维护了一个静态指针，每次执行strtok，static char *static_ptr = token + strlen(token) + 1;也就是静态指针会指向分隔符后面的内容
如果后续调用传入参数NULL，相当于是把静态指针作为参数传入strtok()：继续使用上次保存的静态指针，不用新的字符串
因为只有一个静态指针，strtok()无法实现嵌套分割
*/

int main()
{
    char string[] = "C,1972;C++,1983;Java,1995;Rust,2021;Kotlin,2011";
    
    //定义一个用来存储的结构体类型
    typedef struct 
    {
        char *name;
        int year;
    
    }Language;
    
    const char *language_break = ";";
    const char *field_break = ",";

    int language_capacity = 3;      //不知道有多少种语言，先分配3个
    int language_size = 0;

    Language *languages = malloc(sizeof(Language) * language_capacity);
    
    if(!languages)
    {
        printf("内存分配失败\n");
        abort();
    }
    
    char *token = strtok(string,field_break);
    while(token)
    {
        Language language;
        language.name = token;

        token = strtok(NULL,language_break);
        if(token)
        {
            language.year = atoi(token);
        }

        if(language_size + 1 >= language_capacity)
        {
            language_capacity *= 2;
            languages = realloc(languages,sizeof(Language)*language_capacity);
            if(!languages)
            {
                abort();
            }
        }

        languages[language_size++] = language;

        token = strtok(NULL,field_break);
    }

    for(int i = 0; i < language_size; ++i)
    {
        printf("Language name:%s,year:%d\n",languages[i].name,languages[i].year);

    }

    free(languages);

    return 0;
}
