#include<stdio.h>
#include<time.h>
#include"time_utils.h"

int main()
{
    /*
        函数原型：char *asctime(const struct tm *tm);
        传入一个分解时间(struct tm)，返回一个固定格式的字符串："星期几 月份 日期 时:分:秒 年份\n"

    */
    time_t now = time(NULL);
    puts(asctime(localtime(&now)));
    
    //char *ctime(const time_t *timer);
    //ctime(&now);等价于asctime(localtime(&now));的组合调用
    puts(ctime(&now));

    /*
        函数原型：size_t strftime(char *s,size_t max,const char *format,const struct tm *tm);
        s是输出缓冲区，max是缓冲区最大长度
        format是格式控制字符串
        tm是指向struct tm的指针
        
        成功：返回写入缓冲区的字符数(不包括结尾的'\0')
        失败返回0
        
        常用的格式控制字符： 
        %Y四位年份、%m月份(01-12)、%d日期(01-31)、%H小时(00-23)、%M分钟(00-59)、%S秒(00-59)
    */
    
    char Buffer[20];
    size_t size = strftime(Buffer,sizeof(Buffer),"%Y-%m-%d %H-%M-%S",localtime(&now));
    puts(Buffer);
    printf("%zu\n",size);
    
    /*
        函数原型：int sprintf(char *buffer,const char *format,...);

        格式化符的作用是对二进制数据进行对应的处理，这是底层的实现逻辑
        用好理解的方式说就是：格式化是把二进制数据转换成对应格式的单个或多个字符
        整数65和字符'A'的二进制数据都是0100 0001，使用%d格式化就是把二进制数据识别成整数65,再把65转换成字符'6','5'；使用%c格式化就是直接传递二进制值
        
        但实际上计算机并没有“识别”功能，只会执行指令(直接对二进制数据进行运算)，计算机并不会把01000001识别成整数65,而是%d告诉他该怎么去处理这串二进制数据

        传入的参数如果是变量，它的二进制数据已经存储在内存中；如果传入的是字面量，就需要编译器解析，确认数据类型，翻译成对应二进制数据，在编译期就直接确定了
        当调用sprintf(buffer,%d,var) 时，无论var的类型是char、short、int还是其他数据类型，都会被扩展或截断成4个字节大小

        sprintf()需要传入目标字符串缓冲区buffer，格式控制字符串format，还有可变参数...是要格式化的数据
        成功：返回写入buffer的字符的个数(不包括结尾的'\0')
        失败：返回负数

        sprintf()就是把参数数据格式化，转换成对应格式的字符储存到目标字符串缓冲区里；格式化其实就是转换成字符

    */

    //可以使用%Y%m%d%H%M%S这样的格式化内容作为文件名，但是可能存在重名，所以需要毫秒级精度
    strftime(Buffer,sizeof(Buffer),"%Y%m%d%H%M%S",localtime(&now));
    long_time_t ms = TimeInMillisecond();
    int current_ms = ms % 1000;
    sprintf(Buffer + 14,"%03d",current_ms);
    puts(Buffer);


    return 0;
}
