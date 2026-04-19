#define _XOPEN_SOURCE
#include<stdio.h>
#include<time.h>


//今天学习的内容是怎么把一个表示时间的字符串(例如：2026-4-18 10:40:45)格式化解析，保存到struct tm结构体里，再使用mktime()函数将struct tm转换成time_t时间戳(UTC)
//这里简单复习一下：mktime()是localtime()的逆操作，localtime()是把UTC 时间戳转换成本地时区的解析时间(struct tm结构体)，mktime()默认把传入的struct tm看作是本地时区的分解时间，哪帕传入的struct tm实际上是UTC时间


int main()
{
    /*
        如果说strftime()是按照某种格式把分解时间转换成字符串并保存到字符串缓冲区，函数strptime()就是按照某种格式解析字符串并转换成分解时间保存到struct tm结构体

        函数原型：char *strptime(const char *restrict s,const char *restrict format,struct tm *restrict tm);
        s是要解析的输入字符串，format是与s匹配的格式字符串，tm用于储存解析结果

        成功：返回最后一个被解析字符的下一个字符的指针
        失败：返回NULL

        strftime()是POSIX标准定义的函数
    */
    
    time_t now = time(NULL);
    char buffer[20];
    strftime(buffer,sizeof(buffer),"%F %T",localtime(&now));    //strftime()返回写入的字符个数(size_t类型);localtime()返回struct tm *;%F相当于%Y-%m-%d，%T相当于%H:%M:%S
    puts(buffer);
    
    struct tm parsed_time;
    strptime(buffer,"%F %T",&parsed_time);
    printf("%d\n",parsed_time.tm_year + 1900);
    printf("%d\n",parsed_time.tm_mon + 1);              //之前之所以总是输出比当前月份小一个月是因为tm_mon的范围是0-11，不是因为程序有问题
    printf("%d\n",parsed_time.tm_mday);
    printf("%d\n",parsed_time.tm_hour);
    printf("%d\n",parsed_time.tm_min);
    printf("%d\n",parsed_time.tm_sec);

    //对于不支持strptime()的平台，可以使用sscanf()函数，sscanf()可以从字符串里按照格式读取数据并储存到变量中

    char *current_time = "2026-04-19 13:20:59";
    struct tm current_time_tm;
    sscanf(current_time,"%4d-%2d-%2d %2d:%2d:%2d",&current_time_tm.tm_year,&current_time_tm.tm_mon,&current_time_tm.tm_mday,&current_time_tm.tm_hour,&current_time_tm.tm_min,&current_time_tm.tm_sec);
    current_time_tm.tm_year -= 1900;
    current_time_tm.tm_mon -= 1;
    
    time_t test_time = mktime(&current_time_tm);
    puts(ctime(&test_time));        //ctime(&test_time)相当于是asctime(localtime(&test_time)),输出一个格式固定的字符串    
    







    

    return 0;
}
