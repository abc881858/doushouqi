// TESTView.h : interface of the CTESTView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__B3D84CEC_F4ED_4FBE_BD50_6BF5F37D1872__INCLUDED_)
#define AFX_TESTVIEW_H__B3D84CEC_F4ED_4FBE_BD50_6BF5F37D1872__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetControl.h"
#include "hess.h"

#define	ID_OK		100

class CTESTView : public CView
{
protected: // create from serialization only
	CTESTView();
	DECLARE_DYNCREATE(CTESTView)

// Attributes
public:
	CTESTDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTESTView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

	int	num1;
	int	num2;

	//定义画图用CDC
	CDC	Background;
	CDC ChessAll;
	CDC Mask;
	CDC Choose;

	
	//定义画图用CBitmap
	CBitmap	m_background;
	CBitmap m_chess;
	CBitmap m_mask;
	CBitmap m_choose;


	CButton	m_ok;


// Implementation
public:
	CNetControl *m_pControl;

	void OnOK();

	void PrintAll();

	int SelectNum(int x, int y);

	void DrawChoose(int x,int y,CDC *pdc);

	void DrawChess(Chess ch,CDC *pdc);

	virtual ~CTESTView();

#ifdef _DEBUG

	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTESTView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TESTView.cpp
inline CTESTDoc* CTESTView::GetDocument()
   { return (CTESTDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__B3D84CEC_F4ED_4FBE_BD50_6BF5F37D1872__INCLUDED_)
