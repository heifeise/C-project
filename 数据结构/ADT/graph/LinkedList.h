/*
	功能：链表的实现
	输入：无
	输出：无

	编译环境：windows11  visual stdion code 1.62.0
	开发注释：叶晶 
	修订日期：2021年11月27日 

	参考文献：殷人昆《数据结构(用面向对象方法与C++语言描述)(第2版)》
	版次：2007年6月第2版	页码：PP53-66
	印次：2020年7月第23次印刷
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<iostream>
#include<cstdlib>
using namespace std;
template<class T>
struct node{//结点定义
    T data;
    node<T>* next;
    node()
    {
        data = 0;
        next = NULL;
    }
    node(T& d)
    {
        data = d;
        next = NULL;
    }
};

template<class T> 
class linkedlist;

template<class T>
ostream& operator<< (ostream& output, const linkedlist<T>& list);

template<class T>
class  linkedlist{
    friend ostream& operator<< <>(ostream& output, const linkedlist<T>& list);
    public:
        linkedlist();//构造函数
        linkedlist(const linkedlist<T>& list);//复制构造函数
        linkedlist(T d);//构造函数，以d为表头结点的值
        ~linkedlist(){clear();};
        T del();//删除末尾结点
        T del(int index);//删除下标为index的结点
        bool add(T& d);//在末尾添加结点
        bool insert(int index, T d);//在下边为index的结点之后插入结点
        void clear();//清空链表
        bool empty()//判断链表是否为空
        {
            if(size == 0)
                return true;
            else
                return false;
        }
        int index(T d);//返回值为d的结点在链表中的位置
        int length(){return size;}//返回链表的长度
        T& operator [](int index) const;//重载下标运算符
        void operator=(linkedlist<T> list);//重载复制运算符
    private:
        int size;//结点数（链表长度）
        node<T>* top;//头指针
};

template<class T>
linkedlist<T>::linkedlist()//构造函数
{
    size = 0;
    top = NULL;
}

template<class T>
linkedlist<T>::linkedlist(const linkedlist<T>& list)//复制构造函数
{
    size = list.size;
    top = NULL;
    node<T>* temp = list.top;
    node<T>* temp1 = NULL;//指向新创建的结点
    node<T>* last = NULL;//记录当前复制结点的上一结点
    for(int i = 0; i < size; i++)//依次复制各个结点
    {
        temp1 = new node<T>(temp->data);
        if(i == 0)//头指针赋值
            top = temp1;
        if(last != NULL)
            last->next = temp1;//连接上一结点与新创建的结点
        last = temp1;//更新指向上一结点的指针
        temp = temp->next;
    }
}

template<class T>
linkedlist<T>::linkedlist(T d)//构造函数，以d为表头结点的值
{
    size = 1;
    top = new node<T>(d);
}

template<class T>
T& linkedlist<T>::operator [](int index) const
{
    if(index+1 > size)//下标越界
    {
        cerr<<"out of index!";
        exit(1);
    }
    node<T>* p = top;
    while(index--)//顺着链表查找
    {
        p = p->next;
    }
    return p->data;
}

template<class T>
void linkedlist<T>::operator=(linkedlist<T> list)
{
    if(this->top != list.top)
    {
        this->clear();//删除原链表
        size = list.size;
        node<T>* temp = list.top;
        node<T>* temp1 = NULL;//指向新创建的结点
        node<T>* last = NULL;//记录当前复制结点的上一结点
        for(int i = 0; i < size; i++)
        {
            temp1 = new node<T>(temp->data);
            if(i == 0)//头指针赋值
                top = temp1;
            if(last != NULL)
                last->next = temp1;//连接上一结点与新创建的结点
            last = temp1;//更新指向上一结点的指针
            temp = temp->next;
        }
    }
}

template<class T>
T linkedlist<T>::del()//删除表尾结点
{
    return del(size-1);//删除指定下标的结点
}

template<class T>
T linkedlist<T>::del(int index)//删除下标为index的结点
{
    if(index + 1 > size)//下标越界
    {
        cerr<<"out of index!";
        exit(1);
    }
    node<T>* p = top;
    index--;
    while(index--)//定位
    {
        p = p->next;
    }
    node<T>* t = p->next;
    T d = p->next->data;
    p->next = p->next->next;//形式删除
    size--;
    delete t;//实际删除
    return d;
}

template<class T>
bool linkedlist<T>::add(T& d)
{
    if(size == 0)//表空，新结点作为头结点
    {
        top = new node<T>(d);
        if(top == NULL)
            return false;
        size++;
        return true;
    }
    node<T>* p = top;
    while(p->next != NULL)//定位到表尾
    {
        p = p->next;
    }
    p->next = new node<T>(d);//新结点作为表尾结点
    if(p->next == NULL)//添加失败
        return false;
    size++;
    return true;
}

template<class T>
bool linkedlist<T>::insert(int index, T d)//在下标为index的结点后插入新结点
{
    if(index + 1 > size || index < 0)//下标越界
    {
        cerr<<"out of index!"<<endl;
        return false;
    }
    node<T>* p = top;
    while(index--)//定位
    {
        p = p->next;
    }
    node<T>* t = p->next;//暂存插入点下端
    p->next = new node<T>(d);//插入
    p->next->next = t;//重新连接链表
    if(p->next->data == d)//成功插入
    {
        size++;
        return true;
    }
    return false; 
}

template<class T>
void linkedlist<T>::clear()//清空链表
{
    if(!empty())
    {
        while(top != NULL)
        {
            node<T>* p = top;
            top = top->next;
            delete p;
        }
        size = 0;
    }
}

template<class T>
int linkedlist<T>::index(T d)//返回值为d的结点第一次出现的位置
{
    node<T>* p = top;
    int index = 0;
    // int m = size;
    while(p != NULL)//顺着链表查找
    {
        if(p->data == d)//找到
            return index;
        index++;
        p = p->next;
    }
    return -1;//未找到
}

template<class T>
ostream& operator <<(ostream& output, const linkedlist<T>& list)
{
    node<T>* p = list.top;
    int n = 0;
    while(p != NULL)
    {
        output<<p->data;
        n++;
        if(n != list.size)
            output<<" ";
        p = p->next;
    }
    return output;
}

#endif
