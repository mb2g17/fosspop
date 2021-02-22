#include <iostream>
#include <cassert>

int subtract(int, int);

int main(int argc, char **argv)
{
    int arg1 = 70;
    int arg2 = 40;
    int result = subtract(arg1, arg2);

    assert(result == 30);

    return 0;
}

int subtract(int x, int y)
{
    return x - y;
}