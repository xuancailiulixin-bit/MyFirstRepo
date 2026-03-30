#include<stdio.h>
#include<stdlib.h>      //分配动态内存用到

//定义节点类型
typedef struct ListNode
{
    int value;
    struct ListNode *next;
}Node;

//定义创建节点的函数
Node *Create_Node(int value)
{
    //动态分配一个Node大小的内存空间,调用malloc()返回一个void *类型的指针
    Node *node = (Node *)malloc(sizeof(Node));
    //判断动态内存是否分配成功
    if(node == NULL) exit(1);

    //创建成功，给节点赋值
    node->value = value;
    node->next = NULL;
    //返回指针
    return node;
}

//定义销毁节点的函数
void Destory_Node(Node **node_ptr)
{
    (*node_ptr)->next = NULL;     //先把动态内存里的指针置为NULL
    free(*node_ptr);
    *node_ptr = NULL;

}

//定义创建链表的函数，返回一个指向链表（第一个成员）的指针
Node *Create_Linklist(int arr[],int length)
{
    //如果链表长度为0,返回空链表
    if(length <= 0) return NULL;
    Node *head = Create_Node(arr[0]);
    Node *current = head;
    int i;
    for (i = 1;i < length;++i)
        {
            current->next = Create_Node(arr[i]);
            current = current->next;
        }
    
    return head;
}

//打印链表函数
void Print_Linklist(Node *head)
{
    while(head)
    {
        printf("%d\t",head->value);
        head = head->next;
    }

    printf("\n");
}

//定义销毁链表的函数
void Destory_Linklist(Node **head)
{
    if(!head || !(*head)) return;
    Node *current = *head;
    while(current)
    {
        Node *to_be_destory = current;
        current = current->next;
        Destory_Node(&to_be_destory);
    }

    *head = NULL;
}

//定义插入节点的函数
void Insert_Node(Node **head,int value,int index)
{
    if(head == NULL || index < 0) return;      //插入位置index=0时，说明插入到头节点前面
    Node *new_node = Create_Node(value);
    if(index == 0)
    {
        new_node->next = *head;
        *head = new_node;
    }else if(*head == NULL)
    {
        *head = Create_Node(0);           //如果传入的是空指针，先创建一个值为0的节点

    }
    Node *current = *head;
    while(index > 1)
    {
        if(current->next == NULL)
        {
            current->next = Create_Node(0);     
          
        }
        current = current->next;            //如果链表中的成员数量保证能够插入就不会执行if，如果链表成员个数不足或者只有一个成员，就会执行if创建值为0的节点直到能够插入到对应位置
        index--;
    }
    new_node->next = current->next;         //最终current指向的是要插入位置的前一个位置的成员，这样才能插入
    current->next = new_node;
     
}


int main()
{
    int array[] = {0,1,2,3,4};
    Node *head = Create_Linklist(array,5);
    Insert_Node(&head,5,5);
    Insert_Node(&head,6,6);
    Print_Linklist(head);
    Destory_Linklist(&head);
    printf("%p\n",head);
    return 0;
}











