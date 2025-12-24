

int KM_GPIO_Export(int );
int KM_GPIO_Direction(int, int );
int KM_GPIO_Write(int, int);
main()
{

	KM_GPIO_Export(10);
	KM_GPIO_Direction(10, 1);

while(1)
{
	KM_GPIO_Write(10, 1);
	sleep(1);
	KM_GPIO_Write(10, 0);
	sleep(1);
}


}
