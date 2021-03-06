/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Sensor.h
 * 描	述	：传感器类
 *                    
 * 实验平台	：
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：
 * 创建时间	：2016.9.28
 * 最后编辑	：2016.9.28
  **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

#ifndef __SENSOR_H_
#define __SENSOR_H_

/****************************包含头文件*******************************************/
#include "FSMC.h"
#include "exti.h"
#include "cpp_Math.h"
#
/****************************宏定义***********************************************/
/*
REG_STA :    bit4				 bit3				 bit2				bit1		 bit0
					Ultras_Rdy	Press_Rdy		OPTF_Rdy		Mag_Rdy		MIU_Rdy
状态寄存器的各个位定义*/
#define MIU_RDY					0x01
#define MAG_RDY					0x02
#define OPTF_RDY				0x04
#define PRESS_RDY				0x08
#define ULTRS_RDY				0x10

//====================读写16位的地址===================
#define REG_CMD					150u
#define REG_STA					151u				//
#define REG_PWM1				152u
#define REG_PWM2				153u
#define REG_PWM3				154u
#define REG_PWM4				155u
#define REG_PWM5				156u
#define REG_PWM6				157u
#define REG_PWM7				158u
#define REG_PWM8				159u
#define OPFL_MOTION				160u
#define OPFL_SQUARL				161u
#define OPFL_DX					162u
#define OPFL_DY					163u
#define ALT_ULTRA				164u
//====================只读32位的地址===================
#define ACC_X					0u
#define ACC_Y					1u
#define ACC_Z					2u
#define TMPER					3u
#define GYRO_X					4u
#define GYRO_Y					5u
#define GYRO_Z					6u
#define MAG_X					7u
#define MAG_Y					8u
#define MAG_Z					9u
#define ALT_PRESS				10u


#define MPU_TIMESP_L			11u
#define MPU_TIMESP_H			12u

#define ADNS_TIMESP_L			13u
#define ADNS_TIMESP_H			14u

#define ARP_TIMESP_L			15u
#define ARP_TIMESP_H			16u

#define ULT_TIMESP_L			17u
#define ULT_TIMESP_H			18u

#define G							9.8065				 //9.8065m/s^2
#define MPU_ACC_2mg                ((float)0.00006103f)  // 0.00006250 g/LSB
#define MPU_ACC_4mg                ((float)0.00012207f)  // 0.00012500 g/LSB
#define MPU_ACC_8mg                ((float)0.00024414f)  // 0.00025000 g/LSB
	
#define MPU_ACC_mps2				G*MPU_ACC_8mg

#define MPU_GYRO_s250dps            ((float)0.0076335f)  // 0.0087500 dps/LSB
#define MPU_GYRO_s500dps            ((float)0.0152671f)  // 0.0175000 dps/LSB
#define MPU_GYRO_s2000dps           ((float)0.0609756f)  // 0.0700000 dps/LSB


/***************************类型定义***********************************************/
typedef struct {
	s8 dx;
	s8 dy;
	u8 quality;
	bool motion;
}OPTFLW;
/****************************变量定义***********************************************/
using math::Matrix;
using math::Vector;
using math::Vector3;
/*
% 加速度校准：========================================
% 参考陈湾湾《MEMS 微型惯性测量组合的标定》六位置最小二乘法拟合
%Am=K*A + Acc_Offs      Am为加计输出，K为为标度因数和安装误差、交叉耦合系数矩阵  Acc_Offs为零偏
%    A =[g   -g    0    0   0   0;
%        0    0    g   -g   0   0;
%        0    0    0    0   g  -g;];六位置对应理想输出，
%最小二乘公式：K = (U-Acc_Offs)*A'/(A*A') U为6组Am
%已知   g=9.8065;
%预先求出mult_par = A'/(A·A') 即 A'*inv(A*A')
%K = (U-Acc_Offs) * mult_par
%对加计的补偿：A = inv(K)*(Am-Acc_Offs);
%所以补偿系数：标度因数和安装误差、交叉耦合系数补偿：SINS = inv(K);  零偏：acc_OFFS

*/
const float Acc_OFFS[3]={0,0,0};
const float Acc_SINS[9]={1,0,0,0,1,0,0,0,1};

const float Gyro_OFFS[3]={0,0,0};		//温度稳定时的典型值
const float Gyro_tmp_k[3]={1,1,1};		//假设零偏受温度的影响是线性变化的，设offs=kt+b
const float Gyro_tmp_b[3]={1,1,1};		//

const float Mag_OFFS[3]={0,0,0};
const float Mag_SINS[9]={1,0,0,0,1,0,0,0,1};

/****************************宏定义***********************************************/


class Sensor
{
	public:
		Sensor():sens_sta(0u),imu_temp(0u),press(0.0f),alt_abs(0.0f),alt_rela(0u)
		{
			for(int i=0;i<3;i++){
				acc_raw[i] = 0.0f;
				gyro_raw[i] = 0.0f;
				mag_raw[i] = 0.0f;
			}
		}
		~Sensor(){}
		
		bool Update(void);
		void MPU_AccGyro_Calib(bool tempin);
	void MPU_AccTempGyro_Read(void);
		Vector3 Get_RawAcc(void);
		Vector3 Get_Acc(void);

		Vector3 Get_RawGyro(void);
		Vector3 Get_Gyro(void);
	
		float Get_IMUTemp(void);
	
		
		void MPU_Mag_Calib(void);
	
		
		float Get_AbsAlt(void);
	
		
		u16 Get_RelaAlt_mm(void);
	
		
		OPTFLW Get_Optflw_Raw(void);
		u8 Get_PicQuality(void);
		s8	 Get_RawDx(void);
		s8  Get_RawDy(void);
		float Get_Dx(void);
		float Get_Dy(void);
		
	private:
		 
		 void MPU_Mag_Read(void);
		 void MS5611_Press_Read(void);
		 void SR04_Alt_Read(void);
		 void ADNS_Read(void);
		 u8 sens_sta;
		 s16 acc_raw[3];
		 s16 gyro_raw[3];
		 s16 mag_raw[3];
		 s16 imu_temp;
		 float press;
		 float alt_abs;
		 u16 alt_rela;
		 Vector3 acc;
		 Vector3 gyro;
		 Vector3 mag;
		 OPTFLW optflw;
		
		
};



extern Sensor sensor;

#endif



/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

