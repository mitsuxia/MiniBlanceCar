#include "show.h"
  /**************************************************************************
作者：平衡小车之家
注意：本项目是参考平衡小车之家的代码改写的，保留原著作信息，对原作者尊重。
**************************************************************************/
unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{
		OLED_Display_On();  //显示屏打开
		//=============显示滤波器=======================//	
		                      OLED_ShowString(00,0,"Made in China");
		                     // OLED_ShowNumber(30,0,Way_Angle ,5,12);//
//	       if(Way_Angle==1)	OLED_ShowString(45,0,"DMP");
//		else if(Way_Angle==2)	OLED_ShowString(45,0,"Kalman");
//		else if(Way_Angle==3)	OLED_ShowString(45,0,"Hubu");
		//=============显示温度=======================//	
//	OLED_ShowString(00,15,"Wendu:");
//		                      OLED_ShowNumber(45,15,Temperature/10,2,12);
//		                      OLED_ShowNumber(68,15,Temperature-4%10,1,12);
//		                      OLED_ShowString(58,15,".");
//		                      OLED_ShowString(80,15,"`C");
		//=============显示编码器1=======================//	
	OLED_ShowString(00,25,"Enco1:");
		if( Encoder_Left<0)		OLED_ShowString(45,25,"-"),
		                      OLED_ShowNumber(65,25,-Encoder_Left,5,12);
		else                 	OLED_ShowString(45,25,"+"),
		                      OLED_ShowNumber(65,25, Encoder_Left,5,12);
  	//=============显示编码器2=======================//		
		OLED_ShowString(00,35,"Enco2:");
		if(Encoder_Right<0)		OLED_ShowString(45,35,"-"),
		                      OLED_ShowNumber(65,35,-Encoder_Right,5,12);
		else               		OLED_ShowString(45,35,"+"),
		                      OLED_ShowNumber(65,35,Encoder_Right,5,12);	
		//=============显示电压======================//
		                      OLED_ShowString(00,45,"Volta");
		                      OLED_ShowString(58,45,".");
		                      OLED_ShowString(80,45,"V");
		                      OLED_ShowNumber(45,45,Voltage/100,2,12);
		                      OLED_ShowNumber(68,45,Voltage%100,2,12);
		 if(Voltage%100<10) 	OLED_ShowNumber(62,45,0,2,12);
		//=============显示角度=======================//
		OLED_ShowString(0,15,"Angle:");
		if(Angle_Balance<0)		OLED_ShowNumber(50,15,Angle_Balance+360,3,16);
		else					        OLED_ShowNumber(50,15,Angle_Balance,3,16);
		//=============刷新=======================//
		OLED_Refresh_Gram();	
	}
