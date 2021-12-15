#include"wordsearch.cpp"
int main()
{   
    findwords find;
    try{
        find.print();
    }catch(Myexception& e)
    {
        e.what();
    }
    return 0;
}