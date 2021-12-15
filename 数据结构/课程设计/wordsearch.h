#ifndef WORDSEARCH_H
#define WORDSEARCH_H
#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include<stdlib.h>
#include<exception>
#include"MinHeap.cpp"
using namespace std;
//addres:D:/file/project/C++/数据结构/课程设计/test.txt 
class Myexception:public exception{//自定义异常
    public:
    Myexception()
        {
            word = "error!";
        }
        Myexception(string str)
        {
            word = str;
        }
        const char* what() const throw()
        {
            cout<<word<<endl;
            return "error!";
        }
    private:
        string word;
};

#endif