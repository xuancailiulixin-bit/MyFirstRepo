#include<stdio.h>

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
        int age;
        char *id;
    };
    
    struct Person person;

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
