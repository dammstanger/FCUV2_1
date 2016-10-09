/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Math_base.h
 * 描	述	：数学基础函数头文件
 *                    
 * 实验平台	：
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：
 * 创建时间	：2016.9.26
 * 最后编辑	：2016.9.26
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

#ifndef __MATH_BASE_H_
#define __MATH_BASE_H_	

/****************************包含头文件*******************************************/
#include "stm32f4xx.h"
#include "math.h"
#include "Math_def.h"
/****************************宏定义***********************************************/

/****************************类型定义*********************************************/

/****************************类定义*********************************************/

/****************************变量声明*********************************************/

/****************************变量定义*********************************************/
namespace math{

float safe_asin(float v);

//浮点数限幅
float constrain_float(float amt, float low, float high);

//16位整型数限幅
int16_t constrain_int16(int16_t amt, int16_t low, int16_t high);

//16位无符号整型数限幅
uint16_t constrain_uint16(uint16_t amt, uint16_t low, uint16_t high);

//32位整型数限幅
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high);

//角度转弧度
float radians(float deg);

//弧度转角度
float degrees(float rad);

//求平方
float sq(float v);

//2维向量长度
float pythagorous2(float a, float b);

//3维向量长度
float pythagorous3(float a, float b, float c); 

//4维向量长度
float pythagorous4(float a, float b, float c, float d);


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))

}

#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

