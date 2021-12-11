/*
	���ܣ��������Ĵ洢ʵ��
	���룺��
	�������

	���뻷����windows11  visual stdion code 1.62.0
	����ע�ͣ�Ҷ�� 
	�޶����ڣ�2021��11��5�� 

	�ο����ף������������ݽṹ(��������󷽷���C++��������)(��2��)��,
	��Σ�2007��6�µ�2��	ҳ�룺PP195-210
	ӡ�Σ�2020��7�µ�23��ӡˢ
*/
#if !defined BINARYTREE_H
#define BINARYTREE_H
#include<iostream>
#include<cstdlib>
#include<queue>
#include"LinearStack.h"

using namespace std;
template<typename T>
//define null NULL;
struct BinTreeNode{//�������ڵ㶨��
    T data;//������
    BinTreeNode<T>* leftChild;
    BinTreeNode<T>* rightChild;//������Ůָ���� <T>
    BinTreeNode<T>* parent;
    BinTreeNode()//���캯��
    {   
        leftChild=NULL;
        data=0;
        rightChild=NULL;
        parent=NULL;
    }
    BinTreeNode(T x,BinTreeNode* l,BinTreeNode* r)
    {
        leftChild=l;
        data=x;
        rightChild=r;
        parent=NULL;
    }
    explicit BinTreeNode(T x)
    {
        leftChild=NULL;
        data=x;
        rightChild=NULL;
        parent=NULL;
    }
};

template<class T>
class BinaryTree;
template<class T>
ostream& operator<< (ostream& out,const BinaryTree<T> &tree); //���������
template<class T>
istream& operator>> (istream& in,BinaryTree<T> &tree);//���������
//----------------------------------------------------------------------------------------------------------------
template<class T>
class BinaryTree{//��������Ķ���
public:
    BinaryTree(){//���캯��
        root=NULL;
        refvalue='#';
        height=0;
		size=0;
		heightval=false;
    }
    explicit BinaryTree(char x)//���캯��
    {
    	refvalue=x;
		root=NULL;
		height=0;
		size=0;
		heightval=false;
	}
    explicit BinaryTree(BinaryTree<T> &Tree)//���ƹ��캯��
    {
	
    	BinTreeNode<T>* p=Tree.getRoot();
        copy(root,p);
    }
    ~BinaryTree(){//��������
        destory(root);
    }
    bool IsEmpty(){//�ж϶������Ƿ�Ϊ��
        return (root==NULL) ? true:false;
    }
    BinTreeNode<T>* Parent(BinTreeNode<T>* current){//���ظ��ڵ�ָ��
      return current->parent;
    }
    BinTreeNode<T>* leftChild(BinTreeNode<T>* current){//��������Ů�ڵ�ָ�� 
      return (current==NULL) ? NULL:current-leftChild;
    }
    BinTreeNode<T>* rightChild(BinTreeNode<T>*current){//��������Ů�ڵ�ָ��
      return (current==NULL) ? NULL:current->rightChild;
    }
    int Height()//�������ĸ߶�
    {

        if(heightval==true)
            return height;
        else
        {
            height=Height(root);
            return height;
        }
        
    }
    int Size(){//���ؽڵ���
      if(size!=0)
        return size;
      else
        return Size(root);
    }
    BinTreeNode<T>* getRoot()const{return root;}//ȡ��
    void preOrder(){previsit(root);};//ǰ�����
    void inOrder(){invisit(root);};//�������
    void postOrder(){posvisit(root);};//�������
    void levelOrder(){levelvisit(root);};//��α���
    int insert(BinTreeNode<T>* pos,const T &item);//������Ԫ��
    BinTreeNode<T>* search(const T &item)const;//����
    void Copy(BinaryTree<T>& tree)//����
    {
        destory(root);
        BinTreeNode<T>* p=tree.getRoot();
        copy(root,p);
    }
    friend ostream& operator<< <>(ostream& out,const BinaryTree<T> &tree); //���������
    friend istream& operator>> <>(istream& in,BinaryTree<T> &tree);//���������
//-------------------------------------------------------------------------------------------------
private:
    BinTreeNode<T> *root;//���ڵ�
    char refvalue;//������Ƿ�
    int height;//����
    bool heightval;//���ߵ���Ч�ԣ�ÿ�ν��в���ɾ��������ֵ����Ϊfalse
    int size;//�ڵ�����
    // void CreatBinTree(istream& in,BinTreeNode<T>* &Root);//���ļ����뽨��������
    //void destory(BinTreeNode<T>* subtree);//�ͷ������ڵĿռ�
    void destory(BinTreeNode<T>* &subtree);//�ͷ������ڵĿռ�
    int Height(BinTreeNode<T>* tree);//����������
    int Size(BinTreeNode<T>* tree);//������ڵ���
    void previsit(BinTreeNode<T>* subtree);//ǰ�����
    void invisit(BinTreeNode<T>* subtree);//�������
    void posvisit(BinTreeNode<T>* subtree);//�������
    void levelvisit(BinTreeNode<T>* subtree);//��α���
    void copy(BinTreeNode<T>*& current,BinTreeNode<T>* subtree);//����
    BinTreeNode<T>* find(BinTreeNode<T>* subtree,const T &item)const;//������������
    void Traverse(ostream& out,BinTreeNode<T>* subtree)const;//ǰ��������

};
//------------------------------------------------------------------------------------------------

template<class T>
int BinaryTree<T>::insert(BinTreeNode<T>* pos,const T& item)//������Ԫ��
{
    T tem=pos->data;
    pos=search(tem);
    if(pos!=NULL)
    {
        if(pos->leftChild==NULL)//����Ϊ��ڵ����
        {    
            pos->leftChild=new BinTreeNode<T>(item);
            pos->leftChild->parent=pos;
            return 0;
        }
        else if(pos->rightChild==NULL)//����Ϊ�ҽڵ����
        {
            pos->rightChild=new BinTreeNode<T>(item);
            pos->rightChild->parent=pos;
            return 1;
        }
        else//���ɲ���
            return -1;
    }
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::search(const T &item)const//����
{ 
    return find(root,item);
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::find(BinTreeNode<T>* subtree,const T &item)const//������������
{
    BinTreeNode<T>* p=NULL;
    if(subtree==NULL)
        return NULL;//δ�ҵ�ʱ�ĵݹ��յ�
    if(subtree->data==item)//�������ڵ��ֵ���
        return subtree;//�ҵ�ʱ�ĵݹ��յ�
    if(p=find(subtree->leftChild,item),p!=NULL)//������Ѱ������
        return p;
    else
        return find(subtree->rightChild,item);//������Ѱ�����������ܻ᷵��NULLֵ
}
// void CreatBinTree(istream& in,BinTreeNode<T>* &Root);//���ļ����뽨��������

/*
template<class T>
void BinaryTree<T>::destory(BinTreeNode<T>* subtree)//�ͷ������ڵĿռ�
{
    if(subtree!=NULL)
    {
        destory(root->leftChild);//ɾ��������
        destory(root->rightChild);//ɾ��������
        delete subtree;//ɾ�������ĸ�
    }
}
*/
template<class T>
void BinaryTree<T>::destory(BinTreeNode<T>* &subtree)//�ͷ������ڵĿռ�
{
    subtree=NULL;
}

template<class T>
int BinaryTree<T>::Height(BinTreeNode<T>* tree)//����������
{
    if(tree==NULL)
        return 0;//�ݹ��յ�
    int left=Height(tree->leftChild);//���������߶�
    int right=Height(tree->rightChild);//���������߶�
    return (left>right? left:right)+1;//������������߶�+1
}

template<class T>
int BinaryTree<T>::Size(BinTreeNode<T>* tree)//������ڵ���
{
    if(tree==NULL)
        return 0;
    else
        return Size(tree->leftChild)+Size(tree->rightChild)+1;//���������Ľڵ���֮���ټ��ϵ�ǰ�������ڵ�
}

template<class T>
void BinaryTree<T>::previsit(BinTreeNode<T>* subtree)//ǰ�����
{
    if(subtree==NULL)
        return;
    cout<<subtree->data<<" ";//������ڵ�
    previsit(subtree->leftChild);//���������
    previsit(subtree->rightChild);//���������
}

template<class T>
void BinaryTree<T>::invisit(BinTreeNode<T>* subtree)//�������
{
    if(subtree==NULL)
        return;
    invisit(subtree->leftChild);//���������
    cout<<subtree->data<<" ";//������ڵ�
    invisit(subtree->rightChild);//���������
}

template<class T>
void BinaryTree<T>::posvisit(BinTreeNode<T>* subtree)//�������
{
    if(subtree==NULL)
        return;
    posvisit(subtree->leftChild);//���������
    posvisit(subtree->rightChild);//���������
    cout<<subtree->data<<" ";//������ڵ�
}

template<class T>
void BinaryTree<T>::levelvisit(BinTreeNode<T>* subtree)//��α���
{
    if(subtree==NULL)
        return;
    queue<BinTreeNode<T>* > que;//��������
    BinTreeNode<T>* p;
    p=subtree;//���ڵ�
    que.push(p);
    while(!que.empty())//����Ϊ��ʱ��������
    {
        int size=que.size();//ĳһ��ڵ������
        for(int i=0;i<size;i++)//���ĳһ������нڵ��ֵ�����˳����У�ͬʱ����һ��ڵ�������
        {
            p=que.front();
            cout<<p->data<<" ";//����ڵ�ֵ
            que.pop();
            if(p->leftChild!=NULL)//�������ӽڵ㣬�������ĩβ
                que.push(p->leftChild);
            if(p->rightChild!=NULL)
                que.push(p->rightChild);//�����Һ��ӽڵ㣬�������ĩβ
        }
    }
}

template<class T>
void BinaryTree<T>::copy(BinTreeNode<T>*& current,BinTreeNode<T>* subtree)//����
{
    if(subtree==NULL)
        return;
    current=new BinTreeNode<T>(subtree->data);//�����������ڵ�
    if(current==NULL)
        cerr<<"fail in allocation"<<endl;
    copy(current->leftChild,subtree->leftChild);//����������
    copy(current->rightChild,subtree->rightChild);//����������
    return;//
}

template<class T>
void BinaryTree<T>::Traverse(ostream& out,BinTreeNode<T>* subtree)const//ǰ��������
{
   if(subtree!=NULL)
   {
       out<<subtree->data<<" ";
       Traverse(out,subtree->leftChild);//���������
       Traverse(out,subtree->rightChild);//���������
   }

}

template<class T>
ostream& operator<< (ostream& out,const BinaryTree<T> &tree)//���������
{
    tree.Traverse(out,tree.root);//ǰ��������
    // out<<endl;
    return out;
}
/*
template<class T>
istream& operator>> (istream& in,BinaryTree<T> &tree)//����������
{
    //R(A(C,D(F(,I),G)),B(,E(H)))#
    //R A C D F I G B E H
    //LinearStack<BinTreeNode<T>* > st;
    // tree.destory(tree.root);
    tree.root=NULL;
    int flag=0; 
    stack<BinTreeNode<T>*> st;
    BinTreeNode<T>* p=NULL;
    BinTreeNode<T>* tem=NULL;
    char ch;
    int k=-1;// 0 ������������1 ����������
    while(in>>ch,ch!=tree.refvalue)
    {
        switch(ch){
            case('('):
            k=0;
            st.push(p);
            if(flag==0)
            {
                tree.root=p;
                flag=1;
            }
            break;//��������ǰ��Ԫ����ջ
            case(','):k=1;break;//���ź��Ԫ�����Һ��ӽڵ�
            case(')'):st.pop();break;//�˳��������ڵ�
            default:
            {
                p=new BinTreeNode<T>(ch);//�½��ڵ�
                if(p==NULL)
                {
                    cerr<<"fail in allocation"<<endl;
                    exit(1);
                }
                if(k==0)
                {
                    //st.getTop(tem);
                    tem=st.top();
                    tem->leftChild=p;//�����������ӵ����ڵ�
                    p->parent=tem;
                }
                if(k==1)
                {
                    //st.getTop(tem);
                    tem=st.top();
                    tem->rightChild=p;//���Һ��ӽڵ����ӵ��������ڵ�
                    p->parent=tem;
                }
            }
        }
    }
    
    return in;
}
*/
template<class T>
istream& operator>> (istream& in,BinaryTree<T> &tree)//����������
{
    LinearStack<BinTreeNode<T>* > st;//����ջ
    tree.root=NULL;
    BinTreeNode<T> *p=NULL,*t=NULL;
    int k=0;
    char ch;
    while(in>>ch,ch!=tree.refvalue)
    {
        switch(ch)
        {
            case('('):st.push(p);k=1;break;//��������ǰ��Ԫ����ջ
            case(')'):st.pop(t);break;
            case(','):k=2;break;//�������һ�ڵ����Һ���
            default: p=new BinTreeNode<T>(ch);
            if(tree.root==NULL)
                tree.root=p;
            else if(k==1)
            {
                st.getTop(t);
                if(t!=NULL)
                {
                    t->leftChild=p;
                    p->parent=t;
                }    
            }
            else{
                   st.getTop(t);
                   if(t!=NULL)
                   {
                       t->rightChild=p;
                       p->parent=t;
                   }
            }
        }
    }
    return in;
}

#endif
