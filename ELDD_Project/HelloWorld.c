#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "HelloWorld.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void show_menu(void);
void show_choice(void);
int get_time_date(struct rtc_time *);
void LCD_Testcase(void);
void KM_BBB_GPIO_Init(void);
void KM_BBB_GPIO_Exit(void);

int main(int argc, char *argv[])
{
  int fd2, retval;
  struct rtc_time rtc_tm; 
  int fd3, retval_1;
  int choice;

  int fd;
  int fd1;
  int i = 0;
  int j = 0;
  int n = 12;
  int count = 5;

           char c;
           char buff[5];
	   char buff1[5];

           int ret;
           int Dout = 0;

           float Vref = 1.8;
           float Step_Size;
	   float Vin;
           float temp;
           char Rx_Buff[10];
	   char Rx_Buff1[10];
	   char Rx_Buff2[50];
	   const char *rtc_dev = "/dev/rtc";

        KM_BBB_GPIO_Init();   //LCD, Buzzer Initalization
        KM_LCD_Init();
	KM_GPIO_Write(9,1); // BUZZER ON
        sleep(2);           // 2 sec delay
	KM_GPIO_Write(9,0); // BUZZER OFF
	
	 fd = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY);
           if (fd == -1) {
               fprintf(stderr, "Failed to open you have to load updated modules !\n");
               return(-1);
            }
        fd1 = open("/sys/bus/iio/devices/iio:device0/in_voltage1_raw",O_RDONLY);
            if (fd1 == -1) {
                fprintf(stderr, "Failed to open you have to load updated modules !\n");
                return(-1);
            }

	// /* Creating a file descriptor for RTC */
        // fd2 = open(rtc_dev, O_RDONLY);
        // if (fd2 == -1) {
        //        perror("Requested device cannot be opened!");
        //        _exit(errno);
        // }

/**********************************Set_Time***************************/
	 fprintf(stdout, "\n\t\t\tTWL4030 RTC Driver Test\n\n");
         fflush(stdout);
 
         /* Creating a file descriptor for RTC */
         fd3 = open(rtc_dev, O_RDONLY);
         if (fd3 == -1) {
                 perror("Requested device cannot be opened!");
                 _exit(errno);
         }
 
         /* Displaying Menu */
         show_choice();
 
         /* Getting choice */
         scanf("%d", &choice);
         if (choice) {
                 rtc_tm.tm_sec = 45;     /* second */
                 rtc_tm.tm_min = 59;     /* minute */
                 rtc_tm.tm_hour = 23;    /* hour */
                 rtc_tm.tm_mday = 31;    /* day of the month */
                 rtc_tm.tm_mon = 11;     /* month Jan=0, Feb=1 ... */
                 rtc_tm.tm_year = 104;   /* = year - epoch */
         } else if (choice == 0) {
                 printf("\n");
                 get_time_date(&rtc_tm);
         }
 
         retval_1 = ioctl(fd3, RTC_SET_TIME, &rtc_tm);
         if (retval_1 == -1) {
                 printf("\nFailed setting RTC Date/Time!");
                 perror("ioctl");
                 show_menu();
                 _exit(errno);
         } else {
                 printf("\nSuccessful setting RTC Date/Time!");
         }
 
         /* Reading Current RTC Date/Time */
         retval_1 = ioctl(fd3, RTC_RD_TIME, &rtc_tm);
         if (retval_1 == -1) {
                 perror("ioctl");
                 _exit(errno);
         }
 
         fprintf(stdout,
                 "\n\nNew RTC Date/Time: %d-%d-%d %02d:%02d:%02d\n\n",
                 rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
                 rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
         fflush(stdout);
         close(fd3);

	
/************************************Set_Time**********************************/

/************************************Get_Time**********************************/
/* Creating a file descriptor for RTC */
         fd2 = open(rtc_dev, O_RDONLY);
         if (fd2 == -1) {
                 perror("Requested device cannot be opened!");
                 _exit(errno);
         }

/**************************************Get_Time********************************/
 while(1){
 	HD44780_ClrScr();
	retval = ioctl(fd2, RTC_RD_TIME, &rtc_tm);
         if (retval == -1) {
                 perror("ioctl");
                 _exit(errno);
         }
         fprintf(stdout, "\n %d-%d-%d %02d:%02d:%02d\n\n",
                 rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
                 rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
         fflush(stdout);
         fflush(stdout);
         fflush(stdout);
        // close(fd2);

 	j = 0;
 	Dout = 0;
 	sleep(2);
  
 	buff[3] = '\0';
 	buff1[4] = '\0';
 		
	lseek( fd, 0,SEEK_SET);
 	if((ret = read(fd, buff, 3)) <0){
  	perror("read error:");
  	close(fd);
  	exit(1);
 	}
 	while(j !=3){
   	Dout = (Dout*10)+((buff[j] - 0x30));
   	i++;
   	j++;
 	}
  		
	Step_Size = Vref /4096;
  	Vin = Dout * Step_Size;
  	temp = Vin *100 ;              //use y= mx+c 
  /****************************************Commented on 21-04-2025************************/
   		//sprintf("temp: %.2fV", temp);
		// HD44780_ClrScr();
		sprintf(Rx_Buff,"temp%.2f*C",temp);
        //  	HD44780_Str_XY(0,0,Rx_Buff);
 		printf("temp: %.2f*c\t", temp);
  
  /****************************************Commented on 21-04-2025************************/
  	lseek( fd1, 0,SEEK_SET);
  	if((ret= read(fd1, buff1, 4)) <0){
    	perror("read error:");
   	close(fd1);
   	exit(1);
   	} 
	HD44780_ClrScr();  
	sprintf(Rx_Buff1,"POT:%sV",buff1);
	HD44780_Str_XY(0,0,Rx_Buff);  //Temp
        HD44780_Str_XY(1,0,Rx_Buff1); //Volt
	printf("POT:%sV\n",buff1);
	sleep(1);
	sprintf(Rx_Buff2, "%d-%d-%d %02d:%02d:%02d",rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
                 rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
	HD44780_Str_XY(0,0,Rx_Buff2); //Time
	sleep(1);
    	}
      KM_BBB_GPIO_Exit();   //LCD, Buzzer Uninitalization

	return 0;
}
 void show_menu(void)
 {
         int i = 0;
         printf("\n");
         for (i = 0; i++ < 40;)
                 printf("*");
         printf("\n");
         printf("*\tSet Date Demo\t");
         printf("\n");
         for (i = 0; i++ < 40;)
                 printf("*");
         printf("\n");
         printf("*\tUsage : Date format MMDDYY\n");
         printf("*\tUsage : Time format HHMMSS\n");
         for (i = 0; i++ < 40;)
                 printf("*");
         printf("\n");
 }
 
 void show_choice(void)
 {
         printf("\nSet date and time options:\n");
	 printf("Enter 0 -> to accept date and time from user\n");
         printf("Enter 1 -> to use default date and time\n");
         printf("Choice:");
 }
 int get_time_date(struct rtc_time *rtc_tm)
 {
         char date_str[7] = { 0 };
         char time_str[7] = { 0 };
         int num; 
         unsigned char data[6] = { 0 };
         int i;
 
         show_menu();
         printf("Enter Date:");
         scanf("%s", date_str);
         printf("Enter Time:");
         scanf("%s", time_str);
         num = atoi(date_str);
         for (i = 0; i < 3; i++) {
                 data[i] = num % 10;
                 num /= 10; 
                 data[i] += (num % 10) * 10;
                 num /= 10;
                 /*printf ("data[%d] : %d\n", i, data[i]);*/
         }
         num = atoi(time_str);
         for (; i < 6; i++) {
                 data[i] = num % 10;
                 num /= 10; 
                data[i] += (num % 10) * 10;
                 num /= 10;
                 /* printf ("data[%d] : %d\n", i, data[i]);*/
         }
        rtc_tm->tm_mday = data[1]; 
         rtc_tm->tm_mon = data[2] - 1;
         rtc_tm->tm_year = data[0] + 100;
         rtc_tm->tm_hour = data[5];
         rtc_tm->tm_min = data[4];
         rtc_tm->tm_sec = data[3];
 
         return 0;
 }
void LCD_Testcase(void){
  
         HD44780_ClrScr();
         HD44780_Str_XY(0,3,"WELCOME TO");
         HD44780_Str_XY(1,0,"Device drivers");
 }
 
 
void KM_BBB_GPIO_Init(void) 
 {
         KM_GPIO_Export(44); // LCD_D4
         KM_GPIO_Direction(44,1);// Set output direction
         KM_GPIO_Export(45); // LCD_D5
         KM_GPIO_Direction(45,1);// Set output direction
         KM_GPIO_Export(46); // LCD_D6
         KM_GPIO_Direction(46,1);// Set output direction
         KM_GPIO_Export(47); // LCD_D7
         KM_GPIO_Direction(47,1);// Set output direction
         KM_GPIO_Export(86); // LCD_RS
        KM_GPIO_Direction(86,1);// Set output direction
         KM_GPIO_Export(87); // LCD_RW
         KM_GPIO_Direction(87,1);// Set output direction
         KM_GPIO_Export(88); // LCD_EN
         KM_GPIO_Direction(88,1);// Set output direction
         KM_GPIO_Export(9); // BUZZER
         KM_GPIO_Direction(9,1);// Set output direction
 }
void KM_BBB_GPIO_Exit(void)
 {
         KM_GPIO_Unexport(44);
         KM_GPIO_Unexport(45);
        KM_GPIO_Unexport(46);
         KM_GPIO_Unexport(47);
         KM_GPIO_Unexport(86);
         KM_GPIO_Unexport(87);
         KM_GPIO_Unexport(88);
         KM_GPIO_Unexport(9); // BUZZER
 }

