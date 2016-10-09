/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��Vector.h
 * ��	��	����������ͷ�ļ�
 *                    
 * ʵ��ƽ̨	��
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��
 * ����ʱ��	��2016.9.21
 * ���༭	��2016.9.21
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

#ifndef __VECTOR_H_
#define __VECTOR_H_
/****************************����ͷ�ļ�*******************************************/
#include <sys_code_ctl.h>
/****************************�궨��***********************************************/

/****************************���Ͷ���*********************************************/

/****************************�ඨ��*********************************************/
namespace math
{

template <unsigned int N>
class __EXPORT Vector;


template <unsigned int N>
class __EXPORT VectorBase
{
public:
	/**
	 * vector data
	 */
	float data[N];

	/**
	 * struct for using arm_math functions, represents column vector
	 */
	arm_matrix_instance_f32 arm_col;

	/**
	 * trivial ctor
	 * initializes elements to zero
	 */
	VectorBase()
	{
		arm_col.numRows = N;
		arm_col.numCols = 1;
		arm_col.pData = &data[0];
		for(int i=0;i<N;i++)
		 arm_col.pData[i]=0.0f;
	}

	/**
	 * copy ctor
	 */
	VectorBase(const VectorBase<N> &v) 
	{
		arm_col.numRows = N;
		arm_col.numCols = 1;
		arm_col.pData = &data[0];
		for(int i=0;i<N;i++)
		 arm_col.pData[i]=v[i];
	}

	/**
	 * setting ctor
	 */
	VectorBase(const float d[N])
	{
		arm_col.numRows = N;
		arm_col.numCols = 1;
		arm_col.pData = &data[0];
		memcpy(data, d, sizeof(data));
	}	
	
	virtual ~VectorBase() {};

	/**
	 * set data
	 */
	void set(const float d[N]) {
		memcpy(data, d, sizeof(data));
	}

	/**
	 * access to elements by index
	 */
	float &operator[](const unsigned int i) {			//()������ ����һ��float & ��float�͵�����
		return data[i];
	}

	/**
	 * access to elements by index
	 */
	float operator[](const unsigned int i) const {		//
		return data[i];
	}

	/**
	 * get vector size
	 */
	unsigned int get_size() const {
		return N;
	}

	/**
	 * test for equality
	 */
	bool operator ==(const Vector<N> &v) const {
		for (unsigned int i = 0; i < N; i++)
			if (data[i] != v.data[i])
				return false;

		return true;
	}

	/**
	 * test for inequality
	 */
	bool operator !=(const Vector<N> &v) const {
		for (unsigned int i = 0; i < N; i++)
			if (data[i] != v.data[i])
				return true;

		return false;
	}

	/**
	 * set to value
	 */
	const Vector<N> &operator =(const Vector<N> &v) {
		memcpy(data, v.data, sizeof(data));
		return *static_cast<const Vector<N>*>(this);
	}

	/**
	 * negation ÿ��Ԫ��ȡ��ֵ
	 */
	const Vector<N> operator -(void) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = -data[i];

		return res;
	}

	/**
	 * addition ���
	 */
	const Vector<N> operator +(const Vector<N> &v) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = data[i] + v.data[i];

		return res;
	}

	/**
	 * subtraction
	 */
	const Vector<N> operator -(const Vector<N> &v) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = data[i] - v.data[i];

		return res;
	}

	/**
	 * uniform scaling��������
	 */
	const Vector<N> operator *(const float num) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = data[i] * num;

		return res;
	}

	/**
	 * uniform scaling
	 */
	const Vector<N> operator /(const float num) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = data[i] / num;

		return res;
	}

	/**
	 * addition
	 */
	const Vector<N> &operator +=(const Vector<N> &v) {
		for (unsigned int i = 0; i < N; i++)
			data[i] += v.data[i];

		return *static_cast<const Vector<N>*>(this);
	}

	/**
	 * subtraction
	 */
	const Vector<N> &operator -=(const Vector<N> &v) {
		for (unsigned int i = 0; i < N; i++)
			data[i] -= v.data[i];

		return *static_cast<const Vector<N>*>(this);
	}

	/**
	 * uniform scaling
	 */
	const Vector<N> &operator *=(const float num) {
		for (unsigned int i = 0; i < N; i++)
			data[i] *= num;

		return *static_cast<const Vector<N>*>(this);
	}

	/**
	 * uniform scaling
	 */
	const Vector<N> &operator /=(const float num) {
		for (unsigned int i = 0; i < N; i++)
			data[i] /= num;

		return *static_cast<const Vector<N>*>(this);
	}

	/**
	 * dot product
	 */
	float operator *(const Vector<N> &v) const {
		float res = 0.0f;

		for (unsigned int i = 0; i < N; i++)
			res += data[i] * v.data[i];

		return res;
	}

	/**
	 * cross product
	 */
//	const Vector<N> cprdc(const Vector<N> &v) const {
//		Vector<N> r1({v[0],v[1],v[2]});
//		Vector<N> r2({v[0],v[1],v[2]});
//		Vector<N> r3({v[0],v[1],v[2]});
//		return r3;
//	}
	
	/**
	 * element by element multiplication
	 */
	const Vector<N> emult(const Vector<N> &v) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = data[i] * v.data[i];

		return res;
	}

	/**
	 * element by element division
	 */
	const Vector<N> edivide(const Vector<N> &v) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = data[i] / v.data[i];

		return res;
	}

	/**
	 * gets the length of this vector squared	ģ��ƽ��
	 */
	float length_squared() const {
		float res = 0.0f;

		for (unsigned int i = 0; i < N; i++)
			res += data[i] * data[i];

		return res;
	}

	/**
	 * gets the length of this vector
	 */
	float length() const {
		float res = 0.0f;

		for (unsigned int i = 0; i < N; i++)
			res += data[i] * data[i];

		return sqrtf(res);
	}

	/**
	 * normalizes this vector
	 */
	void normalize() {
		*this /= length();			//�Ա������Աdata��ÿһ��Ԫ��/ģ
	}

	/**
	 * returns the normalized version of this vector
	 */
	Vector<N> normalized() const {		//�����const�����ú������ı����ݳ�Ա��ֵ���ɱ�֤���۸�
		return *this / length();
	}

	/**
	 * set zero vector
	 */
	void zero(void) {
		memset(data, 0, sizeof(data));
	}


};


template <unsigned int N>
class __EXPORT Vector : public VectorBase<N>			//��̳�   ������:���� public��ʾ��������
{
public:
	Vector() : VectorBase<N>() {}

	Vector(const Vector<N> &v) : VectorBase<N>(v) {}

	Vector(const float d[N]) : VectorBase<N>(d) {}

	/**
	 * set to value
	 */
	const Vector<N> &operator =(const Vector<N> &v) {
		memcpy(this->data, v.data, sizeof(this->data));
		return *this;
	}

};
/****************************��������*********************************************/

/****************************��������*********************************************/



//=======��Vector3==================
template<>
class __EXPORT Vector<3>: public VectorBase<3>
{
public:
	Vector() : VectorBase<3>(){}
		
//	Vector(float x,float y,float z):data(x,y,z){}

	Vector(const Vector<3> &v) : VectorBase<3>(v) {}

	Vector(const float d[3]) : VectorBase<3>(d) {}
	
//	/**
//	 * set to value				//��������ƺ���������
//	 */
//	const Vector<3> &operator =(const Vector<3> &v) {
//		memcpy(this->data, v.data, sizeof(this->data));
//		return *this;
//	}
		
	//�������
	Vector<3> operator %(const Vector<3> &v) const
	{
		float tmp[3]={data[1]*v.data[2] - data[2]*v.data[1], data[2]*v.data[0] - data[0]*v.data[2], data[0]*v.data[1] - data[1]*v.data[0]};
		Vector<3> temp(tmp);
		return temp;
	}	

};		//end class Vector<3>

typedef Vector<3> Vector3;

	


}//end namespace math

#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

