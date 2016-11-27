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
					Ultras_Rdy	Press_Rdy		OPTF_Rdy		Mag_Rdy		IMU_Rdy
状态寄存器的各个位定义*/
#define IMU_RDY					0x01
#define MAG_RDY					0x02
#define OPTF_RDY				0x04
#define PRESS_RDY				0x08
#define ULTRS_RDY				0x10

//====================读写16位的地址===================
#define REG_CMD					0u
#define REG_STA					1u				//
#define REG_PWM1				2u
#define REG_PWM2				3u
#define REG_PWM3				4u
#define REG_PWM4				5u
#define REG_PWM5				6u
#define REG_PWM6				7u
#define REG_PWM7				8u
#define REG_PWM8				9u
#define OPFL_MOTION				10u
#define OPFL_SQUARL				11u
#define OPFL_DX					12u
#define OPFL_DY					13u
#define ALT_ULTRA				14u
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

#define G							9.8065f				 //9.8065m/s^2
#define MPU_ACC_2mg                ((float)0.00006103f)  // 0.00006250 g/LSB
#define MPU_ACC_4mg                ((float)0.00012207f)  // 0.00012500 g/LSB
#define MPU_ACC_8mg                ((float)0.00024414f)  // 0.00025000 g/LSB
	

#define MPU_GYRO_s250dps            ((float)0.0076335f)  // 0.0087500 dps/LSB
#define MPU_GYRO_s500dps            ((float)0.0152671f)  // 0.0175000 dps/LSB
#define MPU_GYRO_s2000dps           ((float)0.0609756f)  // 0.0700000 dps/LSB

#define MPU_ACC_mps2				G*MPU_ACC_8mg
#define MPU_GYRO_dps				MPU_GYRO_s2000dps

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
using math::Matrix3;
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
const float Acc_OFFS[3]={-57.83f,11.95,376.23};
const float Acc_SINS[9]={0.9922f,-0.0079f,0.0013f,
						0.0028f,0.9948f,-0.01f,
						0.0066f,0.005f,0.9957f};

const float Gyro_OFFS[3]={13.662f,25.58f,-14.654f};		//温度稳定时的典型值
const float Gyro_tmp_k[3]={1.0f,1.0f,1.0f};		//假设零偏受温度的影响是线性变化的，设offs=kt+b
const float Gyro_tmp_b[3]={1.0f,1.0f,1.0f};		//

const float Mag_OFFS[3]={-41.3941f,195.8141f,24.1599f};
const float Mag_SINS[9]={183.072f,5.244f,2.24f,
							0,103.361f,0.4527,
							0,0,128.4462f};

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
		
		u8 Update(void);
		u8 Get_status(void);
		void MPU_AccGyro_Calib(bool tempin);
	
		Vector3 Get_RawAcc(void);
		Vector3 Get_Acc(void);

		Vector3 Get_RawGyro(void);
		Vector3 Get_Gyro(void);
	
		Vector3 Get_RawMag(void);
		Vector3 Get_MagVct(void);
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
		void MPU_AccTempGyro_Read(void);
		void MPU_Mag_Read(void);
		void MS5611_Press_Read(void);
	private:
		 
		 
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
		long long mpu_timesp;			//64位
		long long mag_timesp;
		long long adns_timesp;
		long long press_timesp;
		long long ultrs_timesp;
		 
		
		
};



extern Sensor sensor;

#endif



/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

