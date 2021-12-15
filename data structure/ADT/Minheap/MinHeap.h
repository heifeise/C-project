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

template<class T>
MinHeap<T>::MinHeap(T array[],int n)//构造函数
{
    heap=new T[n];
    if(heap==NULL)
    {
        cerr<<"fail in allocation"<<endl;
        exit(1);
    }
    for(int i=0;i<n;i++)//复制
        heap[i]=array[i];
    if(Maxheapsize<n)//调整容量
        Maxheapsize=n;
    else
        Maxheapsize=Dmaxsize;
    currentsize=n;//当前元素个数为n
    int currentPos=(currentsize-2)/2;//调整堆的起始点
    while(currentPos>=0)//自底向上，逐步扩大调整范围
    {
        shiftDown(currentPos,n-1);//从currentPos到树底部进行调整(逐步靠近数组前端)
        currentPos--;
    }
}

template<class T>
void MinHeap<T>::shiftDown(int start,int end)//从start到end，进行局部下滑调整，使之成为局部最小堆
{
    int i=start,j=2*i+1;//j是i的左孩子节点
    T tem=heap[i];
    while(j<=end)//下标j仍在数组有效下标范围内（仍在堆中）
    {
        if(j+1<=end&&heap[j]>heap[j+1])//让j等于孩子节点中的最小节点的下标
            j++;//右孩子节点
        if(heap[j]<tem)//父节点大，可以下滑
        {
            heap[i]=heap[j];//下滑一层(下一层覆盖上一层)
            //cout<<tem<<" fall in "<<heap[j]<<endl;
            i=j;j=2*i+1;//第二层,这里，j可能是右节点的下标
        }
        else//不可继续下滑，退出
            break;
    }
    heap[i]=tem;//放回暂存的元素
}

template<class T>
bool MinHeap<T>::Insert(const T &x)//插入元素到最小堆中
{
    if(IsFull())
    {
        cerr<<"the heap is full"<<endl;return false;
    }
    heap[currentsize]=x;//插入尾端
    shiftUp(currentsize);//从下标为currentsize的位置向上调整
    currentsize++;//堆计数加一
    return true;
}

template<class T>
void MinHeap<T>::shiftUp(int start)//从start到0，进行上滑调整，使之成为最小堆
{
    int i=start,j=(i-1)/2;//i是插入节点下标，j是父节点下标
    T temp=heap[i];//暂存
    while(i>0)//插入节点上滑到父节点时停止
    {
        if(temp<heap[j])//插入节点上滑
        {
            heap[i]=heap[j];//上层节点以覆盖的方式下滑
            i=j;j=(i-1)/2;
        }
        else 
            break;
    }
    heap[i]=temp;
}
template<class T>
bool MinHeap<T>::Remove(T &x)//删除堆顶元素并通过x返回
{
    if(IsEmpty())//空堆
        return false;
    x=heap[0];//返回堆顶
    heap[0]=heap[currentsize-1];//堆底元素放到堆顶
    currentsize--;//堆计数减一
    shiftDown(0,currentsize-1);//自顶向下调整
    return true;
}

template<class T>
ostream& operator<< (ostream& out, const MinHeap<T>& minheap)
{
    queue<T> que;
    T tem;
    int j=0;
    que.push(minheap.heap[0]);
    int size;
    while(!que.empty())
    {
        size=que.size();
        for(int i=0;i<size;i++)
        {
            tem=que.front();
            que.pop();
            out<<tem<<" ";
            j=minheap.find(tem);
            if(j*2+1<=minheap.currentsize-1)//左孩子入栈
                que.push(minheap.heap[j*2+1]);
            if(j*2+2<=minheap.currentsize-1)//右孩子入栈
                que.push(minheap.heap[j*2+2]);
        }
        //out<<"the stack is: "<<st<<endl;
    }
        
    return out;
}

template<class T>
int MinHeap<T>::find(T& temp)const//返回temp的下标
{
    int i;
    for(i=0;i<currentsize;i++)
        if(temp==heap[i])
            break;
    return i;
}

template<class T>
istream& operator>> (istream& in, MinHeap<T>& minheap)
{
    for(int i=0;i<minheap.Maxheapsize;i++)
    {    
        in>>minheap.heap[i];
        minheap.currentsize++;
    }
    int currentPos=(minheap.currentsize-2)/2;//调整堆的起始点
    while(currentPos>=0)//自底向上，逐步扩大调整范围
    {
        minheap.shiftDown(currentPos,minheap.currentsize-1);//从currentPos到树底部进行调整(逐步靠近数组前端)
        currentPos--;
    }
    return in;
}

#endif