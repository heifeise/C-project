/*
	功能：链栈的实现 
	输入：无 
	输出：无 

	编译环境：Dev-C++ v5.11
	开发注释：叶晶 
	修订日期：2021年10月7日 

	参考文献：殷人昆《数据结构(用面向对象方法与C++语言描述)(第2版)》,
	版次：2007年6月第2版	页码：P93
	印次：2020年7月第23次印刷
*/
#if !defined LINEARSTACK_H
#define LINEARSTACK_H
#include<iostream>
using namespace std;
template<class T>
class LinearStack;

template <class T>
ostream& operator<<(ostream& os, const LinearStack<T>& ST);

template<class T>
struct Node{
    T data;
    Node<T> *link;
}; 

template<class T>
class LinearStack{//链栈类的定义 
    public:
        LinearStack(){top=NULL;length=0;}; //构造函数，置空 
        ~LinearStack(){//析构函数 
        	makeEmpty();
		}; 
		bool push(const T&  x);//进栈 
		bool pop(T& x);//出栈 
		bool getTop(T& x)const;//得到栈顶元素 
		bool Isempty()//判断栈是否为空 
		{	
			if(top==NULL)
				return true;
			else 
				return false;
			
		};
		int getSize()const;//求栈的元素个数 
		void makeEmpty();//清空栈 
		friend ostream& operator<< <>(ostream& os, const LinearStack<T>& ST);//重载运算符<< 
		
    private:
        Node<T>* top;
        int length;
};
 
template<class T>
bool LinearStack<T>::push(const T& x)//进栈 
{
	Node<T> *tem=new Node<T>;//创建新的节点 
	tem->data=x;tem->link=top;//对新节点的数据赋值 
	top=tem;//头指针指向新节点
	length++;
	return true; 
}

template<class T>
bool LinearStack<T>::pop(T& x)//出栈 
{
	if(top==NULL)//栈空，返回出栈失败 
		return false;
	Node<T> *tem=top;//记录头指针 
	x=top->data;//返回出栈的值
	top=top->link;//修改头指针位置，指向下一节点 
	delete tem;//删除原栈顶元素 
	length--;
	return true;
}
template<class T>
int LinearStack<T>::getSize()const//求栈的元素个数
{
	return length;
}

template<class T>
void LinearStack<T>:: makeEmpty()//清空栈
{
	Node<T> *p;
	while(top!=NULL) 
	{
			p=top;//指针记录栈顶 
			top=top->link;//栈顶下移 
			delete p;//删除原栈顶 
	} 
	length=0;
}
template<class T>
bool LinearStack<T>::getTop(T& x)const//得到栈顶 
{
	if(top==NULL)//栈为空 
		return false;
	x=top->data;//x赋值为栈顶的值 
	return true;
}
template<class T>
ostream& operator<< (ostream& os, const LinearStack<T>& ST)//重载运算符<< 	
{
	Node<T> *p=ST.top;
	while(p!=NULL)
	{
		os<<p->data<<" ";
		p=p->link;
	}
	return os;
}
#endif
