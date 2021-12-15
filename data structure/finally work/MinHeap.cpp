#include"MinHeap.h"
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