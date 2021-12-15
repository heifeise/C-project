/*
	功能：最小堆的实现
	输入：无
	输出：无

	编译环境：windows11  visual stdion code 1.62.0
	开发注释：叶晶 
	修订日期：2021年11月6日 

	参考文献：殷人昆《数据结构(用面向对象方法与C++语言描述)(第2版)》,
	版次：2007年6月第2版	页码：PP236-239
	印次：2020年7月第23次印刷
*/
#if !defined MINHEAP_H
#define MINHEAP_H 
#include<iostream>
#include<cstdlib>
#include<queue>
#define Dmaxsize 10
using namespace std;

template<class T>
class MinHeap;
template<class T>
ostream& operator<< (ostream& out, const MinHeap<T>& minheap);
template<class T>
istream& operator>> (istream& in, MinHeap<T>& minheap);


template<class T>
class MinHeap{
public:
	MinHeap(int size=Dmaxsize){//构造函数
		Maxheapsize=size;currentsize=0;
		heap=new T[Maxheapsize];
        if(heap==NULL)
        {
            cerr<<"fail in allocation"<<endl;
            exit(1);
        }
		// pri=priority;
	}
	MinHeap(T array[],int n);//构造函数
	~MinHeap()//析构函数，清空堆
	{
		delete []heap;
	}
	bool Insert(const T &x);//插入元素到最小堆中
	bool Remove(T &x);//删除堆顶元素并通过x返回
	bool Remove()//删除堆顶元素
	{
		T tem;
		return Remove(tem);
	}
	bool IsEmpty()//判断堆是否为空
	{
		return (currentsize==0) ? true:false;
	}
	bool IsFull()//判断是否堆满
	{
		return (currentsize==Maxheapsize) ? true:false;
	}
	void MakeEmpty()//删除堆
	{
		delete []heap;
	}
	/* bool priority(T a,T b)//默认比较函数
	{
		if(a<b)
			return true;
	}*/
	// bool (*pri)(T a,T b );//函数指针，指向确定堆元素优先级的一个函数，由使用者决定其指向的函数以变更优先级的决定方式
    int find(T& temp)const;//返回tem的下标
    friend ostream& operator<< <>(ostream& out,const MinHeap<T>& minheap);
    friend istream& operator>> <>(istream& in,MinHeap<T>& minheap);
    

//-------------------------------------------------------------------------------------------
protected:
	T* heap;//存放堆元素的数组
	int currentsize;//当前堆中的元素个数
	int Maxheapsize;//堆的容量
	void shiftDown(int start,int end);//从start到end，进行局部下滑调整，使之成为局部最小堆
	void shiftUp(int start);//从start到0，进行上滑调整，使之成为最小堆	
};

#endif