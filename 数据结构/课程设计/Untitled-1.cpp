#include<iostream>
#include<fstream>
using namespace std;
/*
【问题描述】
给定一个小写字母序列，最少一个字母，最多6个字母，在一个指定的字典中找出能由这个字母序列构成的英文单词，例如：给出aptr,可能找到的单词是part、tarp、trap等（有多少单词取决于字典中包含的单词），如果在字典中找不到由字母序列构成的单词则输出“NOT A VALID WORD”。
【基本要求】
先输入一本字典（建议用一个文件存放字典），字典中至少包含100个以上的单词（注意单词的多样性），每个单词占一行，字典中的单词是无序的，每个单词只出现一次，所有单词都是小写的。输入多个字母序列(最后输入#，表示结束)，找出它们对应的单词，如果找到的单词不止一个，输出时要按字典序依次输出，每行输出一个单词，每输出一组对应的单词后就输出一行星号“******”（6个）。
【测试数据】
(1) 输入：
resco
aptr
tset
oresuc
    #
输出：
    score         //在字典中只找到1个单词
******
part          //在字典中找到3个单词,按字典序输出这3个单词
tarp
trap
******
NOT A VALID WORD   //在字典中没找到对应的单词
******
course
******
(2) 自己编写一组测试数据  
【实现提示】
 排序+搜索
*/

int main()
{
    ifstream fp;
    string buffer;
    fp.open("D:/file/project/C++/hello.txt",ios::in);
    if(!fp.is_open())
        cout<<"fail"<<endl;
    else
    {
        while(getline(fp,buffer))
        {
            cout<<buffer<<endl;
            cout<<buffer.length()<<endl;
        }
    }
    fp.close();
    return 0;
}