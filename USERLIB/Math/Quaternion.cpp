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

/****************************包含头文件*******************************************/
#include "Quaternion.h"
/****************************宏定义***********************************************/

/****************************变量声明*********************************************/

/****************************变量定义*********************************************/


namespace math{

/****************************类对象定义*********************************************/
	
//Quaternion Qunion;
	
/****************************函数声明*********************************************/
/**
 * multiplication
 */
 const Quaternion Quaternion::operator *(const Quaternion &q) const {
	float tmp[]={ data[0] * q.data[0] - data[1] * q.data[1] - data[2] * q.data[2] - data[3] * q.data[3],
				   data[0] * q.data[1] + data[1] * q.data[0] + data[2] * q.data[3] - data[3] * q.data[2],
				   data[0] * q.data[2] - data[1] * q.data[3] + data[2] * q.data[0] + data[3] * q.data[1],
				   data[0] * q.data[3] + data[1] * q.data[2] - data[2] * q.data[1] + data[3] * q.data[0]};
	Quaternion Q(tmp);
	return Q;
}
 

/**
 * division除法
 */
Quaternion Quaternion::operator /(const Quaternion &q) const {
	float norm = q.length_squared();
	float tmp[] ={(  data[0] * q.data[0] + data[1] * q.data[1] + data[2] * q.data[2] + data[3] * q.data[3]) / norm,
				(- data[0] * q.data[1] + data[1] * q.data[0] - data[2] * q.data[3] + data[3] * q.data[2]) / norm,
				(- data[0] * q.data[2] + data[1] * q.data[3] + data[2] * q.data[0] - data[3] * q.data[1]) / norm,
				(- data[0] * q.data[3] - data[1] * q.data[2] + data[2] * q.data[1] + data[3] * q.data[0]) / norm
				};
	Quaternion Q(tmp);
	return Q;
}



///**
// * derivative求导
// */
//const Quaternion Quaternion::derivative(const Vector3 &w) {
//	float dataQ[] = {
//		data[0], -data[1], -data[2], -data[3],
//		data[1],  data[0], -data[3],  data[2],
//		data[2],  data[3],  data[0], -data[1],
//		data[3], -data[2],  data[1],  data[0]
//	};
//	Matrix<4, 4> Q(dataQ);
//	float tmp[] = {0.0f, w.data[0], w.data[1], w.data[2]};
//	Vector<4> v(tmp);
//	return Q * v * 0.5f;
//}



/**
 * conjugation 四元数构成的矩阵*矢量
 */
Vector3 Quaternion::conjugate(const Vector3 &v) const {
	float q0q0 = data[0] * data[0];
	float q1q1 = data[1] * data[1];
	float q2q2 = data[2] * data[2];
	float q3q3 = data[3] * data[3];
	float tmp[]={	v.data[0] * (q0q0 + q1q1 - q2q2 - q3q3) +
					v.data[1] * 2.0f * (data[1] * data[2] - data[0] * data[3]) +
					v.data[2] * 2.0f * (data[0] * data[2] + data[1] * data[3]),

					v.data[0] * 2.0f * (data[1] * data[2] + data[0] * data[3]) +
					v.data[1] * (q0q0 - q1q1 + q2q2 - q3q3) +
					v.data[2] * 2.0f * (data[2] * data[3] - data[0] * data[1]),

					v.data[0] * 2.0f * (data[1] * data[3] - data[0] * data[2]) +
					v.data[1] * 2.0f * (data[0] * data[1] + data[2] * data[3]) +
					v.data[2] * (q0q0 - q1q1 - q2q2 + q3q3)};
	Vector3 MQ_v(tmp);
	return MQ_v;
}



/**
 * conjugation with inversed quaternion 四元数旋转逆矩阵*矢量
 */
Vector3 Quaternion::conjugate_inversed(const Vector3 &v) const {
	float q0q0 = data[0] * data[0];
	float q1q1 = data[1] * data[1];
	float q2q2 = data[2] * data[2];
	float q3q3 = data[3] * data[3];
	float tmp[]={
		v.data[0] * (q0q0 + q1q1 - q2q2 - q3q3) +
		v.data[1] * 2.0f * (data[1] * data[2] + data[0] * data[3]) +
		v.data[2] * 2.0f * (data[1] * data[3] - data[0] * data[2]),

		v.data[0] * 2.0f * (data[1] * data[2] - data[0] * data[3]) +
		v.data[1] * (q0q0 - q1q1 + q2q2 - q3q3) +
		v.data[2] * 2.0f * (data[2] * data[3] + data[0] * data[1]),

		v.data[0] * 2.0f * (data[1] * data[3] + data[0] * data[2]) +
		v.data[1] * 2.0f * (data[2] * data[3] - data[0] * data[1]) +
		v.data[2] * (q0q0 - q1q1 - q2q2 + q3q3)};
	Vector3 MQinv_v(tmp);
	return MQinv_v;
}



/**
 * set quaternion to rotation defined by euler angles 由欧拉角得到四元数
 */
void Quaternion::from_euler(float roll, float pitch, float yaw) {
	double cosPhi_2 = cos(double(roll) / 2.0);
	double sinPhi_2 = sin(double(roll) / 2.0);
	double cosTheta_2 = cos(double(pitch) / 2.0);
	double sinTheta_2 = sin(double(pitch) / 2.0);
	double cosPsi_2 = cos(double(yaw) / 2.0);
	double sinPsi_2 = sin(double(yaw) / 2.0);

	/* operations executed in double to avoid loss of precision through
	 * consecutive multiplications. Result stored as float.
	 */
	data[0] = static_cast<float>(cosPhi_2 * cosTheta_2 * cosPsi_2 + sinPhi_2 * sinTheta_2 * sinPsi_2);//强制类型转换
	data[1] = static_cast<float>(sinPhi_2 * cosTheta_2 * cosPsi_2 - cosPhi_2 * sinTheta_2 * sinPsi_2);
	data[2] = static_cast<float>(cosPhi_2 * sinTheta_2 * cosPsi_2 + sinPhi_2 * cosTheta_2 * sinPsi_2);
	data[3] = static_cast<float>(cosPhi_2 * cosTheta_2 * sinPsi_2 - sinPhi_2 * sinTheta_2 * cosPsi_2);
}


	/**
	 * create Euler angles vector from the quaternion 由四元数得到欧拉角
	 */
Vector3 Quaternion::to_euler() const {
		float tmp[]={
			atan2f(2.0f * (data[0] * data[1] + data[2] * data[3]), 1.0f - 2.0f * (data[1] * data[1] + data[2] * data[2])),
			safe_asin(2.0f * (data[0] * data[2] - data[3] * data[1])),
			atan2f(2.0f * (data[0] * data[3] + data[1] * data[2]), 1.0f - 2.0f * (data[2] * data[2] + data[3] * data[3]))
			};
		Vector3 v(tmp);
		return v;
	}


/**
 * set quaternion to rotation by DCM
	
 * Reference: Shoemake, Quaternions, http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
 */
void Quaternion::from_dcm(const Matrix3 &dcm) {
	float tr = dcm.data[0][0] + dcm.data[1][1] + dcm.data[2][2];
	if (tr > 0.0f) {
		float s = sqrtf(tr + 1.0f);
		data[0] = s * 0.5f;
		s = 0.5f / s;
		data[1] = (dcm.data[2][1] - dcm.data[1][2]) * s;
		data[2] = (dcm.data[0][2] - dcm.data[2][0]) * s;
		data[3] = (dcm.data[1][0] - dcm.data[0][1]) * s;
	} else {
		/* Find maximum diagonal element in dcm
		* store index in dcm_i */
		int dcm_i = 0;
		for (int i = 1; i < 3; i++) {
			if (dcm.data[i][i] > dcm.data[dcm_i][dcm_i]) {
				dcm_i = i;
			}
		}
		int dcm_j = (dcm_i + 1) % 3;
		int dcm_k = (dcm_i + 2) % 3;
		float s = sqrtf((dcm.data[dcm_i][dcm_i] - dcm.data[dcm_j][dcm_j] -
		dcm.data[dcm_k][dcm_k]) + 1.0f);
		data[dcm_i + 1] = s * 0.5f;
		s = 0.5f / s;
		data[dcm_j + 1] = (dcm.data[dcm_i][dcm_j] + dcm.data[dcm_j][dcm_i]) * s;
		data[dcm_k + 1] = (dcm.data[dcm_k][dcm_i] + dcm.data[dcm_i][dcm_k]) * s;
		data[0] = (dcm.data[dcm_k][dcm_j] - dcm.data[dcm_j][dcm_k]) * s;
	}
}

/**
 * create rotation matrix for the quaternion
 */
Matrix3 Quaternion::to_dcm(void) const {
	Matrix3 R;
	float aSq = data[0] * data[0];
	float bSq = data[1] * data[1];
	float cSq = data[2] * data[2];
	float dSq = data[3] * data[3];
	R.data[0][0] = aSq + bSq - cSq - dSq;
	R.data[0][1] = 2.0f * (data[1] * data[2] - data[0] * data[3]);
	R.data[0][2] = 2.0f * (data[0] * data[2] + data[1] * data[3]);
	R.data[1][0] = 2.0f * (data[1] * data[2] + data[0] * data[3]);
	R.data[1][1] = aSq - bSq + cSq - dSq;
	R.data[1][2] = 2.0f * (data[2] * data[3] - data[0] * data[1]);
	R.data[2][0] = 2.0f * (data[1] * data[3] - data[0] * data[2]);
	R.data[2][1] = 2.0f * (data[0] * data[1] + data[2] * data[3]);
	R.data[2][2] = aSq - bSq - cSq + dSq;
	return R;
}

	

// 取出CbtR行向量
//  n=0~2,,     若求该四元数的等效旋转矩阵CbtR中的重力分量,n=2
Vector3 Quaternion::row_vector(unsigned int n)
{
	Vector3 v;
	switch(n){
		case 0u:{						
		v.data[0] = 1-2*(data[2]*data[2] + data[3]*data[3]);
		v.data[1] = 2*(data[1]*data[2] - data[0]*data[3]);						  
		v.data[2] = 2*(data[1]*data[3] + data[0]*data[2]);				
		}break;
		case 1u:{						
		v.data[0] = 2*(data[1]*data[2] + data[0]*data[3]);								
		v.data[1] = 1-2*(data[1]*data[1] + data[3]*data[3]);
		v.data[2] = 2*(data[2]*data[3] - data[0]*data[1]);	
		}break;
		case 2u:{						
		v.data[0] = 2*(data[1]*data[3] - data[0]*data[2]);								
		v.data[1] = 2*(data[0]*data[1] + data[2]*data[3]);						  
		v.data[2] = 1-2*(data[1]*data[1] + data[2]*data[2]);
		}break;
		default :{			
		v.data[0] = 0;
		v.data[1] = 0;
		v.data[2] = 0;
		}break;
	}
	return v;
}

// 取出CbtR列向量
Vector3 Quaternion::col_vector(unsigned int n)
{
	Vector3 v;
	switch(n){
		case 0u:{						
		v.data[0] = 1-2*(data[2]*data[2] + data[3]*data[3]);
		v.data[1] = 2*(data[1]*data[2] + data[0]*data[3]);						  
		v.data[2] = 2*(data[1]*data[3] - data[0]*data[2]);				
		}break;
		case 1u:{						
		v.data[0] = 2*(data[1]*data[2] - data[0]*data[3]);								
		v.data[1] = 1-2*(data[1]*data[1] + data[3]*data[3]);
		v.data[2] = 2*(data[2]*data[3] + data[0]*data[1]);	
		}break;
		case 2u:{						
		v.data[0] = 2*(data[1]*data[3] + data[0]*data[2]);								
		v.data[1] = 2*(data[2]*data[3] - data[0]*data[1]);						  
		v.data[2] = 1-2*(data[1]*data[1] + data[2]*data[2]);
		}break;
		default :{			
		v.data[0] = 0;
		v.data[1] = 0;
		v.data[2] = 0;
		}break;
	}
	return v;
}

//
//一阶龙格库塔法更新四元数
void Quaternion::update_Runge_Kutta_1st(Vector3 &w, float deltaT)
{
  data[0] += 0.5f * (-data[1]*w.data[0] - data[2]*w.data[1] - data[3]*w.data[2])* deltaT;
  data[1] += 0.5f * (data[0]*w.data[0] + data[2]*w.data[2] - data[3]*w.data[1])* deltaT;
  data[2] += 0.5f * (data[0]*w.data[1] - data[1]*w.data[2] + data[3]*w.data[0])* deltaT;
  data[3] += 0.5f * (data[0]*w.data[2] + data[1]*w.data[1] - data[2]*w.data[0])* deltaT;	
}

}	//end namespace math


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

