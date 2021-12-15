#include"wordsearch.h"
class findwords{
    public:
        findwords();//构造函数
        findwords(string address);//构造函数
        findwords(string address,string end);//构造函数
        void inputAddress();//输入文件所在的目录,并且打开文件，读入
        void inputPattern();//输入字符串
        bool compare(string patt,string word);//比较两个单词是否是由同一个字母序列构成
        void changeString(char* array,string str);//将string类型的字符串装换为char类型
        void print();//将结果打印到屏幕
        char getmin(char*);//得到字符串中的最小字符
    private:
        int patternLen;//记录需要查找的单词的长度
        string pattern;//需要查找的单词
        string end;//输入结束符，默认为'#'
        string address;//文件地址
};

findwords::findwords()//构造函数
{
    patternLen = 0;
    pattern = "";
    end = "#";
    address = "";
}

findwords::findwords(string address)//构造函数
{
    patternLen = 0;
    pattern = "";
    end = "#";
    this->address = address;
}

findwords::findwords(string address,string end)//构造函数
{
    patternLen = 0;
    pattern = "";
    this->address = address;
    this->end = end;
}

void findwords::inputAddress()//输入文件所在的目录,并且打开文件，读入
{
    cout<<"please input the address of txt(seperated by '/'):"<<endl;
    string temp;
    cin>>temp;//输入文件目录
    // cout<<temp<<endl;
    if(regex_match(temp,regex("^(.+[/])+.+\\.[(txt)(dat)]+?$",regex::icase)))//合法性判断
        address = temp;
    else throw Myexception("please input in correct syntax!");
    // cout<<"here!"<<endl;
}

void findwords::inputPattern()//输入单词
{
    cout<<"please input your word:"<<endl; 
    string temp;
    cin>>temp;
    if(regex_match(temp,regex("^[a-z]+|(\\s*#)$",regex::icase)))//合法性判断
    {
        pattern = temp;
        patternLen = pattern.length();//记录长度
    }
    else throw Myexception("please input in correct syntax!");
}

bool findwords::compare(string patt,string word)//比较两个单词是否是由同一个字母序列构成
{
    if(patternLen != word.length())//长度不相等直接返回false
    {
        return false;
    }
    if(patt == ""||word == "")
        throw Myexception("Array is empty!");
    char pattern_char[patternLen];
    changeString(pattern_char,patt);//将从键盘输入的字符串由string类型转化为char[]类型
    MinHeap<char> patt_heap(pattern_char,patternLen);//放入堆
    char word_char[word.length()];
    changeString(word_char,word);//将从文件读入的字符串由string类型转化为char[]类型
    MinHeap<char> word_heap(word_char,strlen(word_char));//放入堆
    for(int i = 0;i < patternLen;i++)//从最小字母开始比较，直到比较完整个字符串
    {
        char x, y;
        patt_heap.Remove(x);//取最小字符
        word_heap.Remove(y);//取最小字符
        if(x != y)
        {
            return false;
        }
    }
    return true;
}

void findwords::changeString(char* array,string str)//将string类型的字符串装换为char类型
{

    strncpy(array,str.c_str(),str.length()+1);
    for(int i = 0;i < strlen(array);i++)//小写转换
    {
        if(array[i] < 'a')
            array[i] += 32;
    }
}

void findwords::print()
{
    inputAddress();//输入文件目录
    ifstream fp;//创建文件输入流对象
    fp.open(address,ios::in);//以读取的方式打开文件
    // cout<<"here!";
    if(!fp.is_open())//确认文件是否打开
        throw Myexception("fail in opening a file!");
    while(true)
    {
        inputPattern();//输入需要查找的单词
        if(regex_match(pattern,regex("^.*#$")))//结束输入
            break;
        cout<<"*****"<<endl;
        string buffer;
        int sum = 0;
        while(getline(fp,buffer))//读入一行（一个单词）
        {
            if(compare(pattern,buffer))//比对构成两个单词的字母序列是否相等，相等则输出
            {
                cout<<buffer<<endl;
                sum++;
            }
        }
        if(sum == 0)//未找到该序列构成的单词
            cout<<"NOT A VALID WORD"<<endl;
        cout<<"*****"<<endl;
        // cout<<"seek:"<<fp.tellg()<<endl;
        fp.clear();
        fp.seekg(0,ios::beg);//将输入流指针定位到文件开头
        // cout<<"seek:"<<fp.tellg()<<endl;
    }
    fp.close();
}