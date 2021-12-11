/*
	功能：简单图的存储实现
	输入：图的结点和带权边
	输出：图的广度优先遍历

	编译环境：windows11  visual stdion code 1.62.0
	开发注释：叶晶 
	修订日期：2021年11月27日 

	参考文献：殷人昆《数据结构(用面向对象方法与C++语言描述)(第2版)》
	版次：2007年6月第2版	页码：PP355-366
	印次：2020年7月第23次印刷
*/
#include<iostream>
#include<cstring>
#include"LinkedList.h"
#include"GraphLink.h"
using namespace std;
int main()
{
    Graphlink<char, int> graph;
	cin>>graph;
	cout<<graph;
    return 0;
}
