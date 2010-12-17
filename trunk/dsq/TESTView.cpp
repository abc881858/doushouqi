// TESTView.cpp : implementation of the CTESTView class
//

#include "stdafx.h"
#include "TEST.h"

#include "TESTDoc.h"
#include "TESTView.h"
#include "Managers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Managers manager;//申明全局变量

/////////////////////////////////////////////////////////////////////////////
// CTESTView

IMPLEMENT_DYNCREATE(CTESTView, CView)

BEGIN_MESSAGE_MAP(CTESTView, CView)
	//{{AFX_MSG_MAP(CTESTView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_OK,OnOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTESTView construction/destruction

CTESTView::CTESTView()
{
	// TODO: add construction code here
	m_pControl= new CNetControl(this);
}

CTESTView::~CTESTView()
{
}

BOOL CTESTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	// 加载位图
	m_background.LoadBitmap(IDB_BACKGROUND);
	m_chess.LoadBitmap(IDB_CHESS);
	m_mask.LoadBitmap(IDB_MASK);
	m_choose.LoadBitmap(IDB_CHOOSE);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTESTView diagnostics

#ifdef _DEBUG
void CTESTView::AssertValid() const
{
	CView::AssertValid();
}

void CTESTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTESTDoc* CTESTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTESTDoc)));
	return (CTESTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTESTView drawing

void CTESTView::OnDraw(CDC* pDC)
{
	CTESTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	// 初始化CDC
	static bool st=TRUE;
	if (st)
	{
		Background.CreateCompatibleDC(pDC);
		Background.SelectObject(m_background);
		ChessAll.CreateCompatibleDC(pDC);
		ChessAll.SelectObject(m_chess);
		Mask.CreateCompatibleDC(pDC);
		Mask.SelectObject(m_mask);
		Choose.CreateCompatibleDC(pDC);
		Choose.SelectObject(m_choose);

		st=FALSE;
		
// 		MCI_OPEN_PARMS op;
// 		op.dwCallback=NULL;
// 		op.lpstrAlias=NULL;
// 		op.lpstrDeviceType=_T("MPEGAudio"); //设备类型，大多数文件可以这样设置
// 		op.lpstrElementName=_T("sound\\backmusic.mp3") ;//文件路径
// 		op.wDeviceID=NULL;                            //打开设备成功以后保存这个设备号备用
// 		UINT rs;                                                 //接受函数返回结果
// 		rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT ,(DWORD)&op);//发送命令打开设备，成功返回0，否则返回错误号，第三个参数这里必须是MCI_OPEN_ELEMENT 
// 		if(rs==0)             //设备打开成功就播放文件
// 		{
// 			MCI_PLAY_PARMS pp;
// 			pp.dwCallback=NULL;
// 			pp.dwFrom=0;                      //开始播放的位置
// 			mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);//播放文件 还要循环!!!
// 		}
	}
	
	PrintAll();
}

///////////////////////////////////////////////////////////////////////
/*
函数名称：PrintAll(CDC *pdc)
函数介绍：用来整体重画
输入参数：绘图用CDC
输出参数：无
返回值	：无
*/
void CTESTView::PrintAll()
{
 	CDC *pdc=GetDC();

	pdc->BitBlt(0,0,500,636,&Background,0,0,SRCCOPY);

	for(int k=0; k<=15; k++)
	{
		if(manager.nChessinfo[k].type<9)
		{
			if(!manager.nChessinfo[k].color)
			{
				pdc->BitBlt(7+manager.nChessinfo[k].x*70,6+manager.nChessinfo[k].y*70,
					64,62,&ChessAll,(manager.nChessinfo[k].type-1)*64,0,SRCAND);
			}
			else
			{
				pdc->BitBlt(7+manager.nChessinfo[k].x*70,6+manager.nChessinfo[k].y*70,
					64,62,&ChessAll,(manager.nChessinfo[k].type-1)*64,62,SRCAND);
			}
		}
	}


// 	if(manager.Game_State!=0 && manager.Game_State!=1)
// 	{
// 		num1=100;
// 		num2=100;
// 	}
// 
// 	if(num1<100)
// 	{
// 		DrawChoose(num1%10,num1/10,&Buffer);
// 	}
// 	
// 	if(num2<100)
// 	{
// 		DrawChoose(num2%10,num2/10,&Buffer);
// 	}


	ReleaseDC(pdc);

}

/////////////////////////////////////////////////////////////////////////////
// CTESTView message handlers

void CTESTView::OnMouseMove(UINT nFlags, CPoint point)
{
	CDC *pDC=GetDC();
	//跟踪光标坐标
	CString st;
	st.Format("%d  ,%d  ",point.x,point.y);
	pDC->TextOut(600,50,st);

	ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}

void CTESTView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDC *pdc=GetDC();
	
	int k;
	if(point.x>=7 && point.y>=6 && point.x<=494 && point.y<=630)
	{
		k=SelectNum(point.x, point.y);

		if(manager.DoMsg(k%10, k/10, 1))
		{
			num1=k;
			PrintAll();

			char st[10];
			sprintf(st,"33%d%d", k%10, k/10);

			m_pControl->SendMsg(st);

			if(manager.Game_State>1)
			{
				m_pControl->m_Ready[0]=false;
				m_pControl->m_Ready[1]=false;
			}
		}
		else
		{
			num1=100;
			PrintAll();
		}

		CString	st;
		st.Format("%d    ,%d    ", num1%10, num1/10);
		pdc->TextOut(600,80,st);

	}

	ReleaseDC(pdc);

	CView::OnLButtonDown(nFlags, point);
}


BOOL CTESTView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//	TODO: Add your message handler code here and/or call default
	
// 	HCURSOR m_hCur = AfxGetApp()->LoadCursor(IDC_CURSOR3);
// 	::SetCursor(m_hCur);
// 	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)m_hCur);
	
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CTESTView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	
	CView::OnRButtonUp(nFlags, point);
}

int CTESTView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	int k;

	m_pControl->OnSorc();

// 	if(m_pControl->m_Isserver)
// 	{
// 		k=MessageBox("是否选择先手(Y/N)","象棋",MB_OKCANCEL);
// 		if(k==IDOK)
// 		{
// 			manager.PlayerAc=0;
// 		}
// 		else if(k==IDCANCEL)
// 		{
// 			manager.PlayerAc=1;
// 		}
// 	}

	m_ok.Create(_T("开始"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		CRect(615,355,715,395), this, ID_OK);
	m_ok.ShowWindow(SW_SHOW);
	
	return 0;
}

void CTESTView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnTimer(nIDEvent);
}

void CTESTView::OnOK()
{
// 	if(manager.Game_State==0||manager.Game_State==1)
// 		return;
/*	manager.GameStart();*/

	if(m_pControl->m_pSocket==NULL)
		return;

	m_pControl->m_Ready[0]=true;

	if(m_pControl->m_Ready[0] && m_pControl->m_Ready[1])
	{
		manager.GameStart();
		PrintAll();
	}

	m_pControl->SendMsg("ok");

	PrintAll();

}

int CTESTView::SelectNum(int x, int y)
{
	x = (x-7)/70;
	y = (y-6)/70;

	return	y*10+x;
}

void CTESTView::DrawChoose(int x,int y,CDC *pdc)//绘制焦点的代码
{
	ChessAll.SelectObject(&m_choose);
	pdc->BitBlt(2+x*50,2+y*50,65,63,&ChessAll,0,0,MERGEPAINT);
	pdc->BitBlt(2+x*50,2+y*50,65,63,&ChessAll,65,0,SRCAND);
}

void CTESTView::DrawChess(Chess ch,CDC *pdc)
{
// 	pdc->BitBlt(2+manager.nChessinfo[k].x*65,2+manager.nChessinfo[k].y*65,65,65,
// 		&ChessAll,(manager.nChessinfo[k].type-1)*65,0,SRCCOPY);
// 	if(!ch.color)
// 	{
// 		ChessAll.SelectObject(m_mask);
// 		pdc->BitBlt(2+ch.x*65,2+ch.y*65,65,65,&ChessAll,(ch.type-1)*65,0,MERGEPAINT);
// 		ChessAll.SelectObject(m_chess);
// 		pdc->BitBlt(2+ch.x*6550,2+ch.y*65,65,65,&ChessAll,(7-ch.type-1)*65,0,SRCAND);
// 	}
// 	else
// 	{
// 		ChessAll.SelectObject(m_mask);
// 		pdc->BitBlt(2+ch.x*65,2+ch.y*65,65,65,&ChessAll,(ch.type-1)*65,65,MERGEPAINT);
// 		ChessAll.SelectObject(m_chess);
// 		pdc->BitBlt(2+ch.x*65,2+ch.y*65,65,65,&ChessAll,(ch.type-1)*65,65,SRCAND);
// 	}
}











