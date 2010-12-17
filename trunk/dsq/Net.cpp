// Net.cpp : implementation file
//

#include "stdafx.h"
#include "TEST.h"
#include "TESTDoc.h"
#include "TESTView.h"

#include "Net.h"
#include "NetControl.h"
#include "Managers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Managers manager;
/////////////////////////////////////////////////////////////////////////////
// CNet

CNet::CNet()
{
}

CNet::~CNet()
{
}

CNet::CNet(CNetControl *m_Ncc)
{
	m_Nc=m_Ncc;
}

void CNet::OnReceive(int nErrorCode)
{
	m_Nc->FetchMsg(this);
	CSocket::OnReceive(nErrorCode);
}

void CNet::OnAccept(int nErrorCode)
{
	CNet *pSocket=new CNet(m_Nc);
	if(m_Nc->m_pListening->Accept(*pSocket) && m_Nc->m_pSocket==NULL)
	{
		m_Nc->m_pSocket=pSocket;

// 		char st[100];
// 		sprintf(st, "00%c", manager.PlayerAc+100);
// 		m_Nc->SendMsg(st);
	}
	else
	{
		delete pSocket;
	}
	CSocket::OnAccept(nErrorCode);
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CNet, CSocket)
	//{{AFX_MSG_MAP(CNet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CNet member functions
