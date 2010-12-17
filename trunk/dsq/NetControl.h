// NetControl.h: interface for the CNetControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETCONTROL_H__DC4C3D43_8E68_4D66_BFA1_34AE4338AFFD__INCLUDED_)
#define AFX_NETCONTROL_H__DC4C3D43_8E68_4D66_BFA1_34AE4338AFFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Net.h"

class CTESTView;

class CNetControl
{
public:
	CNetControl(CTESTView *p);

	void SendMsg(char const *pMsg);
	void OnSorc();
	void OnSet();
	void OnOpen();
	void FetchMsg(CNet *pRequest);
	CNet* ConnectServer();

//	CString m_PassWord;

	UINT m_Port;//端口
	LPCTSTR m_Server;//服务器名称

	CNet *m_pSocket;//请求连接
	CNet *m_pListening;//监听Socket

	CTESTView *m_pView;
	bool m_Ready[2];

	bool m_Isserver;

	CNetControl();
	virtual ~CNetControl();

};

#endif // !defined(AFX_NETCONTROL_H__DC4C3D43_8E68_4D66_BFA1_34AE4338AFFD__INCLUDED_)
