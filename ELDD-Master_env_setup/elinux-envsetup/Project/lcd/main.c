#include<stdio.h>

main()
{
	int ret;
	ret = KM_LCD_Init();
	if (ret < 0)
	printf("KM_LCD_Init Fails\n");

	KM_LCD_ClrScr();
	KM_LCD_Str_XY(3,0,"Kernel");

	KM_LCD_Exit();
}
