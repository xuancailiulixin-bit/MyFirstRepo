#include<stdio.h>
#include<unistd.h>      //for sleep()
#include<errno.h>


/*
    关于I/O缓冲区，缓冲区就是一块内存，通常是一个字符数组，用来暂存读写数据；
    每个FILE结构体里都有和缓冲区有关的指针，用来对这个流的缓冲区进行操作
    如果没有缓冲区，数据的读写就需要不断地调用CPU,而如果把要读写的数据放到缓冲区里再成批操作，就可以减少CPU调用次数
    
    FILE结构体里有对缓冲区进行操作的指针，但是缓冲区的内存需要额外分配

    FILE结构体里和缓冲区有关的成员：
        缓冲区起始地址<--->缓冲区结束地址
        从不同的视角看同一个缓冲区，可以分为读缓冲区和写缓冲区
        读缓冲区：
            读缓冲区开始地址<--->读缓冲区有效数据结尾地址
            当前读取位置地址
        写缓冲区：
            写缓冲区开始地址<--->写缓冲区结尾地址
            当前写入位置地址

    给缓冲区分配内存的函数：
        函数原型：int setvbuf(FILE *stream,char *buffer,int mode,size_t size);
                ：void setbuf(FILE *stream,char *buffer);
                setbuf的第二个参数大小是固定的BUFSIZ，用户需要提供一个大小为BUFSIZ的字符数组buffer[BUFSIZ]
                setbuf默认采用全缓冲模式，如果第二个参数为NULL，就说明是无缓冲
                setvbuf可以让用户自己定义缓冲区的大小，但是需要提供缓冲区大小size，并且支持选择缓冲区缓冲模式mode
                setvbuf(fp,NULL,mode,size);如果第二个参数为NULL，相当于是匿名缓冲区，缓冲区内存由标准库自动分配;
                当setbuf的第二个参数为NULL时，无论第三个参数是_IOFBUF、_IOLBUF还是_IONBUF，第四个参数是什么都会被忽略掉，系统会使用自己的默认大小
                默认大小通常为BUFSIZ，并没有强制规定，不同平台实现不同，行缓冲和无缓冲都能分配默认大小，无缓冲直接不使用缓冲区
                使用setvbuf设置为无缓冲：setvbuf(fp,NULL,_IONBF,0);

    C标准支持三种缓冲模式，分别是：
        全缓冲(_IOFBF)：缓冲区满之后再写入/读取
        行缓冲(_IOLBF)：遇到换行符\n再写入/读取
        无缓冲(_IONBF)：直接写入/读取

    关于读缓冲区的逻辑空和物理空
        FILE结构体里与读缓冲区有关的指针分别是：
            读缓冲区开始地址、读缓冲区有效数据结尾地址、当前读取位置地址
            读缓冲区有效数据结尾地址不一定是缓冲区结束地址，当前读取位置地址等于读缓冲区有效数据结尾地址时，读缓冲区逻辑空，但是实际上读缓冲区里是有数据存在的，只是被记为无效

*/

int main()
{
    char buffer[BUFSIZ];            //关于缓冲区比较重要的一点就是：缓冲区的生命周期一定要比文件流的生命周期长
    FILE *fp = fopen("io_test.txt","r");
    if(!fp)
    {
        perror("fopen:");           //函数perror()必须要有参数才能编译成功
        return -1;
    }else
    {
        printf("文件打开成功！\n");
        setbuf(fp,buffer);
    }

    fclose(fp);

    printf("hello ");
    //fflush(stdout);
    sleep(2);
    printf("world!\n");             //因为printf()使用的是行缓冲，运行程序会发现并不会直接打印出"hello "，而是先等待两秒，再一起打印出"hello world!"
    

    return 0;
}
