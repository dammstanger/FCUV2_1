/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Vector.h
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

#ifndef __VECTOR_H_
#define __VECTOR_H_
/****************************包含头文件*******************************************/
#include <sys_code_ctl.h>
/****************************宏定义***********************************************/

/****************************类型定义*********************************************/

/****************************类定义*********************************************/
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
	float &operator[](const unsigned int i) {			//()符重载 返回一个float & 即float型的引用
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
	 * negation 每个元素取负值
	 */
	const Vector<N> operator -(void) const {
		Vector<N> res;

		for (unsigned int i = 0; i < N; i++)
			res.data[i] = -data[i];

		return res;
	}

	/**
	 * addition 求和
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
	 * uniform scaling均匀缩放
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
	 * gets the length of this vector squared	模的平方
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
		*this /= length();			//对本对象成员data的每一个元素/模
	}

	/**
	 * returns the normalized version of this vector
	 */
	Vector<N> normalized() const {		//后带的const声明该函数不改变数据成员的值，可保证被篡改
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
class __EXPORT Vector : public VectorBase<N>			//类继承   派生类:基类 public表示公有派送
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
/****************************变量声明*********************************************/

/****************************变量定义*********************************************/



//=======类Vector3==================
template<>
class __EXPORT Vector<3>: public VectorBase<3>
{
public:
	Vector() : VectorBase<3>(){}
		
//	Vector(float x,float y,float z):data(x,y,z){}

	Vector(const Vector<3> &v) : VectorBase<3>(v) {}

	Vector(const float d[3]) : VectorBase<3>(d) {}
	
//	/**
//	 * set to value				//此运算符似乎不用重载
//	 */
//	const Vector<3> &operator =(const Vector<3> &v) {
//		memcpy(this->data, v.data, sizeof(this->data));
//		return *this;
//	}
		
	//向量叉积
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

