#include <iostream>

#include <unistd.h>
using namespace std;

class A
{
public:
    A() { cout << "A" << endl; }
    ~A() { cout << "~A" << endl; }
    A(int n)
    {
    }
};

A a;


