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
**********************************************************************************/

#ifndef __MATRIX_H_
#define __MATRIX_H_

/****************************包含头文件*******************************************/
#include <sys_code_ctl.h>
#include "Vector.h"
/****************************宏定义***********************************************/

/****************************类型定义*********************************************/

/****************************类定义***********************************************/
namespace math
{
	//派生类
template<unsigned int M, unsigned int N>
class __EXPORT Matrix;

	// MxN matrix with float elements
template <unsigned int M, unsigned int N>
class __EXPORT MatrixBase
{
public:
	/**
	 * matrix data[row][col]
	 */
	float data[M][N];

	/**
	 * struct for using arm_math functions
	 */
	arm_matrix_instance_f32 arm_mat;


	/**
	 * trivial ctor
	 * Initializes the elements to zero.
	 */
	MatrixBase()
	{
		arm_mat.numRows = M;
		arm_mat.numCols = N;
		arm_mat.pData = &data[0][0];
		for(int i=0;i<N*M;i++)
			arm_mat.pData[i]=0.0f;
	}

	virtual ~MatrixBase() {};

	/**
	 * copyt ctor 数个同名的 函数重载 或多态
	 */
	MatrixBase(const MatrixBase<M, N> &m) 
	{
		arm_mat.numRows = M;
		arm_mat.numCols = N;
		arm_mat.pData = &data[0][0];
		memcpy(data, m.data, sizeof(data));
	}

	MatrixBase(const float *d)
	{
		arm_mat.numRows = M;
		arm_mat.numCols = N;
		arm_mat.pData = &data[0][0];
		memcpy(data, d, sizeof(data));
	}

	MatrixBase(const float d[M][N])
	{
		arm_mat.numRows = M;
		arm_mat.numCols = N;
		arm_mat.pData = &data[0][0];
		memcpy(data, d, sizeof(data));
	}

	/**
	 * set data
	 */
	void set(const float *d) {
		memcpy(data, d, sizeof(data));
	}

	/**
	 * set data
	 */
	void set(const float d[M][N]) {
		memcpy(data, d, sizeof(data));
	}

	/**
	 * set row from vector
	 */
	void set_row(unsigned int row, const Vector<N> v) {
		for (unsigned i = 0; i < N; i++) {
			data[row][i] = v.data[i];
		}
	}

	/**
	 * set column from vector
	 */
	void set_col(unsigned int col, const Vector<M> v) {
		for (unsigned i = 0; i < M; i++) {
			data[i][col] = v.data[i];
		}
	}

	/**
	 * access by index
	 */
	float &operator()(const unsigned int row, const unsigned int col) {
		return data[row][col];
	}

	/**
	 * access by index
	 */
	float operator()(const unsigned int row, const unsigned int col) const {
		return data[row][col];
	}

	/**
	 * get rows number
	 */
	unsigned int get_rows() const {
		return M;
	}

	/**
	 * get columns number
	 */
	unsigned int get_cols() const {
		return N;
	}

	/**
	 * test for equality
	 */
	bool operator ==(const Matrix<M, N> &m) const {
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				if (data[i][j] != m.data[i][j])
					return false;

		return true;
	}

	/**
	 * test for inequality
	 */
	bool operator !=(const Matrix<M, N> &m) const {
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				if (data[i][j] != m.data[i][j])
					return true;

		return false;
	}

	/**
	 * set to value
	 */
	const Matrix<M, N> &operator =(const Matrix<M, N> &m) {
		memcpy(data, m.data, sizeof(data));
		return *static_cast<Matrix<M, N>*>(this);
	}

	/**
	 * negation
	 */
	Matrix<M, N> operator -(void) const {
		Matrix<M, N> res;

		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				res.data[i][j] = -data[i][j];

		return res;
	}

	/**
	 * addition
	 */
	Matrix<M, N> operator +(const Matrix<M, N> &m) const {
		Matrix<M, N> res;

		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				res.data[i][j] = data[i][j] + m.data[i][j];

		return res;
	}

	Matrix<M, N> &operator +=(const Matrix<M, N> &m) {
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				data[i][j] += m.data[i][j];

		return *static_cast<Matrix<M, N>*>(this);
	}

	/**
	 * subtraction
	 */
	Matrix<M, N> operator -(const Matrix<M, N> &m) const {
		Matrix<M, N> res;

		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				res.data[i][j] = data[i][j] - m.data[i][j];

		return res;
	}

	Matrix<M, N> &operator -=(const Matrix<M, N> &m) {
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				data[i][j] -= m.data[i][j];

		return *static_cast<Matrix<M, N>*>(this);
	}

	/**
	 * uniform scaling
	 */
	Matrix<M, N> operator *(const float num) const {
		Matrix<M, N> res;

		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				res.data[i][j] = data[i][j] * num;

		return res;
	}

	Matrix<M, N> &operator *=(const float num) {
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				data[i][j] *= num;

		return *static_cast<Matrix<M, N>*>(this);
	}

	Matrix<M, N> operator /(const float num) const {
		Matrix<M, N> res;

		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				res.data[i][j] = data[i][j] / num;

		return res;
	}

	Matrix<M, N> &operator /=(const float num) {
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				data[i][j] /= num;

		return *static_cast<Matrix<M, N>*>(this);
	}

	/**
	 * multiplication by another matrix
	 */
	template <unsigned int P>
	Matrix<M, P> operator *(const Matrix<N, P> &m) const {
		Matrix<M, P> res;
		arm_mat_mult_f32(&arm_mat, &m.arm_mat, &res.arm_mat);
		return res;
	}

	/**
	 * transpose the matrix转置
	 */
	Matrix<N, M> transposed(void) const {
		Matrix<N, M> res;
		arm_mat_trans_f32(&this->arm_mat, &res.arm_mat);
		return res;
	}

	/**
	 * invert the matrix
	 */
	Matrix<M, N> inversed(void) const {
		Matrix<M, N> res;
		arm_mat_inverse_f32(&this->arm_mat, &res.arm_mat);
		return res;

	}

	/**
	 * set zero matrix
	 */
	void zero(void) {
		memset(data, 0, sizeof(data));
	}

	/**
	 * set identity matrix
	 */
	void identity(void) {
		memset(data, 0, sizeof(data));
		unsigned int n = (M < N) ? M : N;

		for (unsigned int i = 0; i < n; i++)
			data[i][i] = 1;
	}

};



template <unsigned int M, unsigned int N>
class __EXPORT Matrix : public MatrixBase<M, N>
{
public:
	using MatrixBase<M, N>::operator *;

	Matrix() : MatrixBase<M, N>() {}

	Matrix(const Matrix<M, N> &m) : MatrixBase<M, N>(m) {}

	Matrix(const float *d) : MatrixBase<M, N>(d) {}

	Matrix(const float d[M][N]) : MatrixBase<M, N>(d) {}

	/**
	 * set to value
	 */
	const Matrix<M, N> &operator =(const Matrix<M, N> &m) {
		memcpy(this->data, m.data, sizeof(this->data));
		return *this;
	}

	/**
	 * multiplication by a vector
	 */
	Vector<M> operator *(const Vector<N> &v) const {
		Vector<M> res;
		arm_mat_mult_f32(&this->arm_mat, &v.arm_col, &res.arm_col);

		return res;
	}
};


template <>
class __EXPORT Matrix<3, 3> : public MatrixBase<3, 3>//定义一个类Matrix继承自MatrixBase
{
public:
	using MatrixBase<3, 3>::operator *;

	Matrix() : MatrixBase<3, 3>() {}

	Matrix(const Matrix<3, 3> &m) : MatrixBase<3, 3>(m) {}

	Matrix(const float *d) : MatrixBase<3, 3>(d) {}

	Matrix(const float d[3][3]) : MatrixBase<3, 3>(d) {}
	/**
	 * set data
	 */
	void set(const float d[9]) {
		memcpy(data, d, sizeof(data));
	}


	/**
	 * set to value
	 */
	const Matrix<3, 3> &operator =(const Matrix<3, 3> &m) {
		memcpy(this->data, m.data, sizeof(this->data));
		return *this;
	}

	/**
	 * multiplication by a vector 矩阵乘以矢量
	 */
	Vector<3> operator *(const Vector<3> &v) const{			
		float tmp[3]={data[0][0] * v.data[0] + data[0][1] * v.data[1] + data[0][2] * v.data[2],
		data[1][0] * v.data[0] + data[1][1] * v.data[1] + data[1][2] * v.data[2],
		data[2][0] * v.data[0] + data[2][1] * v.data[1] + data[2][2] * v.data[2]};
		Vector<3> res(tmp);
		return res;
	}
	/**
	 * create a rotation matrix from given euler angles
	 * based on http://gentlenav.googlecode.com/files/EulerAngles.pdf
	 */
	void from_euler(float roll, float pitch, float yaw);

	/**
	 * get euler angles from rotation matrix
	 */
	Vector<3> to_euler(void) const;
};

/****************************变量声明*********************************************/

/****************************变量定义*********************************************/
typedef Matrix<3,3>	Matrix3;



}

#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

