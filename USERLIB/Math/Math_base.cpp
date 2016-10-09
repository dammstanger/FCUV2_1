/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��Math_base.cpp
 * ��	��	����ѧ��������
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

/****************************����ͷ�ļ�*******************************************/
#include "Math_base.h"
/****************************�궨��***********************************************/

/****************************��������*********************************************/

/****************************��������*********************************************/

/****************************�������*********************************************/

namespace math
{

//��֤����ֵ����Ч��
float safe_asin(float v)
{
    if (isnan(v)) {
        return 0.0;
    }
    if (v >= 1.0f) {
        return M_PI/2;
    }
    if (v <= -1.0f) {
        return -M_PI/2;
    }
    return asinf(v);
}

//�������޷�
float constrain_float(float amt, float low, float high) 
{
	if (isnan(amt)) {
		return (low+high)*0.5f;
	}
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//16λ�������޷�
int16_t constrain_int16(int16_t amt, int16_t low, int16_t high) {
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//16λ�޷����������޷�
uint16_t constrain_uint16(uint16_t amt, uint16_t low, uint16_t high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//32λ�������޷�
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high) {
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//�Ƕ�ת����
float radians(float deg) {
	return deg * M_DEG_TO_RAD_F;
}

//����ת�Ƕ�
float degrees(float rad) {
	return rad * M_RAD_TO_DEG_F;
}

//��ƽ��
float sq(float v) {
	return v*v;
}

//2ά��������
float pythagorous2(float a, float b) {
	return sqrtf(sq(a)+sq(b));
}

//3ά��������
float pythagorous3(float a, float b, float c) {
	return sqrtf(sq(a)+sq(b)+sq(c));
}

//4ά��������
float pythagorous4(float a, float b, float c, float d) {
	return sqrtf(sq(a)+sq(b)+sq(c)+sq(d));
}

}



/****************************��������*********************************************/

 

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

