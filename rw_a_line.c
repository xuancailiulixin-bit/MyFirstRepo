#include<stdio.h>

void Echo()
{
    char buffer[4];

    while(1)
    {
        if(!fgets(buffer,sizeof(buffer),stdin))
        {
            break;
        }
        //puts(buffer);     puts()会自动追加换行符，而fgets在发生截断时是不会有换行符的，所以看起来像是一口气读取了超过缓冲区大小个字符
        printf("%s",buffer);       
    
    }
}


int main()
{
    //gets()的危险之处：gets()从stdin里读取，把读取到的数据存放到缓冲区，关键在于gets()没有限制读取的字节的数量，它会一直读直到遇到换行符，可能造成缓冲区溢出
    
    /*
        函数原型：char *fgets(char *str,int n,FILE *stream);
        从指定文件流stream中读取最多n-1个字符，如果读取到'\n'就停止读取，并把'\n'也存入缓冲区，如果一直没遇到'\n'就会读满n-1个字符，然后在第n个字符的位置自动添加'\0'，也就是说无论是否读到'\n'，都会在读取到的字符串末尾添加'\0'，如果发生截断，当再次调用fgets时，会从截断处继续读取字符
        成功读取到一行(包括发生截断)，返回缓冲区地址
        如果读取到文件末尾或者发生读取错误，返回NULL
        
    */

    /*
        函数原型：int fputs(const char *str,FILE *stream);
        将字符串str写入到指定流，不自动添加换行符'\n'和'\0'
        成功返回非负值，失败返回EOF
    */    

    Echo();

    return 0;
}
