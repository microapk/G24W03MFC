﻿
// G24W03MFCDoc.h: CG24W03MFCDoc 클래스의 인터페이스
//


#pragma once


class CG24W03MFCDoc : public CDocument
{
	protected:
	//	CPoint Point = CPoint(-100, -100);
		CArray<CPoint, CPoint> Points;
	public:
		int GetPointsCount() { return (int)Points.GetCount(); }
		CPoint GetPoint(int index) { return Points[index]; }
	//	void SetPoint(CPoint p) { 
	//		Point = p; 
	//		SetModifiedFlag();
	//	}
	void AddPoint(CPoint p){
		Points.Add(p);
		SetModifiedFlag();
	}

	void RemoveLast() {
		if (Points.GetCount() > 0) {
			Points.RemoveAt(Points.GetCount() - 1);
			SetModifiedFlag();
		}
	}


protected: // serialization에서만 만들어집니다.
	CG24W03MFCDoc() noexcept;
	DECLARE_DYNCREATE(CG24W03MFCDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CG24W03MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
