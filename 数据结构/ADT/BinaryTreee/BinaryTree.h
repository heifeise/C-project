/*
	功能：二叉树的存储实现
	输入：无
	输出：无

	编译环境：windows11  visual stdion code 1.62.0
	开发注释：叶晶 
	修订日期：2021年11月5日 

	参考文献：殷人昆《数据结构(用面向对象方法与C++语言描述)(第2版)》,
	版次：2007年6月第2版	页码：PP195-210
	印次：2020年7月第23次印刷
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
struct BinTreeNode{//二叉树节点定义
    T data;//数据域
    BinTreeNode<T>* leftChild;
    BinTreeNode<T>* rightChild;//左右子女指针域 <T>
    BinTreeNode<T>* parent;
    BinTreeNode()//构造函数
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
ostream& operator<< (ostream& out,const BinaryTree<T> &tree); //重载输出流
template<class T>
istream& operator>> (istream& in,BinaryTree<T> &tree);//重载输出流
//----------------------------------------------------------------------------------------------------------------
template<class T>
class BinaryTree{//二叉树类的定义
public:
    BinaryTree(){//构造函数
        root=NULL;
        refvalue='#';
        height=0;
		size=0;
		heightval=false;
    }
    explicit BinaryTree(char x)//构造函数
    {
    	refvalue=x;
		root=NULL;
		height=0;
		size=0;
		heightval=false;
	}
    explicit BinaryTree(BinaryTree<T> &Tree)//复制构造函数
    {
	
    	BinTreeNode<T>* p=Tree.getRoot();
        copy(root,p);
    }
    ~BinaryTree(){//析构函数
        destory(root);
    }
    bool IsEmpty(){//判断二叉树是否为空
        return (root==NULL) ? true:false;
    }
    BinTreeNode<T>* Parent(BinTreeNode<T>* current){//返回父节点指针
      return current->parent;
    }
    BinTreeNode<T>* leftChild(BinTreeNode<T>* current){//返回左子女节点指针 
      return (current==NULL) ? NULL:current-leftChild;
    }
    BinTreeNode<T>* rightChild(BinTreeNode<T>*current){//返回右子女节点指针
      return (current==NULL) ? NULL:current->rightChild;
    }
    int Height()//返回树的高度
    {

        if(heightval==true)
            return height;
        else
        {
            height=Height(root);
            return height;
        }
        
    }
    int Size(){//返回节点数
      if(size!=0)
        return size;
      else
        return Size(root);
    }
    BinTreeNode<T>* getRoot()const{return root;}//取根
    void preOrder(){previsit(root);};//前序遍历
    void inOrder(){invisit(root);};//中序遍历
    void postOrder(){posvisit(root);};//后序遍历
    void levelOrder(){levelvisit(root);};//层次遍历
    int insert(BinTreeNode<T>* pos,const T &item);//插入新元素
    BinTreeNode<T>* search(const T &item)const;//搜索
    void Copy(BinaryTree<T>& tree)//复制
    {
        destory(root);
        BinTreeNode<T>* p=tree.getRoot();
        copy(root,p);
    }
    friend ostream& operator<< <>(ostream& out,const BinaryTree<T> &tree); //重载输出流
    friend istream& operator>> <>(istream& in,BinaryTree<T> &tree);//重载输出流
//-------------------------------------------------------------------------------------------------
private:
    BinTreeNode<T> *root;//根节点
    char refvalue;//结束标记符
    int height;//树高
    bool heightval;//树高的有效性，每次进行插入删除操作后，值更改为false
    int size;//节点数量
    // void CreatBinTree(istream& in,BinTreeNode<T>* &Root);//从文件读入建立二叉树
    //void destory(BinTreeNode<T>* subtree);//释放树所在的空间
    void destory(BinTreeNode<T>* &subtree);//释放树所在的空间
    int Height(BinTreeNode<T>* tree);//遍历求树高
    int Size(BinTreeNode<T>* tree);//遍历求节点数
    void previsit(BinTreeNode<T>* subtree);//前序遍历
    void invisit(BinTreeNode<T>* subtree);//中序遍历
    void posvisit(BinTreeNode<T>* subtree);//后序遍历
    void levelvisit(BinTreeNode<T>* subtree);//层次遍历
    void copy(BinTreeNode<T>*& current,BinTreeNode<T>* subtree);//复制
    BinTreeNode<T>* find(BinTreeNode<T>* subtree,const T &item)const;//在子树中搜索
    void Traverse(ostream& out,BinTreeNode<T>* subtree)const;//前序遍历输出

};
//------------------------------------------------------------------------------------------------

template<class T>
int BinaryTree<T>::insert(BinTreeNode<T>* pos,const T& item)//插入新元素
{
    T tem=pos->data;
    pos=search(tem);
    if(pos!=NULL)
    {
        if(pos->leftChild==NULL)//可作为左节点插入
        {    
            pos->leftChild=new BinTreeNode<T>(item);
            pos->leftChild->parent=pos;
            return 0;
        }
        else if(pos->rightChild==NULL)//可作为右节点插入
        {
            pos->rightChild=new BinTreeNode<T>(item);
            pos->rightChild->parent=pos;
            return 1;
        }
        else//不可插入
            return -1;
    }
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::search(const T &item)const//搜索
{ 
    return find(root,item);
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::find(BinTreeNode<T>* subtree,const T &item)const//在子树中搜索
{
    BinTreeNode<T>* p=NULL;
    if(subtree==NULL)
        return NULL;//未找到时的递归终点
    if(subtree->data==item)//子树根节点的值相等
        return subtree;//找到时的递归终点
    if(p=find(subtree->leftChild,item),p!=NULL)//遍历搜寻左子树
        return p;
    else
        return find(subtree->rightChild,item);//遍历搜寻右子树，可能会返回NULL值
}
// void CreatBinTree(istream& in,BinTreeNode<T>* &Root);//从文件读入建立二叉树

/*
template<class T>
void BinaryTree<T>::destory(BinTreeNode<T>* subtree)//释放树所在的空间
{
    if(subtree!=NULL)
    {
        destory(root->leftChild);//删除左子树
        destory(root->rightChild);//删除右子树
        delete subtree;//删除子树的根
    }
}
*/
template<class T>
void BinaryTree<T>::destory(BinTreeNode<T>* &subtree)//释放树所在的空间
{
    subtree=NULL;
}

template<class T>
int BinaryTree<T>::Height(BinTreeNode<T>* tree)//遍历求树高
{
    if(tree==NULL)
        return 0;//递归终点
    int left=Height(tree->leftChild);//求左子树高度
    int right=Height(tree->rightChild);//求右子树高度
    return (left>right? left:right)+1;//返回最大子树高度+1
}

template<class T>
int BinaryTree<T>::Size(BinTreeNode<T>* tree)//遍历求节点数
{
    if(tree==NULL)
        return 0;
    else
        return Size(tree->leftChild)+Size(tree->rightChild)+1;//左右子树的节点数之和再加上当前子树根节点
}

template<class T>
void BinaryTree<T>::previsit(BinTreeNode<T>* subtree)//前序遍历
{
    if(subtree==NULL)
        return;
    cout<<subtree->data<<" ";//输出根节点
    previsit(subtree->leftChild);//输出右子树
    previsit(subtree->rightChild);//输出左子树
}

template<class T>
void BinaryTree<T>::invisit(BinTreeNode<T>* subtree)//中序遍历
{
    if(subtree==NULL)
        return;
    invisit(subtree->leftChild);//输出右子树
    cout<<subtree->data<<" ";//输出根节点
    invisit(subtree->rightChild);//输出左子树
}

template<class T>
void BinaryTree<T>::posvisit(BinTreeNode<T>* subtree)//后序遍历
{
    if(subtree==NULL)
        return;
    posvisit(subtree->leftChild);//输出右子树
    posvisit(subtree->rightChild);//输出左子树
    cout<<subtree->data<<" ";//输出根节点
}

template<class T>
void BinaryTree<T>::levelvisit(BinTreeNode<T>* subtree)//层次遍历
{
    if(subtree==NULL)
        return;
    queue<BinTreeNode<T>* > que;//辅助队列
    BinTreeNode<T>* p;
    p=subtree;//根节点
    que.push(p);
    while(!que.empty())//队列为空时遍历结束
    {
        int size=que.size();//某一层节点的数量
        for(int i=0;i<size;i++)//输出某一层的所有节点的值，并退出队列，同时将下一层节点带入队列
        {
            p=que.front();
            cout<<p->data<<" ";//输出节点值
            que.pop();
            if(p->leftChild!=NULL)//当有左孩子节点，带入队列末尾
                que.push(p->leftChild);
            if(p->rightChild!=NULL)
                que.push(p->rightChild);//当有右孩子节点，带入队列末尾
        }
    }
}

template<class T>
void BinaryTree<T>::copy(BinTreeNode<T>*& current,BinTreeNode<T>* subtree)//复制
{
    if(subtree==NULL)
        return;
    current=new BinTreeNode<T>(subtree->data);//复制子树根节点
    if(current==NULL)
        cerr<<"fail in allocation"<<endl;
    copy(current->leftChild,subtree->leftChild);//复制左子树
    copy(current->rightChild,subtree->rightChild);//复制右子树
    return;//
}

template<class T>
void BinaryTree<T>::Traverse(ostream& out,BinTreeNode<T>* subtree)const//前序遍历输出
{
   if(subtree!=NULL)
   {
       out<<subtree->data<<" ";
       Traverse(out,subtree->leftChild);//输出左子树
       Traverse(out,subtree->rightChild);//输出右子树
   }

}

template<class T>
ostream& operator<< (ostream& out,const BinaryTree<T> &tree)//重载输出流
{
    tree.Traverse(out,tree.root);//前序遍历输出
    // out<<endl;
    return out;
}
/*
template<class T>
istream& operator>> (istream& in,BinaryTree<T> &tree)//重载输入流
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
    int k=-1;// 0 代表左子树，1 代表右子树
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
            break;//将左括号前的元素入栈
            case(','):k=1;break;//逗号后的元素是右孩子节点
            case(')'):st.pop();break;//退出子树根节点
            default:
            {
                p=new BinTreeNode<T>(ch);//新建节点
                if(p==NULL)
                {
                    cerr<<"fail in allocation"<<endl;
                    exit(1);
                }
                if(k==0)
                {
                    //st.getTop(tem);
                    tem=st.top();
                    tem->leftChild=p;//将左子树连接到根节点
                    p->parent=tem;
                }
                if(k==1)
                {
                    //st.getTop(tem);
                    tem=st.top();
                    tem->rightChild=p;//将右孩子节点连接到子树根节点
                    p->parent=tem;
                }
            }
        }
    }
    
    return in;
}
*/
template<class T>
istream& operator>> (istream& in,BinaryTree<T> &tree)//重载输入流
{
    LinearStack<BinTreeNode<T>* > st;//辅助栈
    tree.root=NULL;
    BinTreeNode<T> *p=NULL,*t=NULL;
    int k=0;
    char ch;
    while(in>>ch,ch!=tree.refvalue)
    {
        switch(ch)
        {
            case('('):st.push(p);k=1;break;//将左括号前的元素入栈
            case(')'):st.pop(t);break;
            case(','):k=2;break;//输入的下一节点是右孩子
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
