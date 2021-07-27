#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
注意：本项目是参考平衡小车之家的代码改写的，保留原著作信息，对原作者尊重。
**************************************************************************/
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=1; 
int Encoder_Left,Encoder_Right;             //左右编码器的脉冲计数
int Moto1,Moto2; //电机PWM变量 
int Temperature;                            //显示温度
int Voltage;                                //电池电压采样相关的变量
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
u32 Distance;                               //超声波测距
int main(void)
{ 
	Stm32_Clock_Init(9);            //系统时钟设置
	delay_init(72);                 //延时初始化
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //初始化与 LED 连接的硬件接口
	LED=1;
	KEY_Init();                     //按键初始化
	OLED_Init();                    //OLED初始化
	uart_init(72,115200);           //初始化串口1
	uart3_init(9600);            //串口3初始化
	Adc_Init();                     //ADC初始化
	MiniBalance_PWM_Init(7199,0);   //=====初始化PWM 10KHZ 高频可以防止电机低频时的尖叫声
	Encoder_Init_TIM2();            //初始化编码器1 
	Encoder_Init_TIM4();            //初始化编码器2 
	IIC_Init();                     //模拟IIC初始化
  MPU6050_initialize();           //=====MPU6050初始化	
	DMP_Init();                     //初始化DMP     
  Timer1_Init(49,7199);           //=====5MS进一次中断服务函数，中断服务函数在control.c
	while(1)
		{
//*****************整个姿态控制都要在定时中断服务函数中进行，while循环只执行一些不重要的工作，oled显示。
			
					delay_ms(500);//延时减缓数据传输频率，确保通信的稳定
					//Temperature=Read_Temperature();  //===读取MPU6050内置温度传感器数据，近似表示主板温度。	
					oled_show(); //===显示屏打开
					delay_ms(100);	//延时减缓数据传输频率，确保通信的稳定			
		}
}
