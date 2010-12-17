// NetControl.cpp: implementation of the CNetControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TEST.h"
#include "TESTDoc.h"
#include "TESTView.h"
#include "Managers.h"

#include "Server.h"
#include "Getin.h"
#include "Net.h"
#include "NetControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern Managers manager;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetControl::CNetControl()
{
	m_Ready[0]=false;
	m_Ready[1]=false;

	m_pSocket=NULL;
	m_Server="";
	m_Port=100;
	m_pListening=NULL;
}

CNetControl::~CNetControl()
{
	if(m_pSocket)
	{
		delete m_pSocket;
	}
	delete m_pListening;
}

CNetControl::CNetControl(CTESTView *p)
{
	m_Ready[0]=false;
	m_Ready[1]=false;
	m_pView=p;
	m_pSocket=NULL;
	m_Server="";
	m_Port=100;
	m_pListening=NULL;
}

void CNetControl::SendMsg(const char *pMsg)
{
	m_pSocket->Send(pMsg,strlen(pMsg));
}

void CNetControl::FetchMsg(CNet *pRequest)
{
	char Msg[10000],tempMsg[1000];
	int ByteCount;
	int End=0;
	CStringArray *temp=new CStringArray;
	strcpy(Msg,"");
	do
	{
		strcpy(tempMsg,"");
		ByteCount=pRequest->Receive(tempMsg,1000);
		if(ByteCount>1000||ByteCount<=0)
		{
			MessageBox(GetActiveWindow(),"����������Ϣ��������","������Ϣ",MB_OK);
			return ;
        }
		else
			if(ByteCount<1000&&ByteCount>0)
			{
				End=1;
			}
		tempMsg[ByteCount]=0;
		strcat(Msg,tempMsg);
	}
	while(End==0);

	CString pMsg=Msg;
///////////////////////////////// TODO /////////////////////////////////////

	if(!strncmp(Msg,"33",2))
	{
		int x=Msg[2]-48;
		int y=Msg[3]-48;

// 		CString str;
// 		str.Format("%d%d", x,y);
// 		AfxMessageBox(str);

		if(manager.map[x][y]==manager.Game_State+1)
		{
// 			CString str;
// 			str.Format("%d%d", x,y);
// 			AfxMessageBox(str);

			manager.PointCh=manager.Search(x,y);

			return;
		}
		else
		{
			manager.Moveto(manager.PointCh,x,y);
			manager.Updata();
			m_pView->PrintAll();
			return;
		}
	}

	if(!strncmp(Msg,"ok",2))
	{
		m_Ready[1]=true;
		if(m_Ready[1] && m_Ready[0])
		{
			manager.GameStart();
			m_pView->PrintAll();
		}
	}

}


void CNetControl::OnSorc()//����,��ʾѡ������or�ͻ���
{
	int k;
	
	k=MessageBox(GetActiveWindow(),"���Ƿ���������������/�ͻ��� Y/N��","��������",MB_OKCANCEL);
	if(k==1)
	{
		CServer ser1;
		ser1.DoModal();
		m_Port=atoi(ser1.m_Port);
		OnSet();
		m_Isserver=true;
		manager.PlayerAc=0;
	}
	else
	{
		CGetin dlg1;
		if(dlg1.DoModal()==IDOK)
		{
			CString *p=new(CString);
			*p=dlg1.m_IP;
			m_Server=*p;
			m_Port=atoi(dlg1.m_Port);
			OnOpen();
			m_Isserver=false;
		}
		manager.PlayerAc=1;
	}
}


void CNetControl::OnSet()//��Ϊ�������ö˿�
{
	m_pListening=new CNet(this);
	if(m_pListening->Create(m_Port))
	{
		if(!m_pListening->Listen())
		{
			MessageBox(GetActiveWindow(),"�˿����ô���!","������Ϣ",MB_OK);
		}
	}
}

void CNetControl::OnOpen()//��Ϊ�ͻ�������ip�Ͷ˿�
{
	if(m_pSocket)
	{
		MessageBox(GetActiveWindow(),"�Ѿ����ӵ�������,��ر���������һ��!","������Ϣ",MB_OK);
		return;
	}
	if(!(m_pSocket=ConnectServer()))
	{
		m_pSocket=NULL;
		return;
	}
}

CNet* CNetControl::ConnectServer()
{
	CNet *pSocket=new CNet(this);
	if(!(pSocket->Create()))
	{
		delete pSocket;
		MessageBox(GetActiveWindow(),"����Socketʧ��","������Ϣ",MB_OK);
        return NULL;
	}
	//���ӵ�������
	if(!pSocket->Connect(m_Server,m_Port))
	{
		delete pSocket;
		MessageBox(GetActiveWindow(),"�������ӵ�������ʧ��","������Ϣ",MB_OK);
        return NULL;
	}
	return pSocket;
}
