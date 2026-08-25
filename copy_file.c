#include<stdio.h>

#define COPY_SUCCESS 0
#define COPY_ILLEGAL_ARGUMENTS -1
//arguments在技术领域是参数/自变量的意思，函数中的arguments就是函数参数，ILLEGAL_ARGUMENTS就是参数不合法的意思
#define COPY_SRC_OPEN_ERROR -2
#define COPY_SRC_READ_ERROR -3
#define COPY_DEST_OPEN_ERROR -4
#define COPY_DEST_WRITE_ERROR -5
#define COPY_UNKNOWN_ERROR -100

#define BUFFER_SIZE 512

int CopyFile(char const *src,char const *dest)
{
    if(!src || !dest)
    {
        return COPY_ILLEGAL_ARGUMENTS;
    }

    FILE *src_file = fopen(src,"r");
    if(!src_file)
    {
        return COPY_SRC_OPEN_ERROR;
    }

    FILE *dest_file = fopen(dest,"w");
    if(!dest)
    {
        fclose(src_file);
        return COPY_DEST_OPEN_ERROR;
    }
    
    int result;

    while(1)
    {
        int next = fgetc(src_file);     //int fgetc(FILE *fp);      从文件流fp读取一个字符，作为unsigned char 转换成int，读取失败返回EOF
        if(next == EOF)
        {
            if(ferror(src_file))
            {
                result = COPY_SRC_READ_ERROR;
            }
            else if(feof(src_file))
            {
                result = COPY_SUCCESS;                
            }
            else
            {
                result = COPY_UNKNOWN_ERROR;
            }
            break;
        }
        
        if(fputc(next,dest_file) == EOF)    //函数会先执行一次，再判断条件是否成立；int fputc(int c,FILE *fp);  向指定文件流写入一个字符c，成功返回c，失败返回EOF
        {
            result = COPY_DEST_WRITE_ERROR;
            break;
        }

    }

    fclose(src_file);
    fclose(dest_file);
    return result;

}
    /*
        实际上，const的精准规则是：“const修饰它左边最近的类型，如果左边没有类型，就修饰它右边最近的类型”，这就解释了为什么const char *和char const *等价
        而单独一个'*'并不是一种类型，'*'是类型构造符，*p的整体才是“指向...的指针”这个类型
        '*'把const锁在了“指针指向的内容的类型“这一层，而不是”指针本身“这一层
        如果是char *const p，那么规则就完全不同，const修饰的是p本身，p是指向char的指针常量
    */


int CopyFile2(char const *src,char const *dest)
{
    if(!src || !dest)
    {
        return COPY_ILLEGAL_ARGUMENTS;
    }

    FILE *src_file = fopen(src,"r");
    if(!src_file)
    {
        return COPY_SRC_OPEN_ERROR;
    }

    FILE *dest_file = fopen(dest,"w");
    if(!dest)
    {
        fclose(src_file);
        return COPY_DEST_OPEN_ERROR;
    }
    
    int result;
    
    char buffer[BUFFER_SIZE];
    char *next;                 //fgets()成功返回缓冲区地址，读取失败或者没有可读内容返回NULL
    while(1)
    {
        next = fgets(buffer,BUFFER_SIZE,src_file);
        if(!next)               //如果next为空，说明发生了错误或者文件里没有可读内容了
        {
            if(ferror(src_file))
            {
                result = COPY_SRC_READ_ERROR;
            }
            else if(feof(src_file))
            {
                result = COPY_SUCCESS; 
            }
            else
            {
                result = COPY_UNKNOWN_ERROR;
            }
            break;
        }

        if(fputs(buffer,dest_file) == EOF)      //int fputs(const char *str,FILE *stream);      成功返回非负值，失败返回EOF
        {
            result = COPY_DEST_WRITE_ERROR;
            break;
        }
    }



    fclose(src_file);
    fclose(dest_file);
    return result;
}

int main()
{
    int result = CopyFile2("io_test.txt","io_test.txt.bak.bak");

    return 0;
}
