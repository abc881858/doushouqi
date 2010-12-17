// Managers.h: interface for the Managers class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANAGERS_H__5393E183_C873_4721_A3E7_DAEFD74F7BDF__INCLUDED_)
#define AFX_MANAGERS_H__5393E183_C873_4721_A3E7_DAEFD74F7BDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetControl.h"
#include "hess.h"


class CTESTView;

class Managers
{
public:
	void GameStart();
	bool DoMsg(int x,int y,int action);
	bool River(int x, int y);
	bool Jump(Chess ch, int x, int y);

	bool Right(Chess *PointCh, int x, int y);

	int Game_State;//��Ϸ״̬
	//-1����Ϸ�ȴ���,�ȴ���ʼ
	// 0����Ϸ�� Player1����
	// 1����Ϸ�� Player2����
	// 2��Player1ʤ��
	// 3��Player2ʤ��
	// 4��ƽ��

	Chess *LossCh;//ָ����һ�α��Ե�����,�����Ϸ�ſ�ʼ����ֵ��NULL
	Chess *PointCh;//���ѡ����,ֻ��ѡ��ĳ�����Ӳ����ƶ���

	Chess nChessinfo[16];//��¼16�����ӵ���Ϣ

	int map[7][9];//��¼�����ϵ���Ϣ
	//0��ʾλ����ʲôҲû��
	//1��ʾ���Ϸ���ҵ�����
	//2��ʾ���·���ҵ�����

	int PlayerAc;//��ǰ���Ե����

	bool isEat;

	friend class CNetControl;

	Managers();
	virtual ~Managers();

protected:
	void Updata();//�����������
	bool Moveto(Chess *PointCh, int x, int y);//�ж��Ƿ�������(��PointCh�ƶ���map[x][y]λ��)
	Chess * Search(int x, int y);//��������������
};

#endif // !defined(AFX_MANAGERS_H__5393E183_C873_4721_A3E7_DAEFD74F7BDF__INCLUDED_)
