/*
	���ܣ���ջ��ʵ�� 
	���룺�� 
	������� 

	���뻷����Dev-C++ v5.11
	����ע�ͣ�Ҷ�� 
	�޶����ڣ�2021��10��7�� 

	�ο����ף������������ݽṹ(��������󷽷���C++��������)(��2��)��,
	��Σ�2007��6�µ�2��	ҳ�룺P93
	ӡ�Σ�2020��7�µ�23��ӡˢ
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
class LinearStack{//��ջ��Ķ��� 
    public:
        LinearStack(){top=NULL;length=0;}; //���캯�����ÿ� 
        ~LinearStack(){//�������� 
        	makeEmpty();
		}; 
		bool push(const T&  x);//��ջ 
		bool pop(T& x);//��ջ 
		bool getTop(T& x)const;//�õ�ջ��Ԫ�� 
		bool Isempty()//�ж�ջ�Ƿ�Ϊ�� 
		{	
			if(top==NULL)
				return true;
			else 
				return false;
			
		};
		int getSize()const;//��ջ��Ԫ�ظ��� 
		void makeEmpty();//���ջ 
		friend ostream& operator<< <>(ostream& os, const LinearStack<T>& ST);//���������<< 
		
    private:
        Node<T>* top;
        int length;
};
 
template<class T>
bool LinearStack<T>::push(const T& x)//��ջ 
{
	Node<T> *tem=new Node<T>;//�����µĽڵ� 
	tem->data=x;tem->link=top;//���½ڵ�����ݸ�ֵ 
	top=tem;//ͷָ��ָ���½ڵ�
	length++;
	return true; 
}

template<class T>
bool LinearStack<T>::pop(T& x)//��ջ 
{
	if(top==NULL)//ջ�գ����س�ջʧ�� 
		return false;
	Node<T> *tem=top;//��¼ͷָ�� 
	x=top->data;//���س�ջ��ֵ
	top=top->link;//�޸�ͷָ��λ�ã�ָ����һ�ڵ� 
	delete tem;//ɾ��ԭջ��Ԫ�� 
	length--;
	return true;
}
template<class T>
int LinearStack<T>::getSize()const//��ջ��Ԫ�ظ���
{
	return length;
}

template<class T>
void LinearStack<T>:: makeEmpty()//���ջ
{
	Node<T> *p;
	while(top!=NULL) 
	{
			p=top;//ָ���¼ջ�� 
			top=top->link;//ջ������ 
			delete p;//ɾ��ԭջ�� 
	} 
	length=0;
}
template<class T>
bool LinearStack<T>::getTop(T& x)const//�õ�ջ�� 
{
	if(top==NULL)//ջΪ�� 
		return false;
	x=top->data;//x��ֵΪջ����ֵ 
	return true;
}
template<class T>
ostream& operator<< (ostream& os, const LinearStack<T>& ST)//���������<< 	
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
