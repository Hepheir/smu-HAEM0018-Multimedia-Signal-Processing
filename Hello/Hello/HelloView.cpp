
// HelloView.cpp : CHelloView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Hello.h"
#endif

#include "HelloDoc.h"
#include "HelloView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelloView

IMPLEMENT_DYNCREATE(CHelloView, CView)

BEGIN_MESSAGE_MAP(CHelloView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHelloView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PRINT_HELLO, &CHelloView::OnPrintHello)
END_MESSAGE_MAP()

// CHelloView 생성/소멸

CHelloView::CHelloView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CHelloView::~CHelloView()
{
}

BOOL CHelloView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CHelloView 그리기

void CHelloView::OnDraw(CDC* pDC)
{
	CHelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->TextOut(100, 100, "첫 번째 영상처리 프로그램 예제입니다.");
}


// CHelloView 인쇄


void CHelloView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHelloView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CHelloView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CHelloView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CHelloView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHelloView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHelloView 진단

#ifdef _DEBUG
void CHelloView::AssertValid() const
{
	CView::AssertValid();
}

void CHelloView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelloDoc* CHelloView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelloDoc)));
	return (CHelloDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelloView 메시지 처리기

void CHelloView::OnPrintHello()
{
	AfxMessageBox("안녕하세요 여러분!!!");
}