
// G24W03MFCView.cpp: CG24W03MFCView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "G24W03MFC.h"
#endif

#include "G24W03MFCDoc.h"
#include "G24W03MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CG24W03MFCView

IMPLEMENT_DYNCREATE(CG24W03MFCView, CView)

BEGIN_MESSAGE_MAP(CG24W03MFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE() // SCREAMING 스네이크 케이스
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CG24W03MFCView 생성/소멸

CG24W03MFCView::CG24W03MFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CG24W03MFCView::~CG24W03MFCView()
{
}

BOOL CG24W03MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CG24W03MFCView 그리기

void CG24W03MFCView::OnDraw(CDC* pDC)
{
	CG24W03MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//CPoint p = pDoc->GetPoint();
	//pDC->Ellipse(p.x - 30, p.y - 30, p.x + 30, p.y + 30);
	
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CRect rect;
	GetClientRect(&rect);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	CBitmap* old = memDC.SelectObject(&bmp);

	memDC.FillSolidRect(rect, RGB(255, 255, 255));

	int n = pDoc->GetPointsCount();
	
	CString countString;
	countString.Format(L"L Count: %d", n);
	memDC.TextOutW(10, 10, countString);

	CPoint p;

	for (int i = 0; i < n; i++) {
		p = pDoc->GetPoint(i);
		//pDC->Ellipse(p.x - 30, p.y - 30, p.x + 30, p.y + 30);
		memDC.Ellipse(p.x - 30, p.y - 30, p.x + 30, p.y + 30);
	}
	pDC->BitBlt(0, 0,
		rect.Width(), rect.Height(),
		&memDC,
		0, 0,
		SRCCOPY);

	memDC.SelectObject(old);
}


// CG24W03MFCView 인쇄

BOOL CG24W03MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CG24W03MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CG24W03MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CG24W03MFCView 진단

#ifdef _DEBUG
void CG24W03MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CG24W03MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CG24W03MFCDoc* CG24W03MFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CG24W03MFCDoc)));
	return (CG24W03MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CG24W03MFCView 메시지 처리기


void CG24W03MFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CClientDC dc(this);
	//dc.Ellipse(point.x - 30, point.y - 30, point.x + 30, point.y + 30);

	GetDocument()->AddPoint(point);
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CG24W03MFCView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	GetDocument()->RemoveLast();
	Invalidate();


	CView::OnRButtonDown(nFlags, point);
}

void CG24W03MFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON) { // 윈도우 NFLAG를 제공 BOOL 값이라 TRUE FALSE 값으로 나눈다. 버튼을 누르고 있을 때
		GetDocument()->AddPoint(point);
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL CG24W03MFCView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}
