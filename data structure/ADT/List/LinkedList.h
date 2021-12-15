#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<iostream>
#include<cstdlib>
using namespace std;
template<class T>
struct node{
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
ostream& operator <<(ostream& output, const linkedlist<T>& list);

template<class T>
class  linkedlist{
    friend ostream& operator << <>(ostream& output, const linkedlist<T>& list);
    public:
        linkedlist();
        linkedlist(T d);
        ~linkedlist(){clear();};
        T del();
        T del(int index);
        bool add(T& d);
        bool insert(int index, T d);
        void clear();
        bool empty()
        {
            if(size == 0)
                emp = true;
            else
                emp = false;
            return emp;
        }
        int index(T d);
        int length(){return size;}
        T& operator [](int index);
    private:
        bool emp;
        int size;//结点数
        node<T>* top;//头指针
};

template<class T>
linkedlist<T>::linkedlist()
{
    emp = true;
    size = 0;
    top = NULL;
}

template<class T>
linkedlist<T>::linkedlist(T d)
{
    emp = false;
    size = 1;
    top = new node<T>(d);
}

template<class T>
T& linkedlist<T>::operator [](int index)
{
    if(index+1 > size)
    {
        cerr<<"out of index!";
        exit(1);
    }
    node<T>* p = top;
    while(index--)
    {
        p = p->next;
    }
    return p->data;
}

template<class T>
T linkedlist<T>::del()
{
    return del(size-1);
}

template<class T>
T linkedlist<T>::del(int index)
{
    if(index + 1 > size)
    {
        cerr<<"out of index!";
        exit(1);
    }
    node<T>* p = top;
    index--;
    while(index--)
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
    node<T>* p = top;
    while(p->next != NULL)
    {
        p = p->next;
    }
    p->next = new node<T>(d);
    if(p->next->data == d)
    {
        size++;
        return true;
    }
    return false;
}

template<class T>
bool linkedlist<T>::insert(int index, T d)
{
    if(index + 1 > size)
    {
        cerr<<"out of index!"<<endl;
        exit(0);
    }
    node<T>* p = top;
    while(index--)
    {
        p = p->next;
    }
    node<T>* t = p->next;
    p->next = new node<T>(d);
    p->next->next = t;
    if(p->next->data == d)
    {
        size++;
        return true;
    }
    return false; 
}

template<class T>
void linkedlist<T>::clear()
{
    if(!empty())
    {
        while(top != NULL)
        {
            node<T>* p = top;
            top = top->next;
            delete p;
        }
    }
    size = 0;
}

template<class T>
int linkedlist<T>::index(T d)
{
    node<T>* p = top;
    int index = 0;
    // int m = size;
    while(p != NULL)
    {
        if(p->data == d)
            return index;
        index++;
        p = p->next;
    }
    return -1;
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
