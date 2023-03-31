//
// BasicType.h
//
// Last Modified : 2000/05/04
//
// By jw9557@dali.korea.ac.kr
//
#ifndef __BASIC_TYPE
#define __BASIC_TYPE

typedef unsigned char	BYTE;

typedef int				INT;

typedef float			FLOAT;

typedef struct {
	float fRe;
	float fIm;
} COMPLEX;

typedef struct {
	int iX;
	int iY;
} VECTOR;

typedef struct {
	BYTE byR;
	BYTE byG;
	BYTE byB;
} RGB;

typedef struct {
	float fY;
	float fU;
	float fV;
} YUV;

typedef struct {
	float fH;
	float fS;
	float fI;
} HSI;

#endif // __BASIC_TYPE