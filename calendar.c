#include<stdio.h>
#include<time.h>
#include"time_utils.h"

int main()
{
    time_t current_time = time(NULL);
    struct tm *calendar_time = localtime(&current_time);
    printf("年份:%d\n",calendar_time->tm_year + 1900);
    printf("月份:%d\n",calendar_time->tm_mon + 1);
    printf("一个月的第几天:%d\n",calendar_time->tm_mday);

    printf("小时:%d\n",calendar_time->tm_hour);
    printf("分钟:%d\n",calendar_time->tm_min);
    printf("秒:%d\n",calendar_time->tm_sec);


    /*
        函数原型：struct tm *localtime(const time_t *timer);
        功能是将一个时间戳(time_t类型)转换成本地时间(struct tm结构体)
        参数timer是指向time_t类型变量的指针，通常是time()函数返回的时间戳
        成功时返回一个指向struct tm结构体的指针，失败返回NULL
        localtime()把时间戳转换成当前时区的分解时间(struct tm结构体)，追随系统的时区设置   
    */
    
    /*
        函数原型：time_t mktime(struct tm *tm);
        将本地时区的分解时间(struct tm)转换为日历时间(time_t时间戳)
        虽然time_t时间戳表示的是从纪元开始的秒数，之所以称为日历时间是因为秒数可以转换成年、月、日、时、分、秒等日历形式的时间，二来是与另一种时间概念——clock_t处理器时间区分
    
        mktime()把struct tm结构体转换成time_t,相当于是localtime()的逆操作
        mktime()还会自动调整struct tm里超出范围的字段，比如tm_sec = 70,超出了60的最大范围会自动调整：tm_sec -= 60;tm_min += 1;
        而且还会计算并填充tm_wday(星期几)和tm_yday(年内天数)，所以并不要求填满struct tm结构体里的所有成员，mktime()执行转换主要依赖以下成员：
        tm_sec、tm_min、tm_hour、tm_mday、tm_mon、tm_year这些是必须的，是程序执行的最低限度
        其他成员不是必须的，像tm_wday和tm_yday，即使在结构体里提供了值，mktime()也会忽视它们，并根据必须成员信息计算正确的tm_wday和tm_yday值
        
    
    */
    
    time_t current_time2 = mktime(calendar_time);
    printf("%ld\n",current_time2);
    
    //函数原型：struct tm *gmtime(const time_t *);
    //gmtime()与localtime()的区别就是，gmtime()将time_t时间戳转换成UTC的分解时间(struct tm)
    struct tm *gmt = gmtime(&current_time);
    printf("年份:%d\n",gmt->tm_year + 1900);
    printf("月份:%d\n",gmt->tm_mon + 1);
    printf("一个月的第几天:%d\n",gmt->tm_mday);
    printf("小时:%d\n",gmt->tm_hour);        //会发现与UTC时间差了8个小时
    printf("分钟:%d\n",gmt->tm_min);
    printf("秒:%d\n",gmt->tm_sec);








    return 0;
}
