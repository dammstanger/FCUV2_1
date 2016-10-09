/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Quaternion.h
 * 描	述	：四元数类
 *                    
 * 实验平台	：FCUV2
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：V1.0.0
 * 创建时间	：2016.9.26
 * 最后编辑	：2016.9.26
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

#ifndef __QUATERNION_H_
#define __QUATERNION_H_

/****************************包含头文件*******************************************/
#include <math.h>
#include "Vector.h"
#include "Matrix.h"
#include "Math_base.h"
/****************************宏定义***********************************************/

/****************************类型定义*********************************************/

/****************************类定义*********************************************/


/****************************变量定义*********************************************/

namespace math
{
class __EXPORT Quaternion : public Vector<4>
{
public:
	/**
	 * trivial ctor
	 */
	Quaternion() : Vector<4>() {}

	/**
	 * copy ctor
	 */
	Quaternion(const Quaternion &q) : Vector<4>(q) {}

	/**
	 * casting from vector
	 */
	Quaternion(const Vector<4> &v) : Vector<4>(v) {}

	/**
	 * setting ctor
	 */
	Quaternion(const float d[4]) : Vector<4>(d) {}

	/**
	 * setting ctor
	 */
//	Quaternion(const float a0, const float b0, const float c0, const float d0): data[0](a0),data[1](b0),data[2](c0),data[3](d0){}

	using Vector<4>::operator *;

	/**
	 * multiplication
	 */
	const Quaternion operator *(const Quaternion &q) const;

	/**
	 * division除法
	 */
	Quaternion operator /(const Quaternion &q) const;

//	/**
//	 * derivative求导
//	 */
//	const Quaternion derivative(const Vector3 &w);



/**
 * derivative求导
 */
const Quaternion derivative(const Vector3 &w) {
	float dataQ[] = {
		data[0], -data[1], -data[2], -data[3],
		data[1],  data[0], -data[3],  data[2],
		data[2],  data[3],  data[0], -data[1],
		data[3], -data[2],  data[1],  data[0]
	};
	Matrix<4, 4> Q(dataQ);
	float tmp[] = {0.0f, w.data[0], w.data[1], w.data[2]};
	Vector<4> v(tmp);
	return Q * v * 0.5f;
}


	/**
	 * conjugate	共轭
	 */
	Quaternion conjugated() const {
		float tmp[]={data[0], -data[1], -data[2], -data[3]};
		Quaternion Q(tmp);
		return Q;

	}

	/**
	 * inversed 求逆
	 */
	Quaternion inversed() const {
		float norm = length_squared();
		float tmp[]={data[0] / norm, -data[1] / norm, -data[2] / norm, -data[3] / norm};
		Quaternion Q(tmp);
		return Q;
	}

//	/**
//	 * conjugation 四元数构成的矩阵*矢量
//	 */
//	Vector3 conjugate(const Vector3 &v) const;

//	/**
//	 * conjugation with inversed quaternion	四元数旋转逆矩阵*矢量
//	 */
//	Vector3 conjugate_inversed(const Vector3 &v) const;

	

	/**
	 * conjugation 四元数构成的矩阵*矢量
	 */
	Vector3 conjugate(const Vector3 &v) const;


	/**
	 * conjugation with inversed quaternion 四元数旋转逆矩阵*矢量
	 */
	Vector3 conjugate_inversed(const Vector3 &v) const;


	
	/**
	 * imaginary part of quaternion 四元数的虚数部分
	 */
	Vector3 imag(void) {
		return Vector3(&data[1]);		
	}

	/**
	 * simplified version of the above method to create quaternion representing rotation only by yaw	只带航向角的四元数
	 */
	void from_yaw(float yaw) {
		data[0] = cosf(yaw / 2.0f);
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = sinf(yaw / 2.0f);
	}


	/**
	 * set quaternion to rotation defined by euler angles 由欧拉角得到四元数
	 */
	void from_euler(float roll, float pitch, float yaw);


		/**
		 * create Euler angles vector from the quaternion 由四元数得到欧拉角
		 */
	Vector3 to_euler() const;

	/**
	 * set quaternion to rotation by DCM
	 * Reference: Shoemake, Quaternions, http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
	 */
	void from_dcm(const Matrix3 &dcm);

	/**
	 * create rotation matrix for the quaternion
	 */
	Matrix3 to_dcm(void) const;
	
	
	// 取出行向量
	Vector3 row_vector(unsigned int n);
	// 取出列向量
	Vector3 col_vector(unsigned int n);	
	//更新四元数,一阶龙格库塔法
	void update_Runge_Kutta_1st(Vector3 &w, float deltaT);

};


/****************************变量声明*********************************************/
//extern Quaternion Qunion;
}

#endif // QUATERNION_HPP

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

