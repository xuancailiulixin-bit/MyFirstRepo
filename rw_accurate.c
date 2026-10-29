#include<stdio.h>


/*
    无论是fgetc和fputc，还是fgets和fputs都不能指定读写的字节数，C语言提供了精确读写指定数量的字节的函数：fread()和fwrite()
    
        
    函数原型：size_t fread(void *_Buffer,size_t _ElementSize,size_t _ElementCount,FILE *_Stream);
    _Buffer是缓冲区地址，_ElementSize是每个数据单元的大小(字节数)，_ElementCount是要读取的数据单元的个数，_Stream是指定的文件流指针
    成功：返回实际读取到的数据单元的个数
    出错或读取到文件末尾：返回小于_ElementCount的数
    


    
    函数原型：size_t fwrite(const void *_Buffer,size_t _ElementSize,size_t _ElementCount,FILE *_Stream);
    功能：把_Buffer所指向的内容写入到指定文件流；_Buffer可以是任意数据类型的变量的地址，把它们全部看作是字节序列处理

    返回值判断方式：
    size_t n = fread(buffer,1,1024,fp);
    if(n != 1024)
        {
            if(feof(fp))
                {
                    printf("读取到文件末尾，读取到%zu个字节\n",n);
                }
            else if(ferror(fp))
                {
                    perror("fread出错\n");
                }   
        }
*/


void Echo()
{
    #define BUFFER_SIZE 4
    char buffer[BUFFER_SIZE];

    while(1)
    {
        
        size_t bytes_read = fread(buffer,sizeof(buffer[0]),BUFFER_SIZE,stdin);      //先从标准输入流读取字符缓冲区大小个字节

        if(bytes_read < BUFFER_SIZE)        //根据fread的返回值判断是否全部读取完或者发生错误
        {
            if(feof(stdin))
            {
                puts("EOF");
                fwrite(buffer,sizeof(buffer[0]),bytes_read,stdout);         //还没读取完指定的字节数，就已经读到stdin缓冲区末尾
            }
            else if(ferror(stdin))      //fread读取发生错误，结束循环
            {
                perror("Error read from stdin");
                break;
            }
        }
        
        fwrite(buffer,sizeof(buffer[0]),BUFFER_SIZE,stdout);        //成功从stdin缓冲区读取到指定的字节数，执行下一次循环
        
    }
    

}

int main()
{
    
    Echo();
    return 0;
}
