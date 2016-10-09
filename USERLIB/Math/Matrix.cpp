/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Matrix.h
 * 描	述	：矩阵运算头文件
 *                    
 * 实验平台	：
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：
 * 创建时间	：2016.9.21
 * 最后编辑	：2016.9.21
  **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

/****************************包含头文件*******************************************/
#include "Matrix.h"
#include "Vector.h"
/****************************宏定义***********************************************/

/****************************变量声明*********************************************/

/****************************变量定义*********************************************/

/****************************类对象定义*********************************************/

namespace math
{
	//从欧拉角转到旋转矩阵
	void Matrix<3,3>::from_euler(float roll, float pitch, float yaw) {
		float cp = cosf(pitch);
		float sp = sinf(pitch);
		float sr = sinf(roll);
		float cr = cosf(roll);
		float sy = sinf(yaw);
		float cy = cosf(yaw);

		data[0][0] = cp * cy;
		data[0][1] = (sr * sp * cy) - (cr * sy);
		data[0][2] = (cr * sp * cy) + (sr * sy);
		data[1][0] = cp * sy;
		data[1][1] = (sr * sp * sy) + (cr * cy);
		data[1][2] = (cr * sp * sy) - (sr * cy);
		data[2][0] = -sp;
		data[2][1] = sr * cp;
		data[2][2] = cr * cp;
	}
	
	//从旋转矩阵到欧拉角
	Vector<3> Matrix<3,3>::to_euler(void) const {
		Vector<3> euler;
		euler.data[1] = asinf(-data[2][0]);

		if (fabsf(euler.data[1] - M_PI_2_F) < 1.0e-3f) {
			euler.data[0] = 0.0f;
			euler.data[2] = atan2f(data[1][2] - data[0][1], data[0][2] + data[1][1]) + euler.data[0];

		} else if (fabsf(euler.data[1] + M_PI_2_F) < 1.0e-3f) {
			euler.data[0] = 0.0f;
			euler.data[2] = atan2f(data[1][2] - data[0][1], data[0][2] + data[1][1]) - euler.data[0];

		} else {
			euler.data[0] = atan2f(data[2][1], data[2][2]);
			euler.data[2] = atan2f(data[1][0], data[0][0]);
		}

		return euler;
	}
}



/****************************函数声明*********************************************/

 

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

