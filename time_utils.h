#ifndef TIME_UTILS
#define TIME_UTILS

//从这里开始到#endif之前的内容并不是对TIME_UTILS的替换，而是条件编译

//不同平台有各自的时间库扩展
#if defined(_WIN32)
#include<sys/timeb.h>
#elif defined(__unix__)
#include<sys/time.h>
#endif

typedef long long long_time_t;      //typedef后面需要加分号

long_time_t TimeInMillisecond(void)     //millisecond就是毫秒的意思
{
    #if defined(_WIN32)
        struct timeb time_buffer;
        /*
            struct timeb
            {
                long time;          //自纪元(1970-1-1 00:00:00 UTC)以来的秒数，和time()的返回值一样
                short millitm;      //秒后面的小数部分，单位是毫秒，这是它比time()更精确的关键
                short timezone;     //本地时区相对于UTC的差异，单位是分钟
                short dstflag;      //夏令时标志，0表示当前正在使用夏令时 
            };

        */
        ftime(&time_buffer);    //接收一个struct timeb *类型的变量(指向struct timeb结构体的指针)，然后把当前时间填进去
        #if defined(_USE_32BIT_TIME_T)      //默认情况下，time成员是64位的，但如果定义了_USE_32BIT_TIME_T宏，timeb会强制降级为32位版本，time成员就是一个32位的long类型
            return time_buffer.time * 1000L + time_buffer.millitm;     //1000L是long类型的字面量的写法
        #else
            return time_buffer.time * 1000LL + time_buffer.millitm;     //1000LL是long long类型的字面量的写法
        #endif
    #elif defined(__unix__)
        struct timeval time_value;
        /*
            struct timeval
            {
                time_t tv_sec;          //秒数，自纪元(1970-1-1 00:00:00 UTC)以来的秒数，和time()的返回值一样
                suseconds_t tv_usec;    //微秒(范围0-999,999)，suseconds_t是long的别名

            };


        */
        gettimeofday(&time_value,NULL); 
        /*
            函数原型：int gettimeofday(struct timeval *restrict tv,struct timezone *_Nullable restrict tz);
                tv是指向struct timeval类型变量的指针，函数会将获取到的时间写入这里，
                tz用于设置时区。这个参数已经废弃，在调用时请务必将其设置为NULL
                成功时返回0,失败时返回-1,并设置相应的errno

            实际上gettimeofday()这个函数已经过时了，更现代的函数是clock_gettime()配合struct timespec结构体，其结构体成员为tv_sec和tv_nsec，支持纳秒级精度  
            函数clock_gettime()并不是C标准库函数，而是POSIX(Unix_like系统)标准，平台受限(Linux、macOS等POSIX系统)但是用途广泛
            C11标准提供的函数timespec_get()需要在编译时使用支持C11或更高版本的编译器以获取函数声明(函数原型)
            函数原型：int timespec_get(struct timespec *ts,int base);
                ts是指向struct timespec类型的指针，用于存储获取到的时间
                base是时间基准，目前只支持TIME_UTC(表示获取UTC时间)
                成功时返回base的值(TIME_UTC)，失败返回0；TIME_UTC并不是一个时间辍，而是一个固定的整数值

        */
        return time_value.tv_sec * 1000LL + time_value.tv_usec / 1000;
        
    #elif defined(__STDC__) && __STDC_VERSION__ == 201112L      //如果既不是win也不是unix，但是只要支持C11，就使用这个
        struct timespec timespec_value;
        timespec_get(&timespec_value,TIME_UTC);
        return timespec_value.tv_sec * 1000LL + timespec_value.tv_usec / 1e6;
    #else
        time_t current_time = time(NULL);
        return current_time * 1000LL;

    #endif

}


#endif
