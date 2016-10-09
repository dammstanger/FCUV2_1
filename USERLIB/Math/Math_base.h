/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��Math_base.h
 * ��	��	����ѧ��������ͷ�ļ�
 *                    
 * ʵ��ƽ̨	��
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��
 * ����ʱ��	��2016.9.26
 * ���༭	��2016.9.26
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

#ifndef __MATH_BASE_H_
#define __MATH_BASE_H_	

/****************************����ͷ�ļ�*******************************************/
#include "stm32f4xx.h"
#include "math.h"
#include "Math_def.h"
/****************************�궨��***********************************************/

/****************************���Ͷ���*********************************************/

/****************************�ඨ��*********************************************/

/****************************��������*********************************************/

/****************************��������*********************************************/
namespace math{

float safe_asin(float v);

//�������޷�
float constrain_float(float amt, float low, float high);

//16λ�������޷�
int16_t constrain_int16(int16_t amt, int16_t low, int16_t high);

//16λ�޷����������޷�
uint16_t constrain_uint16(uint16_t amt, uint16_t low, uint16_t high);

//32λ�������޷�
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high);

//�Ƕ�ת����
float radians(float deg);

//����ת�Ƕ�
float degrees(float rad);

//��ƽ��
float sq(float v);

//2ά��������
float pythagorous2(float a, float b);

//3ά��������
float pythagorous3(float a, float b, float c); 

//4ά��������
float pythagorous4(float a, float b, float c, float d);


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))

}

#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

