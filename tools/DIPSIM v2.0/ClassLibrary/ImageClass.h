// 
// ImageClass.H
// 
// Last Modified : 2000/06/30
//
// By jw9557@dali.korea.ac.kr
//
#ifndef __IMAGE_CLASS
#define __IMAGE_CLASS

#include <string.h>
#include <stdlib.h>
#include "BasicType.h"

class CImageByte;
class CImageFloat;
class CImageComplex;
class CImageRGB;

enum { IT_BYTE, IT_FLOAT, IT_COMPLEX, IT_RGB, IT_SEQ, IT_VECTOR, IT_UNKNOWN = 100 };

////////////////////////////////////////////////////////////////////////////
//
// Class : CImageObject
//
// Des : 모든 하위 클래스를 받을수 있게 하는 최상위 클래스                      
//
////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CImageObject 
{
// attribute
private:

	// 가로크기
	int m_iWidth;
	
	// 세로크기
	int m_iHeight; 

protected:

	// Image의 타입정보
	int m_iType;	

// methods
public:

	// Constructor
	CImageObject();

	// Destructor
	~CImageObject();

	// Image의 종류를 얻는다.
	int GetType();

	// Image의 종류를 설정한다.
	void SetType( int iType );

	// Image의 가로 크기를 얻는다.
	int GetWidth(); 
	
	// Image의 세로 크기를 얻는다.
	int GetHeight(); 

	// Image의 가로 크기를 설정한다.
	void SetWidth( int nWidth );
	
	// Image의 세로 크기를 설정한다.
	void SetHeight( int nHeight ); 
};


template <class T> 
class AFX_EXT_CLASS CImageTemplate : public CImageObject 
{
// attribute
protected:

	// 1DImage Pointer의 인덱스 정보를 가지는 Pointer
	// 2D 형식의 Array를 지원해 준다.
	T** m_p2DImage;		

	// 실제 Image 정보가 들어가 있는 1D Array
	T* m_p1DImage;

// methods
public:

	// Constructor
	CImageTemplate();

	// Destructor
	~CImageTemplate();

	// 1DImage의 포인터를 바로 얻어온다.
	T* Get1DImage();
	const T* Get1DImage() const;

	// 2DImage의 포인터를 바로 얻어온다.
	T** Get2DImage();
	const T** Get2DImage() const;

	// 메모리의 할당
	BOOL Alloc( int iWidth, int iHeight );

	// 할당된 메모리의 해제
	BOOL Free();

	// 한 픽셀의 정보를 얻어온다.
	void GetPixel( T &pixel, int nX, int nY );

	// 한 픽셀의 정보를 얻어온다.
	T GetPixel( int nX, int nY );

	// 픽셀의 정보를 저장한다.
	void SetPixel( T pixel, int nX, int nY );

	// 메모리가 할당되었는지 알아본다.
	BOOL IsAlloc();

	// [] operator overloading
	T* operator[]( int iIndex ); 
};

//
// CImageTemplate Member Functions
//

template <class T> 
CImageTemplate<T>::CImageTemplate()
{
	m_p1DImage = NULL;
	m_p2DImage = NULL;
}

// Destructor
template <class T> 
CImageTemplate<T>::~CImageTemplate()
{
	if ( Free() == FALSE )
	{
		AfxMessageBox( "Free(): Memory Free Error" );
	}
}

// 메모리의 할당
template <class T> 
BOOL CImageTemplate<T>::Alloc( int iWidth, int iHeight )
{
	SetWidth( iWidth );
	SetHeight( iHeight );

	m_p1DImage = (T*)GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT, iWidth * iHeight * sizeof( T ) );

	if ( m_p1DImage == NULL ) return FALSE;
	
	m_p2DImage = new T*[ iHeight ];

	if ( m_p2DImage == NULL ) return FALSE;

	for( int iC = 0; iC < iHeight; iC++ ) m_p2DImage[iC] = (T*)( m_p1DImage + iWidth * iC );

	return TRUE;
}

// 할당된 메모리의 해제
template <class T> 
BOOL CImageTemplate<T>::Free()
{
	if ( m_p1DImage == NULL ) return FALSE;
	
	delete []m_p2DImage;
	GlobalFree( (HGLOBAL)m_p1DImage );

	m_p1DImage = NULL;
	m_p2DImage = NULL;

	return TRUE;
}

// 1DImage의 포인터를 바로 얻어온다.
template <class T> 
T* CImageTemplate<T>::Get1DImage()
{
	return (T*)m_p1DImage;
}

template <class T> 
const T* CImageTemplate<T>::Get1DImage() const
{
	return (const T*)m_p1DImage;
}

// 2DImage의 포인터를 바로 얻어온다.
template <class T> 
T** CImageTemplate<T>::Get2DImage()
{
	return (T**)m_p2DImage;
}

template <class T> 
const T** CImageTemplate<T>::Get2DImage() const
{
	return (const T**)m_p2DImage;
}

// 메모리가 할당되었는지 알아본다.
template <class T> 
BOOL CImageTemplate<T>::IsAlloc()
{
	return (m_p1DImage != NULL) ? TRUE : FALSE;
}

// 한 픽셀의 정보를 얻어온다.
template <class T> 
void CImageTemplate<T>::GetPixel( T &pixel, int iX, int iY )
{
	pixel = m_p2DImage[iX][iY];
}

// 한 픽셀의 정보를 얻어온다.
template <class T> 
T CImageTemplate<T>::GetPixel( int iX, int iY )
{
	return m_p2DImage[iX][iY];
}

// 픽셀의 정보를 저장한다.
template <class T> 
void CImageTemplate<T>::SetPixel( T pixel, int iX, int iY )
{
	m_p2DImage[iX][iY] = pixel;
}

template <class T>
T* CImageTemplate<T>::operator[]( int iIndex ) 
{
	ASSERT( iIndex >= 0 && iIndex < GetHeight() );
	return m_p2DImage[iIndex];
}

class AFX_EXT_CLASS CImageByte : public CImageTemplate<BYTE> 
{
// methods
public:

	// Constructor	
	CImageByte();
	CImageByte( int iWidth, int iHeight );
	CImageByte( CImageByte& Object );
	CImageByte( CImageFloat& Object );
	CImageByte( CImageComplex& Object );
	CImageByte( CImageRGB& Object );

	~CImageByte();

	// Operator overloading
	CImageByte& operator=( CImageByte& Object );
	CImageByte& operator=( CImageFloat& Object );
	CImageByte& operator=( CImageComplex& Object );
	CImageByte& operator=( CImageRGB& Object );
};

class AFX_EXT_CLASS CImageFloat : public CImageTemplate<FLOAT> 
{
// methods
public:

	// Constructor	
	CImageFloat();
	CImageFloat( int iWidth, int iHeight );
	CImageFloat( CImageByte& Object );
	CImageFloat( CImageFloat& Object );
	CImageFloat( CImageComplex& Object );
	CImageFloat( CImageRGB& Object );

	~CImageFloat();

	// Operator overloading
	CImageFloat& operator=( CImageByte& Object );
	CImageFloat& operator=( CImageFloat& Object );
	CImageFloat& operator=( CImageComplex& Object );
	CImageFloat& operator=( CImageRGB& Object );
};

class AFX_EXT_CLASS CImageComplex : public CImageTemplate<COMPLEX> 
{
// methods
public:

	// Constructor
	CImageComplex();
	CImageComplex( int iWidth, int iHeight );
	CImageComplex( CImageByte& Object );
	CImageComplex( CImageFloat& Object );
	CImageComplex( CImageComplex& Object );
	CImageComplex( CImageRGB& Object );

	~CImageComplex();

	// Operator overloading
	CImageComplex& operator=( CImageByte& Object );
	CImageComplex& operator=( CImageFloat& Object );
	CImageComplex& operator=( CImageComplex& Object );
	CImageComplex& operator=( CImageRGB& Object );

	// 픽셀의 Imaginary 데이터를 얻는다.
	void GetPixelIm( float &fIm, int iX, int iY );

	// 픽셀의 Imaginary 데이터를 얻는다.
	float GetPixelIm( int iX, int iY );

	// 픽셀의 Real 데이터를 얻는다.
	void GetPixelRe( float &fRe, int iX, int iY );

	// 픽셀의 Real 데이터를 얻는다.
	float GetPixelRe( int iX, int iY );

	// 픽셀의 Imaginary 정보를 세긴다.
	void SetPixelIm( float fIm, int iX, int iY ); 

	// 픽셀의 Real 정보를 세긴다.
	void SetPixelRe( float fRe, int iX, int iY );
};

class AFX_EXT_CLASS CImageRGB : public CImageTemplate<RGB> 
{
// methods
public:

	// Constructor	
	CImageRGB();
	CImageRGB( int iWidth, int iHeight );
	CImageRGB( CImageByte& Object );
	CImageRGB( CImageFloat& Object );
	CImageRGB( CImageComplex& Object );
	CImageRGB( CImageRGB& Object );

	~CImageRGB();

	// Operator overloading
	CImageRGB& operator=( CImageByte& Object );
	CImageRGB& operator=( CImageFloat& Object );
	CImageRGB& operator=( CImageComplex& Object );
	CImageRGB& operator=( CImageRGB& Object );

	// 픽셀의 R 데이터를 얻는다.
	void GetPixelR( BYTE &byR, int iX, int iY );
	BYTE GetPixelR( int iX, int iY );

	// 픽셀의 G 데이터를 얻는다.
	void GetPixelG( BYTE &byG, int iX, int iY );
	BYTE GetPixelG( int iX, int iY );
	
	// 픽셀의 B 데이터를 얻는다.
	void GetPixelB( BYTE &byB, int iX, int iY );
	BYTE GetPixelB( int iX, int iY );

	// 픽셀의 RGB 데이터를 얻는다.
	void GetPixelRGB( RGB &rgb, int iX, int iY );
	RGB GetPixelRGB( int iX, int iY );

	// 픽셀의 R,G,B값을 쓴다.
	void SetPixelR( BYTE byR, int iX, int iY ); 
	void SetPixelG( BYTE byG, int iX, int iY ); 
	void SetPixelB( BYTE byB, int iX, int iY ); 

	// 픽셀의 RGB 정보를 세긴다.
	void SetPixelRGB( RGB rgb, int iX, int iY );
	void SetPixelRGB( BYTE byR, BYTE byG, BYTE byB, int iX, int iY );

	// YUV와 RGB의 변환
	YUV RGBtoYUV( RGB rgb );
	RGB YUVtoRGB( YUV yuv );

	// HSI와 RGB의 변환
	HSI RGBtoHSI( RGB rgb );
	RGB HSItoRGB( HSI hsi );
};


#endif // __IMAGE_CLASS