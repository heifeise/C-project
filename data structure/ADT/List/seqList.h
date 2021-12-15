/*
	功能：顺序表模板类的声明 
	输入：无 
	输出：无 

	编译环境：Dev-C++ v5.11
	开发注释：叶晶 
	修订日期：2021年10月12日 

	参考文献：殷人昆《数据结构(用面向对象方法与C++语言描述)(第2版)》,
	版次：2007年6月第2版	页码：PP43-53
	印次：2020年7月第23次印刷
*/
#include<iostream>
#include<cmath>
#include"linearList.h"
#if !defined SEQLIST_H
#define SEQLIST_H
using namespace std;
template<class T> 
class seqList:public linearList<T>{
	public:
	 seqList(){
       pos=NULL;
       leng=0;
       capacity=0;
       last=-1;
     }//constructor
     
     seqList(int Len){
       if(Len>0)
       {
       		pos=new T[Len];
      	 capacity=Len;
       	leng=0;
       	last=-1;
	   }
     }
     
     ~seqList(){delete[] pos;}//destructor
     
     seqList(const seqList& A);//copy constructor
     
//--------------------------------------------
     virtual int length()const;//return the length of the list
     //virtual T search(T& x)const;//return the index of the variable
     virtual bool empty()const;//judge if it's empty
     virtual void sort(int a);//sort the list in less<>(1)/greater<>(2)
     T& operator[](int i);//overloarding the operator[],return the value with index i
     seqList<T>& operator=(const seqList<T>& A);
     void reset(int index,const T& a);
     virtual bool check(int i)const;//avoid the index is illegal
     virtual bool IsFull()const;//check if it's full
     virtual void insert(int i,T a);//insert an element as ith element
     virtual void insert(T a);//add an element after the last element
     virtual void Delete(int i);//delete the ith element
     virtual int find(const T& x);//return the index of x
     void output();//output all the elements by foramt
     int Capacity(){return capacity;}//return the capacity
     //void moveZero();//move zero to end  
 //------------------------------------------
  protected:
     int last;//the last index of the end of list
     int leng;//the size
     int capacity;
     T* pos;//a pointer pointing to the first element
};


//copy constructor
template<class T>
seqList<T>::seqList(const seqList& A)
{
    leng=A.leng;//长度赋值 
    last=leng-1;//最后一位的下标赋值 
    capacity=A.capacity;//容量赋值 
    pos=new T[capacity];//创建数组空间 
    if(pos==NULL)//判断是否成功 
      cerr<<"fail in allocation"<<endl;
    for(int i=0;i<leng;i++)//依次赋值 
    { pos[i]=A.pos[i];}
}

//return the length of the list
template<class T>
int seqList<T>::length()const
{
  return leng;//返回长度 
}

template<class T>
int seqList<T>::find(const T& x)
{
  int i;
    for(i=0;i<leng;i++)//遍历搜索 
    {
      if(pos[i]==x)//返回第一个相等值的下标 
        return i;
    }
    //未找到 
      return -1;
}

//judge if it's empty
template<class T>
bool seqList<T>::empty()const
{
   if(pos==NULL||leng==0)
     return true;
   else
     return false;
}

//sort the list in less<>/greater<>
template<class T>
void seqList<T>::sort(int a)
{
	/*升序排序*/ 
  int i,j; 
  T tem;
  if(leng!=0&&(a==1||a==2))
  {
     if(a==1)
     {
       for(i=0;i<leng;i++)
         for(j=0;j<leng-1-i;j++)
         {
             if(pos[j]>pos[j+1])
             {
              	tem=pos[j];
              	pos[j]=pos[j+1];
              	pos[j+1]=tem;
			       }
          }
      }
      /*降序排序*/ 
      else if(a==2)
       {
         for(i=0;i<leng;i++)
           for(j=0;j<leng-1-i;j++)
           {
	            if(pos[j]<pos[j+1])
	             {
	                tem=pos[j];
              		pos[j]=pos[j+1];
              		pos[j+1]=tem;
				        }
           }
        }
   }
     
}

//overloarding the operator[],return the value with index i
template<class T>
T& seqList<T>::operator[](int i)
{
   if(check(i))//合法性检查 
     return pos[i];
   else
    {
      cerr<<"illegal index"<<endl;
      cout<<i<<endl;
      exit(1);
    }
}

template<class T>
seqList<T>& seqList<T>::operator=(const seqList<T>& A)
{
  int i;
  const seqList<T> *op;
  op=&A;
  while(A.leng!=0&&this!=op)
  {
    T *p=pos;//记录原数组指针 
    pos=new T[A.capacity];//分配新的空间 
    if(pos==NULL)
    {
      pos=p;//分配失败，保留原数组 
      cerr<<"fail in allocation"<<endl;
      exit(1);
    }
    delete[] p;//分配成功，删除原数组 
    leng=A.leng;//长度赋值 
    last=leng-1;//末尾下标赋值 
    capacity=A.capacity;//容量赋值 
    for(i=0;i<leng;i++)//复制数组 
      pos[i]=A.pos[i];
    return *this;
  }
}

template<class T>
void seqList<T>::reset(int index,const T& a)
{
	if(check(index)) 
		pos[index]=a;//修改 
	else
	{
		cerr<<"illegal index"<<endl;
		exit(0);
	}
}
//avoid the index is illegal
template<class T>
bool seqList<T>::check(int i)const
{
	if(i>=0&&i<leng)
  		return true;
	else
		return false;
}

//check if it's full
template<class T>
bool seqList<T>::IsFull()const
{
  if(leng==capacity)//长度等于容量 
    return true;
   else
     return false;
}

//insert an element with index i
template<class T>
void seqList<T>::insert(int i,T a)
{
	  int j;
	  static int n=0;//多次分配空间用的系数，每次分配的空间加倍 
	  T *p=pos;
	  if(i<0||i>leng+1)//the num is illegal 
	   {
	     cerr<<"illegal index"<<endl;
	     exit(1);
	   }
	  else if(i==leng)//插入到最后端 
	  	(*this).insert(a);
	  else if(!(*this).IsFull())//插入到其中且数组不满 
	   {
	     for(j=last;j>=i;j--)//插入位点后的元素后移 
	     {
	        pos[j+1]=pos[j];
	     }
	     pos[i]=a; 
	   }
	   else if((*this).IsFull())// 插入到其中且数组已满 
	   {
	       n++;int m=capacity+pow(2,n);//分配新的空间，且多次分配时，增加每次分配的空间数量 
	       pos=new T[m];
	       if(pos==NULL)
	       {
	          pos=p;n--;
	          cerr<<"fail in allocation"<<endl;
	          exit(1);
	        }
	        leng++;
	        last++;capacity=m;
	        //分两次复制 
	        cout<<"aa"<<endl;
	        for(j=0;j<i;j++)//插入位点之前 
	        	pos[j]=p[j];
	        pos[i]=a;
	        for(j=i+1;j<leng;j++)//插入位点之后 
	        	pos[j]=p[j-1];
	        delete[] p;// 删除原数组 
	   }
   
}

//add an element after the lastest element
template<class T>
void seqList<T>::insert(T a)
{
    int n=0,i;
    T *p; 
    if(!(*this).IsFull())//数组未满，直接插入 
    {
      last++;
      leng++;
      pos[last]=a;
    }
    else if((*this).IsFull())//数组已满 
    {
        p=pos;n++;int k=capacity+pow(2,n); //新建更大的数组 
        pos=new T[k];
        if(pos==NULL)//分配空间失败，保留原数组 
        {
          cerr<<"fail in allocation"<<endl;
          n--;pos=p;
          exit(1);
        }
        for(i=0;i<leng;i++)//分配空间成功 ，复制后删除原数组 
        	pos[i]=p[i];
        delete[] p;
        capacity=k;
        leng++;last++;
        pos[last]=a;
    }
      
}

//delete the element with index i
template<class T>
void seqList<T>::Delete(int i) 
{
  int j;
  if(!check(i))//合法性检测 
  {
    cerr<<"illegal index"<<endl;
    exit(1);
  }
  for(j=i;j<=leng-2;j++)//删除位点后的元素前移 
    pos[j]=pos[j+1];
    leng--;
    last--;
    //cout<<"delete"<<tem<<endl;
}

template<class T>
void seqList<T>::output()//输出 
{
	int i;
	 for(i=0;i<last;i++)
	 	cout<<pos[i]<<' ';
	cout<<pos[i];
}

// template<class T>
// void seqList<T>::moveZero()//move zero to end  
// {
// 	int i,j,num=0;
// 	for(i=0;i<leng;i++)
// 	{
// 		if(pos[i]==0)
// 			num++;
// 		else
// 			pos[i-num]=pos[i];
// 	}
// 	for(i=0,j=leng-1;i<num;i++,j--)
// 		pos[j]=0;
// 	/*int i=0,j=leng-1;
// 	T tem;
// 	while(i!=j)
// 	{
// 		while(pos[j]==0&&j>i)
// 			j--;
// 		while(pos[i]!=0&&j>i)
// 			i++;
// 		if(j>i)
// 		{
// 			tem=pos[i];
// 			pos[i]=pos[j];
// 			pos[j]=tem;
// 		}
// 	}*/
// }

#endif
