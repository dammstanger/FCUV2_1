/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��Sensor.cpp
 * ��	��	����������
 *                    
 * ʵ��ƽ̨	��
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��
 * ����ʱ��	��2016.9.28
 * ���༭	��2016.9.28
  **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

/****************************����ͷ�ļ�*******************************************/
#include "Sensor.h"
/****************************�궨��***********************************************/

/****************************��������*********************************************/

/****************************��������*********************************************/

/****************************�������*********************************************/
Sensor sensor;

/****************************��������*********************************************/

//=======��ȡMPU����������======================
void Sensor::MPU_AccTempGyro_Read(void)
{
	u32 tmp[7];
	fsmc.ReadBuf32(ACC_X,tmp,7);
	acc_raw[0]=(s16)tmp[0];
	acc_raw[1]=(s16)tmp[1];
	acc_raw[2]=(s16)tmp[2];
	imu_temp=(s16)tmp[3];
	gyro_raw[0]=(s16)tmp[4];
	gyro_raw[1]=(s16)tmp[5];
	gyro_raw[2]=(s16)tmp[6];
	
}

//=======��ȡMPU����������======================
void Sensor::MPU_AccGyro_Calib(bool tempin)
{
	Vector3 acc_r;				//ԭʼ���ٶ�ʸ��
	acc_r[0]=(float)acc_raw[0];
	acc_r[1]=(float)acc_raw[1];
	acc_r[2]=(float)acc_raw[2];
	
	Vector3 acc_offs(Acc_OFFS);					//
	Matrix<3,3> M_acc_sins(Acc_SINS);			//У���ۺ�ϵ����
	
	Vector3 acc_t = acc_r*MPU_ACC_mps2-acc_offs;//ת����λ�󣬵�λ��m/s^2 
	
	acc = M_acc_sins*acc_t;						//У������ٶ�ʸ������λm/s^2
	
	//
	Vector3 g_raw;
	g_raw[0]=(float)gyro_raw[0];
	g_raw[1]=(float)gyro_raw[1];
	g_raw[2]=(float)gyro_raw[2];

	Vector3 g_offs(Gyro_tmp_k);
	if(tempin==true)
	{
		g_offs.set(Gyro_tmp_k);					//�Ƿ����
		g_offs = g_offs*imu_temp+Gyro_tmp_b;
		
		gyro = g_raw - g_offs;					//������ƫ
		
	}
	else{										//�������¶�
		g_offs.set(Gyro_OFFS);					
		gyro = g_raw - g_offs;					
	}
	
}

//��ȡ�¶�
//Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 35
float Sensor::Get_IMUTemp(void)
{
	
	return imu_temp/340.0f+35;
}

//���ظ����ͼӼ�ԭʼֵ
Vector3 Sensor::Get_RawAcc(void)
{
	
	Vector3 res;
	res[0]=(float)acc_raw[0];
	res[1]=(float)acc_raw[1];
	res[2]=(float)acc_raw[2];
	return res; 
}

//���ؼ�ֵ
Vector3 Sensor::Get_Acc(void)
{
	return acc; 
}

//���ظ����͵�������ԭʼֵ
Vector3 Sensor::Get_RawGyro(void)
{
	Vector3 res;
	res[0]=(float)gyro_raw[0];
	res[1]=(float)gyro_raw[1];
	res[2]=(float)gyro_raw[2];
	return res; 
	
}

//���ؽ��ٶ�ֵ
Vector3 Sensor::Get_Gyro(void)
{
	return gyro;
}

void Sensor::MPU_Mag_Read(void)
{
	u32 tmp[3];
	fsmc.ReadBuf32(MAG_X,tmp,3);
	mag_raw[0]=(s16)tmp[0];
	mag_raw[1]=(s16)tmp[1];
	mag_raw[2]=(s16)tmp[2];
}
	
/*�ش�ʸ��У׼ % ���򷽳̿�дΪ��((X-X0)'*R')*(R *(X-X0)) = 1
% ��������Ϊ��X_sphere = R *(X-X0);
% ��׼Բ���Ϊ��X = inv(R)*X_sphere + X0
%   Ae = [a d e; d b f; e f c] Ϊ�������״����
%   X0 Ϊ��������ĵ����꣺
%   X0 = -Ae^-1/[p q r]'
*/
void Sensor::MPU_Mag_Calib(void)
{
	
	Vector3 mag_r;				//ԭʼ�ش�ʸ��
	mag_r[0]=(float)mag_r[0];
	mag_r[1]=(float)mag_r[1];
	mag_r[2]=(float)mag_r[2];
	Vector3 mag_offs(Mag_OFFS);					//
	Matrix<3,3> M_acc_sins(Mag_SINS);			//У���ۺ�ϵ����
	
	Vector3 acc_t = M_acc_sins*mag_r;// + mag_offs;//У׼����λԲ
	
	acc = acc_t.normalized();					//��һ��
}

void Sensor::MS5611_Press_Read(void)
{
	
	u32 tmp = fsmc.Read32b(ALT_PRESS);
	press = tmp/100.0f;
	
}

float Sensor::Get_AbsAlt(void)
{
	return press;				//ԭʼ��press�Ŵ���100��;
}

void Sensor::SR04_Alt_Read(void)
{
	alt_rela = fsmc.Read16b(ALT_ULTRA);
}

u16 Sensor::Get_RelaAlt_mm(void)
{
	return alt_rela;
}

void Sensor::ADNS_Read(void)
{
	u16 tmp[4];
	fsmc.ReadBuf16(OPFL_MOTION,tmp,4);
	optflw.motion = (bool)tmp[0]&0x80;			//��һλ�д���֤
	optflw.quality = (u8)tmp[1];
	optflw.dx = (s8)tmp[2];
	optflw.dy = (s8)tmp[3];
}

//
//	void Sensor::Optflw_distcal(void)
//	{
//		
//	}

OPTFLW Sensor::Get_Optflw_Raw(void)
{
	return optflw;
}

u8 Sensor::Get_PicQuality(void)
{
	return optflw.quality;
}

s8 Sensor::Get_RawDx(void)
{
	return optflw.dx;
}	

s8 Sensor::Get_RawDy(void)
{
	return optflw.dy;
}


bool Sensor::Update(void)
{
	sens_sta = fsmc.Read16b(REG_STA);
	
	if(sens_sta&MIU_RDY)
	{
		MPU_AccTempGyro_Read();
	}
	if(sens_sta&MAG_RDY)
	{
		MPU_Mag_Read();
	}
	if(sens_sta&OPTF_RDY)
	{
		ADNS_Read();
	}
	if(sens_sta&ULTRS_RDY)
	{
		SR04_Alt_Read();
	}
	if(sens_sta&PRESS_RDY)
	{
		MS5611_Press_Read();
	}
	if(sens_sta>0)
		return true;
	else
		return false;
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/
