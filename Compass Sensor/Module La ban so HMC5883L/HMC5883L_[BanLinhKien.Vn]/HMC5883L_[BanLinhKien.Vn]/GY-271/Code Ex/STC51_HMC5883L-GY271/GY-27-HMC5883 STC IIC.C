//***************************************
// HMC5883 IIC
// 11.0592M
// LCD1602
// Keil uVision2
//
//****************************************
#include  <REG51.H> 
#include  <math.h>    //Keil library
#include  <stdio.h>   //Keil library    
#include  <INTRINS.H>
#define   uchar unsigned char
#define   uint unsigned int 
//--------------------------
#define   DataPort P0
sbit    SCL=P1^0;
sbit    SDA=P1^1;
sbit    LCM_RS=P2^0;
sbit    LCM_RW=P2^1;
sbit    LCM_EN=P2^2;

#define SlaveAddress   0x3C
typedef unsigned char BYTE;
typedef unsigned short WORD;

BYTE BUF[8];
uchar ge,shi,bai,qian,wan;
int  dis_data;

void delay(unsigned int k);
void InitLcd();
void Init_HMC5883(void);

void WriteDataLCM(uchar dataW);
void WriteCommandLCM(uchar CMD,uchar Attribc);
void DisplayOneChar(uchar X,uchar Y,uchar DData);
void conversion(uint temp_data);

void  Single_Write_HMC5883(uchar REG_Address,uchar REG_data);
uchar Single_Read_HMC5883(uchar REG_Address);
void  Multiple_Read_HMC5883();
//------------
void Delay5us();
void Delay5ms();
void HMC5883_Start();
void HMC5883_Stop();
void HMC5883_SendACK(bit ack);
bit  HMC5883_RecvACK();
void HMC5883_SendByte(BYTE dat);
BYTE HMC5883_RecvByte();
void HMC5883_ReadPage();
void HMC5883_WritePage();
//-----------------------------------

//*********************************************************
void conversion(uint temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;
    qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;
    ge=temp_data+0x30;  
}

/*******************************/
void delay(unsigned int k)  
{                       
unsigned int i,j;               
for(i=0;i<k;i++)
{           
for(j=0;j<121;j++)          
{;}}                        
}
/*******************************/
void WaitForEnable(void)    
{                   
DataPort=0xff;      
LCM_RS=0;LCM_RW=1;_nop_();
LCM_EN=1;_nop_();_nop_();
while(DataPort&0x80);   
LCM_EN=0;               
}                   
/*******************************/
void WriteCommandLCM(uchar CMD,uchar Attribc)
{                   
if(Attribc)WaitForEnable(); 
LCM_RS=0;LCM_RW=0;_nop_();
DataPort=CMD;_nop_();   
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}                   
/*******************************/
void WriteDataLCM(uchar dataW)
{                   
WaitForEnable();        
LCM_RS=1;LCM_RW=0;_nop_();
DataPort=dataW;_nop_(); 
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}       
/***********************************/
void InitLcd()              
{           
WriteCommandLCM(0x38,1);    
WriteCommandLCM(0x08,1);    
WriteCommandLCM(0x01,1);    
WriteCommandLCM(0x06,1);    
WriteCommandLCM(0x0c,1);
}           
/***********************************/
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{                       
Y&=1;                       
X&=15;                      
if(Y)X|=0x40;                   
X|=0x80;            
WriteCommandLCM(X,0);       
WriteDataLCM(DData);        
}                       

/**************************************

**************************************/
void Delay5us()
{
             _nop_();_nop_();_nop_();_nop_();
             _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
              _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
             _nop_();_nop_();_nop_();_nop_();

}

/**************************************

**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
**************************************/
void HMC5883_Start()
{
    SDA = 1;
    SCL = 1;
    Delay5us();
    SDA = 0;
    Delay5us();
    SCL = 0;
}

/**************************************
**************************************/
void HMC5883_Stop()
{
    SDA = 0;
    SCL = 1;
    Delay5us();
    SDA = 1;
    Delay5us();
}

/**************************************

**************************************/
void HMC5883_SendACK(bit ack)
{
    SDA = ack;
    SCL = 1;
    Delay5us();
    SCL = 0;
    Delay5us();
}

/**************************************

**************************************/
bit HMC5883_RecvACK()
{
    SCL = 1;
    Delay5us();
    CY = SDA;
    SCL = 0;
    Delay5us();

    return CY;
}

/**************************************

**************************************/
void HMC5883_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)
    {
        dat <<= 1;
        SDA = CY;
        SCL = 1;
        Delay5us();
        SCL = 0;
        Delay5us();
    }
    HMC5883_RecvACK();
}

/**************************************

**************************************/
BYTE HMC5883_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;
    for (i=0; i<8; i++)
    {
        dat <<= 1;
        SCL = 1;
        Delay5us();
        dat |= SDA;
        SCL = 0;
        Delay5us();
    }
    return dat;
}

//***************************************************

void Single_Write_HMC5883(uchar REG_Address,uchar REG_data)
{
    HMC5883_Start();
    HMC5883_SendByte(SlaveAddress);
    HMC5883_SendByte(REG_Address);
    HMC5883_SendByte(REG_data);
    HMC5883_Stop();
}

//*********************************
uchar Single_Read_HMC5883(uchar REG_Address)
{  uchar REG_data;
    HMC5883_Start();
    HMC5883_SendByte(SlaveAddress);
    HMC5883_SendByte(REG_Address);
    HMC5883_Start();
    HMC5883_SendByte(SlaveAddress+1);
    REG_data=HMC5883_RecvByte();
    HMC5883_SendACK(1);   
    HMC5883_Stop();
    return REG_data; 
}
//******************************************************
//

//
//******************************************************
void Multiple_read_HMC5883(void)
{   uchar i;
    HMC5883_Start();
    HMC5883_SendByte(SlaveAddress);
    HMC5883_SendByte(0x03);
    HMC5883_Start();
    HMC5883_SendByte(SlaveAddress+1);
     for (i=0; i<6; i++)
    {
        BUF[i] = HMC5883_RecvByte();
        if (i == 5)
        {
           HMC5883_SendACK(1);
        }
        else
        {
          HMC5883_SendACK(0);
       }
   }
    HMC5883_Stop();
    Delay5ms();
}

//****
void Init_HMC5883()
{
     Single_Write_HMC5883(0x02,0x00);  //
}
//*********************************************************
//
//*********************************************************
void main()
{ // bit sign_bit;
   unsigned int i;
   int x,y,z;
   double angle;

   delay(500);          
   InitLcd();
   Init_HMC5883();
  while(1)
  { 
    Multiple_Read_HMC5883();
//---------
    x=BUF[0] << 8 | BUF[1]; //Combine MSB and LSB of X Data output register
    z=BUF[2] << 8 | BUF[3]; //Combine MSB and LSB of Z Data output register
    y=BUF[4] << 8 | BUF[5]; //Combine MSB and LSB of Y Data output register

    angle= atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
    angle*=10;
    conversion(angle);       //
    DisplayOneChar(2,0,'A'); 
    DisplayOneChar(3,0,':'); 
    DisplayOneChar(4,0,qian); 
    DisplayOneChar(5,0,bai); 
    DisplayOneChar(6,0,shi); 
    DisplayOneChar(7,0,'.'); 
    DisplayOneChar(8,0,ge); 

    for (i=0;i<10000;i++);   //
  }
} 
