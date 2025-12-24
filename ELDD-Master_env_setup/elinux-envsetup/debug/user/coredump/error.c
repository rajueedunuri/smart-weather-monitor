#include <stdio.h>
void fun()
{
    int *ptr = 0;
    *ptr = 7;
}

int main()
{
    fun();
    return 0;
}
