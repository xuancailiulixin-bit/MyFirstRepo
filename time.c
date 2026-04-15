#include<time.h>
#include<stdio.h>

#include"time_utils.h"      //包含为了能够获取毫秒级精度而创建的头文件，里面其实是一个函数，使用条件编译来调用不同平台时间库扩展函数

//time_t是一种数据类型，这种数据类型的变量用来表示“从1970年1月1日0时起的秒数”，通常是long int 或long long int（32位：long；64位：long long）
//使用time_t可以明确语义，告诉阅读者该变量表示时间值，不是普通的整数
//旧版系统long类型是4个字节，也就是32位，能表示的时间只能到2038年；如果标准规定直接使用long，那么之后想改成long long就需要修改所有代码，而使用time_t就只需要把typedef long time_t修改成typedef long long time_t就可以了

int main()
{
    printf("%zu\n",sizeof(time_t));     //%zu是专用来格式化size_t类型值
    
    /*
    struct tm结构体
    struct tm
    {
        int tm_sec;
        int tm_min;
        int tm_hour;
        int tm_mday;    //一个月里的第几天 - [1,31]
        int tm_mon;
        int tm_year;    //years since 1900；比如2020年的值是120 
        int tm_wday;    //星期几 - [0,6]
        int tm_yday;    //一年中的第几天 - [0,365]
        int tm_isdst;   //夏令时标志，有三个值[0,1,-1]，分别表示不是夏令时(标准时间)，是夏令时，让系统自动确定(未知）
                        //中国不使用夏令时，所以这里先略过
    };
    */
    
    /*
    函数原型：time_t time(time_t *timer);返回值是从纪元（1970-01-01 00:00:00 UTC）到当前时刻的秒数，返回值总是UTC时间，不受时区影响
    两种使用方法：
    1.通过返回值获取：time_t now = time(NULL);
    2.通过参数获取：time_t now; time(&now); 时间值存入now
    
    */

    time_t now = time(NULL);
    printf("%ld\n",now);        //返回值是秒数

    time(&now);
    printf("%ld\n",now);        //会发现返回值与上面的结果相同，这是因为返回值是秒数，不够精确，除了秒之外还有毫秒、微秒、纳秒。1s=1000ms,1ms=1000微秒,1微秒=1000ns

    //为了获取精度更高的时间，我们定义一个函数来获取毫秒，并且能够屏蔽不同系统的差异，我们定义一个头文件：time_utils.h，utils是utilities的缩写，意为实用工具/程序

    printf("%lld\n",TimeInMillisecond());












    return 0;
}


