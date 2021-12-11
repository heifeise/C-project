/*
	功能：简单图的存储实现
	输入：无
	输出：无

	编译环境：windows11  visual stdion code 1.62.0
	开发注释：叶晶 
	修订日期：2021年11月27日 

	参考文献：殷人昆《数据结构(用面向对象方法与C++语言描述)(第2版)》
	版次：2007年6月第2版	页码：PP355-366
	印次：2020年7月第23次印刷
*/
//实现简单图，无平行边
#ifndef GRAPHLINK_H
#define GRAPHLINK_H
#include<iostream>
#include<fstream>
#include<cstring>
#include"LinkedList.h"
#define DefaultSize 10
using namespace std;

//T:结点内的数据类型
//E:边的权值的数据类型
template<class T, class E>
struct Edge{//边结点定义
    int dest;//边的另一顶点位置
    E weight;//边的权值
    Edge<T,E> *next;//下一条边的链指针
    Edge(){next = NULL;}//构造函数
    Edge(int index, E weight)//构造函数
    {
        dest = index;
        this->weight = weight;
        next = NULL;
    }
    //bool operator == (Edge<T, E>& ed);//判断两边是否相等
};

template<class T, class E>
struct Vertext{//顶点结点定义
    T data;//数据域
    // int degree;//顶点度数
    Edge<T, E> *tope;//边链表的头指针
    Vertext()//构造函数
    {
        tope = NULL;
    }
    Vertext(T data)//构造函数
    {
        this->data = data;
        tope = NULL;
    }
};

template<class T, class E>
class Graphlink;

template<class T, class E>
istream& operator>> (istream& input, Graphlink<T, E>& graph);

template<class T, class E>
ostream& operator<< (ostream& output, const Graphlink<T, E>& graph);

template<class T, class E>
class Graphlink{
    friend istream& operator>> <>(istream& input, Graphlink<T, E>& graph);
    friend ostream& operator<< <>(ostream& output, const Graphlink<T, E>& graph);
    public:
        Graphlink();//构造函数
        Graphlink(const Graphlink<T, E>& graph);//复制构造函数
        // Graphlink(int vertnum, int edgenum);
        ~Graphlink()
        {   
            vertlist.clear();
            VerNUM = 0;//结点数量
            EdgeNUM = 0;//边的数量
        }
        int VertextPos(T ver)const;//取结点在结点链表中的下标
        int VertNum(){return VerNUM;}//返回结点数量  
        int EdgeNum(){return EdgeNUM;}//返回边的数量
        bool Empty()//判断图是否为空
        {
            if(VerNUM == 0)
                return true;
            else
                return false;
        }
        int Degree(T v)const;//取结点的度
        E getWeight(T v1, T v2)const;//取v1,v2之间边的权重
        bool insertVertext(T ver);//插入顶点结点
        bool insertEdge(T v1, T v2, E weig);//插入边
        bool removeVertext(T d);//删除一个顶点
        bool removeEdge(T v1, T v2);//删除v1,v2之间的一条边
        T getFirstVertext(T ver);//取结点v的第一个邻接结点
        T getnextVerttext(T ver, int i);//取第i个邻接结点
    private:
        linkedlist<Vertext<T, E> > vertlist;//结点链表
        int VerNUM;//结点数量
        int EdgeNUM;//边的数量
};

template<class T, class E>
Graphlink<T, E>::Graphlink()//构造函数
{
    VerNUM = 0;//结点数量
    EdgeNUM = 0;//边的数量
}

template<class T, class E>
Graphlink<T, E>::Graphlink(const Graphlink<T, E>& graph)//复制构造函数
{
    VerNUM = graph.VerNUM;//结点数量
    EdgeNUM = graph.EdgeNUM;//边的数量
    vertlist = graph.vertlist;//结点链表(使用链表内置赋值运算符重载)
    for(int i = 0; i < VerNUM; i++)//复制各个结点的邻接边链表
    {
        Edge<T, E>* temp = graph.vertlist[i].tope;//记录头指针
        Edge<T, E>* temp1 = NULL;//指向新建的边结点
        Edge<T, E>* last = NULL;//记录上一个边结点
        int n = graph.Degree(graph.vertlist[i].data);//需要复制的边链表的长度
        for(int j = 0; j < n; j++)//逐个复制边结点
        {
            temp1 = new Edge<T, E>(temp->dest, temp->weight);//新建复制节点
            if(j == 0)//边链表的头结点
                vertlist[i].tope = temp1;//链入
            if(last != NULL)
                last->next = temp1;//链入
            last = temp1;//更新指向上一结点的指针
            temp = temp->next;//移动到下一个需要复制的结点
        }
    }
}

template<class T, class E>
int Graphlink<T, E>::VertextPos(T ver)const//取结点在结点链表中的下标
{
    //不可使用verlist的内置index方法，因为只有ver无法比较顶点的指针域
    int i;
    for(i = 0; i<VerNUM; i++)//遍历结点链表查找目标结点
    {
        if(ver == vertlist[i].data)//找到
            return i;
    }
    return -1;//未找到
}

template<class T, class E>
int Graphlink<T, E>::Degree(T ver)const//取结点的度
{
    int i = VertextPos(ver);
    if(i == -1)//结点不存在
    {
        cerr<<"vertext was not contained in the Graph!"<<endl;
        exit(1);
    }
    Edge<T, E>*temp = vertlist[i].tope;//暂存边链表的头指针
    int de = 0;
    while(temp != NULL)//求该结点的邻接边链表长度
    {
        de++;
        temp = temp->next;
    }
    return de;
}

template<class T, class E>
E Graphlink<T, E>::getWeight(T v1, T v2)const//取v1,v2之间边的权重
{
    int i = VertextPos(v1);//结点v1在结点链表中的位置
    int j = VertextPos(v2);//结点v2在结点链表中的位置
    if(i == -1 || j == -1)//任意一个顶点不存在
    {
        cerr<<"vertext was not contained in the Graph!"<<endl;
        exit(1);
    }
    Edge<T, E>*temp = vertlist[i].tope;//暂存边链表的头指针
    while(temp != NULL)//顺着邻接边链表查找
    {
        if(temp->dest == j)//找到
            return temp->weight;
        temp = temp->next;//移动到下一结点
    }
    return -10000000;
}

template<class T, class E>
bool Graphlink<T, E>::insertVertext(T ver)//插入顶点结点
{
    if(VertextPos(ver) != -1)//结点已存在
    {
        cerr<<"the vertext has existed!"<<endl;
        exit(1);
    }
    Vertext<T, E> vert(ver);
    vertlist.add(vert);//在表尾添加
    VerNUM++;
    return (VertextPos(ver) != -1) ? true : false;//返回再次查找的结果
}

template<class T, class E>
bool Graphlink<T, E>::insertEdge(T v1, T v2, E weig)//插入边
{
    int i = VertextPos(v1);//结点v1在结点链表中的位置
    int j = VertextPos(v2);//结点v2在结点链表中的位置
    if(i == -1 || j == -1)//任意一个顶点不存在
    {
        cerr<<"can not insert an edge between vertexts which are not exist!"<<endl;
        exit(1);
    }
    Edge<T, E>*temp = vertlist[i].tope;//暂存边链表的头指针
    while(temp != NULL)//确定在v1的邻接边中不存在将要插入的边
    {
        if(temp->dest == j)//存在平行边
        {
            cerr<<"there have been an edge between "<<v1<<" and "<<v2<<endl;//简单图
            exit(1);
        }
        temp = temp->next;
    }  
    if(vertlist[i].tope == NULL)//作为邻接边链表的表头
    {
        vertlist[i].tope = new Edge<T, E>(j, weig);//插入边
        // cout<<"heool"<<endl;
    }
    else
    {
        // cout<<"adfadadg"<<endl;
        temp = vertlist[i].tope;//暂存结点v1的邻接边链表的头指针
        while(temp->next != NULL)//找到结点v1的邻接边链表的末尾
        {
            temp = temp->next;
        }
        temp->next = new Edge<T, E>(j, weig);//插入边
        
    }
    
// ---------------------第二次插入--------------------------------
    if(vertlist[j].tope == NULL)//作为邻接边链表的表头
    {
        vertlist[j].tope = new Edge<T, E>(i, weig);//插入边
    }
    else
    {
        temp = vertlist[j].tope;//暂存结点v2的邻接边链表的头指针
        while(temp->next != NULL)//找到结点v2的邻接边链表的末尾
        {
            temp = temp->next;
        }
        temp->next = new Edge<T, E>(i, weig);//插入边
    }
    EdgeNUM++;
    return true;
}

template<class T, class E>
bool Graphlink<T, E>::removeVertext(T d)//删除一个顶点
{
    int i = VertextPos(d);
    if(i != -1)//需要删除的点存在
    {
        Edge<T, E>*temp = vertlist[i].tope;
        Edge<T, E>*t;
        while(temp != NULL)//删除邻接边链表
        {
            t = temp->next;
            delete temp;
            temp = t;
        }
        vertlist.del(i);//删除结点
    }
    else//需要删除的点不存在
    {
        cerr<<"the vertext is not exist!";
        return false;
    }
    VerNUM--;
    return true;
}

template<class T, class E>
bool Graphlink<T, E>::removeEdge(T v1, T v2)//删除v1,v2之间的一条边
{
    int i = VertextPos(v1);//结点v1的位置
    int j = VertextPos(v2);//结点v2的位置
    Edge<T, E>* temp = vertlist[i].tope;//记录边链表的头指针
    int flag = 0;
    while(temp != NULL)//确定欲删除边是否在v1的边链表中
    {
        if(temp->dest == j)
        {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if(i == -1 || j == -1 || flag == 0)//任意一个顶点不存在或欲删除的边不存在
    {
        cerr<<"can not remove an edge between a vertexts which are not exist!"<<endl;
        return false;
    }

    temp = vertlist[i].tope;//记录v1的边链表的头指针
    if(temp->dest == j)//欲删除边为第一条邻接边
    {
        vertlist[i].tope = temp->next;
        delete temp;
    }
    else{
        while(temp->next->dest != j)//定位到删除结点的前一位置
        {
            temp = temp->next;
        }
        Edge<T, E>* t = temp;//暂存
        temp->next = temp->next->next;//重连接
        delete t;//删除
    }
//--------------------二次删除-----------------------------------
    temp = vertlist[j].tope;//记录v2的边链表的头指针
    if(temp->dest == i)//欲删除边为第一条邻接边
    {
        vertlist[j].tope = temp->next;
        delete temp;
    }
    else{
        while(temp->next->dest != j)//定位到删除结点的前一位置
        {
            temp = temp->next;
        }
        Edge<T, E>* t = temp;//暂存
        temp->next = temp->next->next;//重连接
        delete t;//删除
    }
    return true;
}

template<class T, class E>
T Graphlink<T, E>::getFirstVertext(T ver)//取结点v的第一个邻接结点
{
    if(vertlist[VertextPos(ver)].tope != NULL)
    {
        int i = vertlist[VertextPos(ver)].tope->dest;
        return vertlist[i].data;
    }
    else//没有邻接点
        cerr<<"the vertext is not exist!return self!"<<endl;
    return ver;
}

template<class T, class E>
T Graphlink<T, E>::getnextVerttext(T ver, int i)//取第i个邻接结点
{
    if(i > Degree(ver) || i <= 0)
    {
        cerr<<"the vertext is not exist!return self!"<<endl;
        return ver;
    }
    Edge<T, E>* temp = vertlist[VertextPos(ver)].tope;//ver的边链表的头结点
    for(int j = 0; j< i-1; j++)//顺着链表查找
    {
        temp = temp->next;
    }
    return vertlist[temp->dest].data;
}

template<class T, class E>
istream& operator>> (istream& input, Graphlink<T, E>& graph)//输入流重载
{
    //cout<<"请输入总的顶点数和边数："<<endl;
    graph.vertlist.clear();
    graph.VerNUM = 0;
    graph.EdgeNUM = 0;
    int num_vert,num_edge;
    input>>num_vert>>num_edge;
    //cout<<"请输入各个顶点："<<endl;
    for(int i = 0; i < num_vert; i++)//插入点
    {
        T vert;
        input>>vert;
        if(!graph.insertVertext(vert))
            i--;
    }
    //cout<<"请输入各条边（格式为：点-点-权）："<<endl;
    for(int i = 0; i < num_edge; i++)//插入边
    {
        T vert1;
        T vert2;
        E weigth;
        input>>vert1>>vert2>>weigth;
        if(!graph.insertEdge(vert1, vert2, weigth))
            i--;
    }
    return input;
}

template<class T, class E>
ostream& operator<< (ostream& output, const Graphlink<T, E>& graph)//输出流重载
{
    for(int i = 0; i< graph.VerNUM; i++)
    {
        //Edge<T, E>* edge = graph.vertlist[i].tope;
        for(int j = 0;j < graph.VerNUM; j++)
        {
            E W = graph.getWeight(graph.vertlist[i].data , graph.vertlist[j].data);
            if(W > 0&& i < j)
            {
                cout<<"("<<graph.vertlist[i].data<<","<<graph.vertlist[j].data<<","<<W<<")"<<endl;
            }
        }
        //在linkedlist的下标重载函数后面需要有const修饰，此函数内所有被调用的的其他函数都是如此
        // int n = graph.Degree(graph.vertlist[i].data);
        // while (n--)
        // {
        //     int j = edge->dest;
        //     if(i < j)
        //     {
        //         cout<<"("<<graph.vertlist[i].data<<","<<graph.vertlist[j].data<<","<<edge->weight<<")"<<endl;
        //     }
        //     edge = edge->next;
        // }
    }
    return output;
}

#endif
