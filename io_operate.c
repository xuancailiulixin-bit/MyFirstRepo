#include<stdio.h>

void Echo()
{
    while(1)
    {   
        int next_input = getchar();
        if(next_input == EOF)           //键盘上并没有EOF这个按键，在绝大部分操作系统上，EOF是由组合键Ctrl + D触发的，在Windows命令行上由Ctrl + Z（然后按回车）触发，
                                        //对于标准流stdin来说，EOF不再仅表示数据已经读完了，还意味着“用户告诉程序：我不想再继续输入了”
        {   
            break;
        }
        else if(next_input == '\n')
        {
            continue;
        }

        printf("%c\n",next_input);
    }

}

int main()
{
    /*
        函数原型：int fgetc(FILE *stream);
            功能：从指定流中读取一个字符
            成功：返回读取的字符（作为unsigned char转换为int）；失败返回EOF

        函数原型：int fputc(int c,FILE *stream);
            功能：向指定流写入一个字符,参数c会转换成unsigned char后写入
            成功：返回写入的字符（转换为int）；失败返回EOF
        
        函数原型：int getchar(void);
            功能：从stdin流的缓冲区读取数据；stdin流使用行缓冲，
            用户在终端输入一个个字符直到按下回车键(\r或\n)，在按下回车键之前，这些字符会被暂存在内核的行缓冲区，不能取消但可以使用退格键修改，回车键会被终端驱动程序识别为“这一行输入结束”，终端驱动程序把这行数据发送给关联到该终端的程序->数据进入由C标准库管理的stdin流缓冲区(从内核行缓冲区复制到stdin行缓冲区)
            函数getchar()从stdin缓冲区取走第一个字符，下次调用getchar()会取走stdin缓冲区里的下一个字符
            如果缓冲区是空的，则等待(阻塞)直到内核发来一行数据
            回车键(Enter)一般会产生CR('\r',ASCII 13)或LF('\n',ASCII 10)，Linux会把Enter解释为'\n'，Windows可能产生'\r\n'

        int ch = getchar();     //输入a并回车('\n')
        int ch = getchar();     //直接返回'\n'
    */


    /*
        为什么不能用char类型变量来接收fgetc/fputc的返回值？(char是无符号类型)
        fgetc()从文件流中读取一个字符(一个字节)，把这个字节转换成int类型(8位->32位)
        EOF(-1)的int表示是0xFFFFFFFF，截断为char类型是0xFF(十进制数255)
        在用返回值与-1作比较时，char类型会被提升为int类型(0xFF->0x000000FF)，0x000000FF != 0xFFFFFFFF(-1)
        如果使用signed char来接收返回值，那么0xFF会被解释为-1(有符号数最高位0为正数，1为负数，-1的8位有符号数原码：10000001,反码11111110,补码11111111)
    */

    /*
        为什么不推荐使用getc()和putc()？
        最主要的原因：getc和putc是宏
        
        getc和putc直接操作FILE结构体里的成员
        getc的简化定义：#define getc(fp) (--(fp)->_cnt >= 0 ? *(fp)->_ptr++ : _filbuf(fp))
            _cnt是缓冲区剩余字符数
            _ptr是当前读/写位置(指向缓冲区中下一个字符的位置)
            int _filbuf(FILE *fp);函数负责通过系统调用read()重新填充缓冲区

            getc的功能就是先减少_cnt，再判断_cnt是否>=0，也就是判断缓冲区里是否还有剩余字符
            如果有字符先返回*(fp)->_ptr，再_ptr++
            如果缓冲区里没有字符了，就调用函数_filbuf()重新填充缓冲区

            宏的优势在于没有函数调用开销(当缓冲区里有内容的时候)
            缺点就是宏会对参数进行多次求值的副作用
            
            getchar()和putchar()也是宏：
                #define getchar() getc(stdin)
                #define putchar(c) putc((c),stdout)     参数c会被转换成unsigned char写入到输出流

    */
    
    Echo();         //因为getchar()每次从stdin的缓冲区里只读取一个字符，我们可以一次输入多个字符到stdin缓冲区
    return 0;
}
