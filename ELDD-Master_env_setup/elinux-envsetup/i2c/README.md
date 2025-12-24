# "Linux I2C Drivers" Course Structure

+ docs   -> I2C documents

+ master -> I2C Master - AM3358 I2C Device Controller

	+ u-boot 
	+ kernel
	+ user

+ slave -> I2C Slave - DS1307 

	+ kernel
	+ app
	+ patch


## I2C Slave device on BBB and KM-BBB expansion board

AM3358 have 3 I2C device controllers those are i2c-0, i2c-1 and i2c-2.

BBB have 3 I2C Slave devices those are EEPROM, PMIC and HDMI

KM-BBB expansion board have 3 I2C Slave device those are RTC(DS1307), EEPROM(AT24) and Accelerometer Sensor(ADXL345).



