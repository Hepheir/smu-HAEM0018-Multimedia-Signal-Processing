
// ImagePro_KimDongJooDoc.cpp : CImagePro_KimDongJooDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_KimDongJoo.h"
#endif

#include "ImagePro_KimDongJooDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImagePro_KimDongJooDoc

IMPLEMENT_DYNCREATE(CImagePro_KimDongJooDoc, CDocument)

BEGIN_MESSAGE_MAP(CImagePro_KimDongJooDoc, CDocument)
END_MESSAGE_MAP()


// CImagePro_KimDongJooDoc 생성/소멸

CImagePro_KimDongJooDoc::CImagePro_KimDongJooDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImagePro_KimDongJooDoc::~CImagePro_KimDongJooDoc()
{
}

BOOL CImagePro_KimDongJooDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}

// CImagePro_KimDongJooDoc serialization

void CImagePro_KimDongJooDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring() == TRUE)
	{
		ar.Write(resultImg, 256 * 256);
	}
	else
	{
		CFile *fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256) {
			ar.Read(inputImg, 256 * 256);
		}
		else {
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImagePro_KimDongJooDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImagePro_KimDongJooDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImagePro_KimDongJooDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImagePro_KimDongJooDoc 진단

#ifdef _DEBUG
void CImagePro_KimDongJooDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImagePro_KimDongJooDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImagePro_KimDongJooDoc 명령

void CImagePro_KimDongJooDoc::PixelAdd()
{
	int value = 0;

	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			value = inputImg[x][y] + 100;
			if (value > 255) {
				resultImg[x][y] = 255;
			}
			else {
				resultImg[x][y] = value;
			}
		}
	}
}


void CImagePro_KimDongJooDoc::PixelHistoEq()
{
	int x, y, i, k;
	int acc_hist = 0;
	float N = 256 * 256;
	int hist[256], sum[256];

	// initialize
	for (k = 0; k < 256; k++) {
		hist[k] = 0;
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			k = inputImg[y][x];
			hist[k] += 1;
		}
	}

	for (i = 0; i < 256; i++) {
		acc_hist = acc_hist + hist[i];
		sum[i] = acc_hist;
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			k = inputImg[y][x];
			resultImg[y][x] = sum[k] / N * 255;
		}
	}
}


void CImagePro_KimDongJooDoc::PixelTwoImageAdd()
{
	int value = 0;

	LoadTwoImages();

	for (int y = 0; y < 256; y++) {
		for (int x = 0; x < 256; x++) {
			value = inputImg[y][x] + inputImg2[y][x];
			if (value > 255) {
				resultImg[y][x] = 255;
			}
			else {
				resultImg[y][x] = value;
			}
		}
	}
}


void CImagePro_KimDongJooDoc::LoadTwoImages()
{
	CFile file;
	CFileDialog dlg(TRUE);

	AfxMessageBox("Select the First Image");

	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		file.Read(inputImg, 256 * 256);
		file.Close();
	}

	AfxMessageBox("Select the Second Image");

	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		file.Read(inputImg2, 256 * 256);
		file.Close();
	}
}
