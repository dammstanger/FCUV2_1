/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��Quaternion.h
 * ��	��	����Ԫ����
 *                    
 * ʵ��ƽ̨	��FCUV2
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��V1.0.0
 * ����ʱ��	��2016.9.26
 * ���༭	��2016.9.26
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

#ifndef __QUATERNION_H_
#define __QUATERNION_H_

/****************************����ͷ�ļ�*******************************************/
#include <math.h>
#include "Vector.h"
#include "Matrix.h"
#include "Math_base.h"
/****************************�궨��***********************************************/

/****************************���Ͷ���*********************************************/

/****************************�ඨ��*********************************************/


/****************************��������*********************************************/

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
	 * division����
	 */
	Quaternion operator /(const Quaternion &q) const;

//	/**
//	 * derivative��
//	 */
//	const Quaternion derivative(const Vector3 &w);



/**
 * derivative��
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
	 * conjugate	����
	 */
	Quaternion conjugated() const {
		float tmp[]={data[0], -data[1], -data[2], -data[3]};
		Quaternion Q(tmp);
		return Q;

	}

	/**
	 * inversed ����
	 */
	Quaternion inversed() const {
		float norm = length_squared();
		float tmp[]={data[0] / norm, -data[1] / norm, -data[2] / norm, -data[3] / norm};
		Quaternion Q(tmp);
		return Q;
	}

//	/**
//	 * conjugation ��Ԫ�����ɵľ���*ʸ��
//	 */
//	Vector3 conjugate(const Vector3 &v) const;

//	/**
//	 * conjugation with inversed quaternion	��Ԫ����ת�����*ʸ��
//	 */
//	Vector3 conjugate_inversed(const Vector3 &v) const;

	

	/**
	 * conjugation ��Ԫ�����ɵľ���*ʸ��
	 */
	Vector3 conjugate(const Vector3 &v) const;


	/**
	 * conjugation with inversed quaternion ��Ԫ����ת�����*ʸ��
	 */
	Vector3 conjugate_inversed(const Vector3 &v) const;


	
	/**
	 * imaginary part of quaternion ��Ԫ������������
	 */
	Vector3 imag(void) {
		return Vector3(&data[1]);		
	}

	/**
	 * simplified version of the above method to create quaternion representing rotation only by yaw	ֻ������ǵ���Ԫ��
	 */
	void from_yaw(float yaw) {
		data[0] = cosf(yaw / 2.0f);
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = sinf(yaw / 2.0f);
	}


	/**
	 * set quaternion to rotation defined by euler angles ��ŷ���ǵõ���Ԫ��
	 */
	void from_euler(float roll, float pitch, float yaw);


		/**
		 * create Euler angles vector from the quaternion ����Ԫ���õ�ŷ����
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
	
	
	// ȡ��������
	Vector3 row_vector(unsigned int n);
	// ȡ��������
	Vector3 col_vector(unsigned int n);	
	//������Ԫ��,һ�����������
	void update_Runge_Kutta_1st(Vector3 &w, float deltaT);

};


/****************************��������*********************************************/
//extern Quaternion Qunion;
}

#endif // QUATERNION_HPP

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

