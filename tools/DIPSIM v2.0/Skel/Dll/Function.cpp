#include "stdafx.h"
#include "ImageClass.h"
#include "MatrixClass.h"

extern "C" __declspec(dllexport)
BOOL Invert( CImageByte* pIn, CImageByte* pOut )
{
	pOut->Alloc( pIn->GetWidth(), pIn->GetHeight() );

	for ( int iC = 0; iC < pIn->GetWidth() * pIn->GetHeight(); iC++ )
	{
		pOut->Get1DImage()[iC] = 255 - pIn->Get1DImage()[iC];
	}

	return TRUE;
}