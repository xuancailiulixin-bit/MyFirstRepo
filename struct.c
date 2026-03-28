#include<stdio.h>

//C11标准引入了对齐控制关键字
#include<stdalign.h>   

/*
_Alignas(16) char buffer[32];指定这个数组成员对齐到16字节
或者使用alignas宏：alignas(16) char buffer[32];

struct alignas(64) <结构体名>
{
    .....
};              //结构体整体对齐到64字节边界

printf("%zu\n",_Alignof(<数据类型> | <结构体变量.结构体成员> | <结构体变量>));
或使用宏：
printf("%zu\n",alignof(<数据类型> | <结构体变量.结构体成员> | <结构体变量>));

*/

int main()
{   
    /*
    struct 结构体名
    {
        <成员类型> <成员名>;
        ...
    }<结构体变量>;

    结构体名不是必须的，在需要重复定义结构体变量时需要
    
    一次性使用的结构体可以没有结构体名：
    struct 
    {
        <成员类型> <成员名>;
        ...
    }<结构体变量>;

    */
    struct Person
    {
        char *name;
        char *id;
        int age;    //内存对齐
    };
    
    struct Person person;
    
    //结构体每个成员默认会对齐到其类型大小的整数倍
    //GCC/Clang支持使用__attribute__((packed))让结构体紧凑对齐，使用__attribute__(aligned(<size>))让单个结构体/成员对齐到size大小
    struct Align 
    {
        char a;
        char b;
        int c;
        int d;
        char *char_arr;
        
    }__attribute__((packed));              //只对这个结构体应用紧凑对齐
    
    /*
    也可以这样写
    struct __attribute__((packed)) Align
    {
        ....
   
    };

    用__attribute__((aligned(32)))替换__attribute__((packed)),意思是结构体总大小对齐到32字节边界
    */

    printf("%zu\n",sizeof(struct Align));  //18
    printf("%zu\n",sizeof(struct Align));  

    //使用typedef定义一种结构体类型
    typedef struct template
    {
        int size;
    }structype;

    //初始化结构体变量
    struct Person myself = {.name="xuncailiulixin",.age=24,.id="2203060113"};   //.是成员选择运算符
    
    myself.age = 18;    //^w^
    printf("%d\n",myself.age);
    struct Person *person_ptr = &myself;
    puts(person_ptr->name);
    printf("%p\n",person_ptr);
    printf("%p\n",&myself.name);    //成员选择运算符的优先级比&高
    
    structype template1 = {.size=4};
    printf("%d\n%zu\n",template1.size,sizeof(template1));   //最好使用%zu格式化sizeof()
    
    return 0;
}
