#if !defined(AFX_NET_H__A2FADB23_E41C_448A_9B85_DBD1072D1DAF__INCLUDED_)
#define AFX_NET_H__A2FADB23_E41C_448A_9B85_DBD1072D1DAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Net.h : header file
//


class CNetControl;
/////////////////////////////////////////////////////////////////////////////
// CNet command target

class CNet : public CSocket
{
// Attributes
public:

// Operations
public:
	CNet();
	virtual ~CNet();
	CNet(CNetControl *m_Ncc);

// Overrides
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	CNetControl *m_Nc;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNet)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CNet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NET_H__A2FADB23_E41C_448A_9B85_DBD1072D1DAF__INCLUDED_)
