#include <stdio.h>


void fun3()
{
	int x=3;
}
void fun2()
{
	int x=2;
	fun3();
}

void fun1()
{
	int x=1;
	fun2();
}
int main()
{
	int x=0;
	fun1();
	
	return 0;
}
