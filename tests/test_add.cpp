#include <iostream>
#include <cassert>

int add(int, int);

int main(int argc, char **argv)
{
    int arg1 = 10;
    int arg2 = 20;
    int result = add(arg1, arg2);

    assert(result == 30);

    return 0;
}

int add(int x, int y)
{
    return x + y;
}