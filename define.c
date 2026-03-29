#include<stdio.h>

//#define MAX(a,b) a > b ? a : b            

/*
MAX(1,MAX(3,4))supposed to return a result of 4,
however,actually,MAX(1,MAX(3,4))without () is replaced with 1 > 3 > 4 ? 3 : 4 ? 1 : 3 > 4 ? 3 : 4
*/

#define MAX(a,b) (a) > (b) ? (a) : (B)      //good,因为#define只是简单的文本替换，用()括起来能够避免歧义

/*
参数每次作用于宏定义时，将会重新求值。由于多次求值MAX(x++,y++)，可能产生不可预测的后果
参数在被函数调用前只求值一次。参数的副本在函数中多次使用并不会导致多次求值的问题
*/


int main()
{



    return 0;
}    
