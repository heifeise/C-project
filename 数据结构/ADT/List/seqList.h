/*
	���ܣ�˳���ģ��������� 
	���룺�� 
	������� 

	���뻷����Dev-C++ v5.11
	����ע�ͣ�Ҷ�� 
	�޶����ڣ�2021��10��12�� 

	�ο����ף������������ݽṹ(��������󷽷���C++��������)(��2��)��,
	��Σ�2007��6�µ�2��	ҳ�룺PP43-53
	ӡ�Σ�2020��7�µ�23��ӡˢ
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
    leng=A.leng;//���ȸ�ֵ 
    last=leng-1;//���һλ���±긳ֵ 
    capacity=A.capacity;//������ֵ 
    pos=new T[capacity];//��������ռ� 
    if(pos==NULL)//�ж��Ƿ�ɹ� 
      cerr<<"fail in allocation"<<endl;
    for(int i=0;i<leng;i++)//���θ�ֵ 
    { pos[i]=A.pos[i];}
}

//return the length of the list
template<class T>
int seqList<T>::length()const
{
  return leng;//���س��� 
}

template<class T>
int seqList<T>::find(const T& x)
{
  int i;
    for(i=0;i<leng;i++)//�������� 
    {
      if(pos[i]==x)//���ص�һ�����ֵ���±� 
        return i;
    }
    //δ�ҵ� 
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
	/*��������*/ 
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
      /*��������*/ 
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
   if(check(i))//�Ϸ��Լ�� 
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
    T *p=pos;//��¼ԭ����ָ�� 
    pos=new T[A.capacity];//�����µĿռ� 
    if(pos==NULL)
    {
      pos=p;//����ʧ�ܣ�����ԭ���� 
      cerr<<"fail in allocation"<<endl;
      exit(1);
    }
    delete[] p;//����ɹ���ɾ��ԭ���� 
    leng=A.leng;//���ȸ�ֵ 
    last=leng-1;//ĩβ�±긳ֵ 
    capacity=A.capacity;//������ֵ 
    for(i=0;i<leng;i++)//�������� 
      pos[i]=A.pos[i];
    return *this;
  }
}

template<class T>
void seqList<T>::reset(int index,const T& a)
{
	if(check(index)) 
		pos[index]=a;//�޸� 
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
  if(leng==capacity)//���ȵ������� 
    return true;
   else
     return false;
}

//insert an element with index i
template<class T>
void seqList<T>::insert(int i,T a)
{
	  int j;
	  static int n=0;//��η���ռ��õ�ϵ����ÿ�η���Ŀռ�ӱ� 
	  T *p=pos;
	  if(i<0||i>leng+1)//the num is illegal 
	   {
	     cerr<<"illegal index"<<endl;
	     exit(1);
	   }
	  else if(i==leng)//���뵽���� 
	  	(*this).insert(a);
	  else if(!(*this).IsFull())//���뵽���������鲻�� 
	   {
	     for(j=last;j>=i;j--)//����λ����Ԫ�غ��� 
	     {
	        pos[j+1]=pos[j];
	     }
	     pos[i]=a; 
	   }
	   else if((*this).IsFull())// ���뵽�������������� 
	   {
	       n++;int m=capacity+pow(2,n);//�����µĿռ䣬�Ҷ�η���ʱ������ÿ�η���Ŀռ����� 
	       pos=new T[m];
	       if(pos==NULL)
	       {
	          pos=p;n--;
	          cerr<<"fail in allocation"<<endl;
	          exit(1);
	        }
	        leng++;
	        last++;capacity=m;
	        //�����θ��� 
	        cout<<"aa"<<endl;
	        for(j=0;j<i;j++)//����λ��֮ǰ 
	        	pos[j]=p[j];
	        pos[i]=a;
	        for(j=i+1;j<leng;j++)//����λ��֮�� 
	        	pos[j]=p[j-1];
	        delete[] p;// ɾ��ԭ���� 
	   }
   
}

//add an element after the lastest element
template<class T>
void seqList<T>::insert(T a)
{
    int n=0,i;
    T *p; 
    if(!(*this).IsFull())//����δ����ֱ�Ӳ��� 
    {
      last++;
      leng++;
      pos[last]=a;
    }
    else if((*this).IsFull())//�������� 
    {
        p=pos;n++;int k=capacity+pow(2,n); //�½���������� 
        pos=new T[k];
        if(pos==NULL)//����ռ�ʧ�ܣ�����ԭ���� 
        {
          cerr<<"fail in allocation"<<endl;
          n--;pos=p;
          exit(1);
        }
        for(i=0;i<leng;i++)//����ռ�ɹ� �����ƺ�ɾ��ԭ���� 
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
  if(!check(i))//�Ϸ��Լ�� 
  {
    cerr<<"illegal index"<<endl;
    exit(1);
  }
  for(j=i;j<=leng-2;j++)//ɾ��λ����Ԫ��ǰ�� 
    pos[j]=pos[j+1];
    leng--;
    last--;
    //cout<<"delete"<<tem<<endl;
}

template<class T>
void seqList<T>::output()//��� 
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
