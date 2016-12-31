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
 * ���༭	��2016.10.9
  **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

/****************************����ͷ�ļ�*******************************************/
#include "Sensor.h"
/****************************�궨��***********************************************/

/****************************��������*********************************************/

/****************************��������*********************************************/
u8 g_STA=0;
/****************************�������*********************************************/
Sensor sensor;
//���ٶ�У׼ϵ��
const Vector3 acc_offs(Acc_OFFS);					//
const Matrix3 M_acc_sins(Acc_SINS);				//У���ۺ�ϵ����
//������У׼ϵ��
Vector3 g_offs(Gyro_tmp_k);
//���贫����У׼ϵ��
Vector3 mag_offs(Mag_OFFS);					//
Matrix3 M_mag_sins(Mag_SINS);			//У���ۺ�ϵ����

/****************************��������*********************************************/

u8 Sensor::Get_status(void)
{
	return sens_sta;
}

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
	
	fsmc.ReadBuf32(MPU_TIMESP_L,tmp,2);
	mpu_timesp = ((long long)tmp[1]<<32)+tmp[0];
}

//=======��ȡMPU����������======================
void Sensor::MPU_AccGyro_Calib(bool tempin)
{
	Vector3 acc_r;				//ԭʼ���ٶ�ʸ��
	acc_r[0]=(float)acc_raw[0];
	acc_r[1]=(float)acc_raw[1];
	acc_r[2]=(float)acc_raw[2];
	
	Vector3 acc_t = acc_r-acc_offs;//ת����λ�󣬵�λ��m/s^2 
	acc_t *=MPU_ACC_mps2;
	acc = M_acc_sins*acc_t;			//У������ٶ�ʸ������λm/s^2
	
	//������У׼
	Vector3 g_raw;
	g_raw[0]=(float)gyro_raw[0];
	g_raw[1]=(float)gyro_raw[1];
	g_raw[2]=(float)gyro_raw[2];

	
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
	gyro *=MPU_GYRO_dps;
	
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
	
	fsmc.ReadBuf32(MPU_TIMESP_L,tmp,2);
	mag_timesp = mpu_timesp;
}

Vector3 Sensor::Get_RawMag(void)
{
	Vector3 res;
	res[0]=(float)mag_raw[0];
	res[1]=(float)mag_raw[1];
	res[2]=(float)mag_raw[2];
	return res; 
	
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

	
	Vector3 mag_t = M_acc_sins*mag_r + mag_offs;//У׼����λԲ
	
	mag = mag_t;//.normalized();					//��һ��
}

Vector3 Sensor::Get_MagVct(void)
{
	return mag;
}


void Sensor::MS5611_Press_Read(void)
{
	u32 tmp[2];
	press = fsmc.Read32b(ALT_PRESS);	
	
	fsmc.ReadBuf32(ARP_TIMESP_L,tmp,2);
	press_timesp = ((long long)tmp[1]<<32)+tmp[0];
	
}

float Sensor::Get_AbsAlt(void)
{
	return press;				//ԭʼ��press�Ŵ���100��;
}

void Sensor::SR04_Alt_Read(void)
{
	u32 tmp[2];
	alt_rela = fsmc.Read16b(ALT_ULTRA);
	
	fsmc.ReadBuf32(ULT_TIMESP_L,tmp,2);
	ultrs_timesp = ((long long)tmp[1]<<32)+tmp[0];
}

u16 Sensor::Get_RelaAlt_mm(void)
{
	return alt_rela;
}

void Sensor::ADNS_Read(void)
{
	u16 tmp[4];
	fsmc.ReadBuf16(OPFL_MOTION,tmp,4);
	optflw.motion = (bool)(tmp[0]&0x80);			//��һλ�д���֤
	optflw.quality = (u8)tmp[1];
	optflw.dx = (s8)tmp[2];
	optflw.dy = (s8)tmp[3];
	
	u32 tmp2[2];
	fsmc.ReadBuf32(ADNS_TIMESP_L,tmp2,2);
	adns_timesp = ((long long)tmp2[1]<<32)+tmp2[0];
	
}

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

//
u32 Sensor::Get_IMU_Timp_ms(void)
{
	return (u32)((mpu_timesp+500)/1000);	//С�����1λ��������
}

long long Sensor::Get_IMU_Timp_us(void)
{
	return mpu_timesp;	//С�����1λ��������
}

//
u32 Sensor::Get_MAG_Timp_ms(void)
{
	return (u32)((mag_timesp+500)/1000);	//С�����1λ��������
}

long long Sensor::Get_MAG_Timp_us(void)
{
	return mag_timesp;	//С�����1λ��������
}


//
u32 Sensor::Get_ADNS_Timp_ms(void)
{
	return (u32)((adns_timesp+500)/1000);	//С�����1λ��������
}

long long Sensor::Get_ADNS_Timp_us(void)
{
	return adns_timesp;	//С�����1λ��������
}


//
u32 Sensor::Get_MS5611_Timp_ms(void)
{
	return (u32)((press_timesp+500)/1000);	//С�����1λ��������
}


long long Sensor::Get_MS5611_Timp_us(void)
{
	return press_timesp;	//С�����1λ��������
}


//
u32 Sensor::Get_SR04_Timp_ms(void)
{
	return (u32)((ultrs_timesp+500)/1000);	//С�����1λ��������
}

long long Sensor::Get_SR04_Timp_us(void)
{
	return ultrs_timesp;	//С�����1λ��������
}



u8 Sensor::Update(void)
{
	sens_sta = fsmc.Read16b(REG_STA);
	g_STA=sens_sta;
	if(sens_sta&IMU_RDY)
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
	return sens_sta;
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

