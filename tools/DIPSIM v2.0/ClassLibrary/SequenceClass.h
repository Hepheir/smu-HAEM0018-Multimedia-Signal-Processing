// 
// Sequence.h
// 
// Last Modified : 2000/08/28
//
// By jw9557@dali.korea.ac.kr
//
#ifndef __SEQUENCE_CLASS
#define __SEQUENCE_CLASS

#include <string.h>
#include <stdlib.h>
#include "BasicType.h"
#include "ImageClass.h"

class AFX_EXT_CLASS CSequence  
{
public:
	CSequence();
	virtual ~CSequence();

	// Type : 0 -> YUV
	//        1 -> Y
	//        ...
	CSequence( CString strFileName, int iFrame, int iWidth, int iHeight, int iType = 1 );

	// Make Sequence File
	// Type : 0 -> YUV
	//        1 -> Y
	//        ...
	BOOL MakeSequenceFile( CString strFileName, int iFrame, int iWidth, int iHeight, int iType = 1 );

	// Get Y Frame Pointer from Sequence File.
	CImageFloat* GetFrame( int iFrame );

	// Set Y Frame Pointer from Sequence File.
	BOOL SetFrame( CImageFloat* pY, int iFrame );

	// Sequence의 이름을 얻는다.
	CString GetSequenceName();

	// Sequence의 이름을 정한다.
	void SetSequenceName( CString strFileName );

	// Get Number of Frames.
	int GetNumberOfFrames();
	
	// Sequence의 Frame수를 정한다.
	void SetNumberOfFrames( int iFrame );

	int GetType();

	void SetType( int iType );

	int GetWidth();

	int GetHeight();

	void SetWidth( int iWidth );

	void SetHeight( int iHeight );

// attribute
private:

	// Number of All frame.
	int m_iFrameSize;
	
	// Sequence file( successive CIF Formats )
	CString m_strFileName;

	// Type : 0 -> YUV
	//        1 -> Y
	//        ...
	int m_iType;

	// Width Of Frame Image
	int m_iWidth;

	// Height Of Frame Image
	int m_iHeight;
};

#endif
