/*****************************************
* 基于AVR单片机GY-27模块通信程序 		 *
* HMC5883L+ADXL345 通信程序              *
* 功    能：IIC通信读取数据并显示        *
* 时钟频率：内部1M 						 *
* 设    计：广运电子					 *
* 修改日期：2011年4月20日				 *
* 编译环境：ICC-AVR7.14					 *
* 实验环境：ATmega16+1602    			 *
* 使用端口：PC0,PC1,PC6,PC7,PA4~PA7 	 *
* 参    考：莫锦攀实验程序24c02读取实验  *
*****************************************/
#include <iom16v.h>
#include "I2C.h"
#include "1602.h"
#include "delay.h"
#include  "math.h"  
#include  "stdio.h"  
void conversion(unsigned int i);
unsigned char display[5]={0,0,0,0,0};//显示数据

/*********************************************
数据转换,十六进制数据转换成10进制
输入十六进制范围：0x0000-0x270f（0-9999）
结果分成个十百千位，以ascii存入显示区
**********************************************/
void conversion(unsigned int i)  
{  
 	display[0]=i/10000+0x30 ;
    i=i%10000;    //取余运算
	display[1]=i/1000+0x30 ;
    i=i%1000;    //取余运算
    display[2]=i/100+0x30 ;
    i=i%100;    //取余运算
    display[3]=i/10+0x30 ;
   i=i%10;     //取余运算
    display[4]=i+0x30;  
}
//*******************************
//显示角度
void display_angle(void)
{   float temp;
      int x,y;
	 double angle;

     x=I2C_Read(0x03);
     x=(x<<8)+I2C_Read(0x04);
	 
	 y=I2C_Read(0x07);
     y=(y<<8)+I2C_Read(0x08);
	
	 
     angle= atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
     angle*=10;

    conversion(angle);          //转换出显示需要的数据
	LCD_write_char(0,0,'A');   //第0行，第0列 显示A
	LCD_write_char(1,0,'n');   //
	LCD_write_char(2,0,'g');   //
	LCD_write_char(3,0,'l');   //
	LCD_write_char(4,0,'e');   //
    LCD_write_char(5,0,':'); 
    LCD_write_char(6,0,display[1]);  
    LCD_write_char(7,0,display[2]); 
    LCD_write_char(8,0,display[3]); 
    LCD_write_char(9,0,'.'); 
	LCD_write_char(10,0,display[4]); 
	LCD_write_char(11,0,0xdf); 
	
}

/*******************************
主程序
*******************************/
void main(void)
{	
	unsigned char i;		
	 delay_nms(50);          //lcd上电延时
	 LCD_init();             //lcd初始化
     
	while(1){               //循环  
	I2C_Write(0x02,0x00);   //模式寄存器写0
	delay_nms(50); 
	display_angle();       //显示角度
	delay_nms(50); 	
    }
}

