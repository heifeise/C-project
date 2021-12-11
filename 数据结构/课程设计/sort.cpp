#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(int a, int b)
{
    return a>b;
}

int main()
{
    string str[6] = {"bac","bca","cab","cba","abc","acb"};
    sort(str,str+6);
	for(string x:str)
    	cout<<x<<endl;
    return 0;
}

