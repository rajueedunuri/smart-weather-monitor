#include <stdio.h>

void fun1 (int , int );
void fun2 (int , int );
void fun3 (int , int );

int main ()
{
	//int x,y;
	//x=4;
	//y=5;

	fun1 (4, 5);
	return 0;
}


void fun1 (int a, int b)
{
	int x;
	x = a;
	fun2(6,7);
}

void fun2 (int a, int b)
{
	int x;
	x = a;
	fun3(7,8);
}

void fun3 (int a, int b)
{ 
	int x;
	x = a;
}

