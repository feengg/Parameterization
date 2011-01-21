//////////////////////////////////////////////////////////////////////
// Matrix.h
//
// ����������� CMatrix �������ӿ�
//
// �ܳ�������, 2002/8
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__ACEC32EA_5254_4C23_A8BD_12F9220EF43A__INCLUDED_)
#define AFX_MATRIX_H__ACEC32EA_5254_4C23_A8BD_12F9220EF43A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "../Common/BasicDataType.h"

// #if !defined(_BITSET_)
// #	include <bitset>
// #endif // !defined(_BITSET_)

//////////////////////////////////////////////////////////////////////////////////////
//
//(-- class CMatrix
//
class CMatrix  
{
	//
	// ���нӿں���
	//
public:
	bool SetRotation2Matrix(float angle, Coord axis);
	bool SetScale2Matrix(Coord scale);
	bool SetTrans2Matrix(Coord trans);
	bool TransformVector(Coord& coord);
	void Matrix2Array(double * data);
	void Array2Matrix(double * data);
	void Array2Matrix(double data[3][3]);
	void SetRowCol(int nRows, int nCols);

	//
	// ����������
	//

	CMatrix();										// �������캯��
	CMatrix(int nRows, int nCols);					// ָ�����й��캯��
	CMatrix(int nRows, int nCols, double value[]);	// ָ�����ݹ��캯��
	CMatrix(int nSize);								// �����캯��
	CMatrix(int nSize, double value[]);				// ָ�����ݷ����캯��
	CMatrix(const CMatrix& other);					// �������캯��
	bool	Init(int nRows, int nCols);				// ��ʼ������	
	bool	MakeUnitMatrix(int nSize);				// �������ʼ��Ϊ��λ����
	bool	MakeZeroMatrix(int nSize);				// �������ʼ��Ϊ�����
	virtual ~CMatrix();								// ��������
	void Matrix2Array(double** data);
	void Array2Matrix(double** data);

	//
	// Ԫ����ֵ����
	//

	bool	SetElement(int nRow, int nCol, double value);	// ����ָ��Ԫ�ص�ֵ
	double	GetElement(int nRow, int nCol) const;			// ��ȡָ��Ԫ�ص�ֵ
	void    SetData(double value[]);						// ���þ����ֵ
	int		GetNumColumns() const;							// ��ȡ���������
	int		GetNumRows() const;								// ��ȡ���������
	int     GetRowVector(int nRow, double* pVector) const;	// ��ȡ�����ָ���о���
	std::vector<double> GetRowVector(int nRow);
	int     GetColVector(int nCol, double* pVector) const;	// ��ȡ�����ָ���о���
	double* GetData() const;								// ��ȡ�����ֵ

	//
	// ��ѧ����
	//

	CMatrix& operator=(const CMatrix& other);
	bool operator==(const CMatrix& other) const;
	bool operator!=(const CMatrix& other) const;
	CMatrix	operator+(const CMatrix& other) const;
	CMatrix	operator-(const CMatrix& other) const;
	CMatrix	operator*(double value) const;
	CMatrix	operator*(const CMatrix& other) const;
	// ������˷�
	bool CMul(const CMatrix& AR, const CMatrix& AI, const CMatrix& BR, const CMatrix& BI, CMatrix& CR, CMatrix& CI) const;
	// �����ת��
	CMatrix Transpose() const;

	//
	// �㷨
	//

	// ʵ���������ȫѡ��Ԫ��˹��Լ����
	bool InvertGaussJordan();                                               
	// �����������ȫѡ��Ԫ��˹��Լ����
	bool InvertGaussJordan(CMatrix& mtxImag);                                 
	// �Գ��������������
	bool InvertSsgj();                                              
	// �в����Ⱦ�������İ����ط���
	bool InvertTrench();                                                    
	// ������ʽֵ��ȫѡ��Ԫ��˹��ȥ��
	double DetGauss();                                                              
	// ������ȵ�ȫѡ��Ԫ��˹��ȥ��
	int RankGauss();
	// �Գ��������������˹���ֽ�������ʽ����ֵ
	bool DetCholesky(double* dblDet);                                                               
	// ��������Ƿֽ�
	bool SplitLU(CMatrix& mtxL, CMatrix& mtxU);                                     
	// һ��ʵ�����QR�ֽ�
	bool SplitQR(CMatrix& mtxQ);                                                      
	// һ��ʵ���������ֵ�ֽ�
	bool SplitUV(CMatrix& mtxU, CMatrix& mtxV, double eps = 0.000001);                                       
	// ������������ֵ�ֽⷨ
	bool GInvertUV(CMatrix& mtxAP, CMatrix& mtxU, CMatrix& mtxV, double eps = 0.000001);
	// Լ���Գƾ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��
	bool MakeSymTri(CMatrix& mtxQ, CMatrix& mtxT, double dblB[], double dblC[]);
	// ʵ�Գ����Խ����ȫ������ֵ�����������ļ���
	bool SymTriEigenv(double dblB[], double dblC[], CMatrix& mtxQ, int nMaxIt = 60, double eps = 0.000001);
	// Լ��һ��ʵ����Ϊ���겮�����ĳ������Ʊ任��
	void MakeHberg();
	// ����겮�����ȫ������ֵ��QR����
	bool HBergEigenv(double dblU[], double dblV[], int nMaxIt = 60, double eps = 0.000001);
	// ��ʵ�Գƾ�������ֵ�������������ſɱȷ�
	bool JacobiEigenv(double dblEigenValue[], CMatrix& mtxEigenVector, int nMaxIt = 60, double eps = 0.000001);
	// ��ʵ�Գƾ�������ֵ�������������ſɱȹ��ط�
	bool JacobiEigenv2(double dblEigenValue[], CMatrix& mtxEigenVector, double eps = 0.000001);

	//
	// ���������ݳ�Ա
	//
protected:
	int	m_nNumColumns;			// ��������
	int	m_nNumRows;				// ��������
	double*	m_pData;			// �������ݻ�����

	//
	// �ڲ�����
	//
private:
	void ppp(double a[], double e[], double s[], double v[], int m, int n);
	void sss(double fg[2], double cs[2]);

};
//
//--) // class CMatrix
//
//////////////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_MATRIX_H__ACEC32EA_5254_4C23_A8BD_12F9220EF43A__INCLUDED_)
