/*
	���ܣ����Ա��ģ���� 
	���룺�� 
	������� 

	���뻷����Dev-C++ v5.11
	����ע�ͣ�Ҷ�� 
	�޶����ڣ�2021��10��12�� 

	�ο����ף������������ݽṹ(��������󷽷���C++��������)(��2��)��,
	��Σ�2007��6�µ�2��	ҳ�룺PP43-53
	ӡ�Σ�2020��7�µ�23��ӡˢ
*/
#if !defined LINEARLIST_H
#define LINEARLIST_H
using namespace std;
template <class T>
class linearList{
  public:
     //linearList();//constructor
     //linearList(const linearList& A);//copy constructor
     //~linearList();//destructor
     virtual int length()const=0;//return the length of the list
     virtual int find(const T& x)=0;//return the index of x
     virtual bool empty()const=0;//judge if it's empty
     virtual void sort(int a)=0;//sort the list in less<>(1)/greater<>(2)
     virtual T& operator[](int i)=0;//overloarding the operator[],return the value with index i
     virtual bool check(int i)const=0;//avoid the index is illegal
     virtual bool IsFull()const=0;//check if it's full
     virtual void insert(int i,T a)=0;//insert an element as ith element
     virtual void insert(T a)=0;//add an element after the lastest element
     virtual void Delete(int i)=0;//delete the ith element
 //--------------------------------
  protected:
     int last;//the last index of the end of list
     int leng;//the size
     int capacity;
     T* pos;//a pointer pointing to the first element
     //virtual void reSize(int newSize)=0;//allocate new memory and then copy the old data
};
#endif
