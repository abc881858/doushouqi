// hess.h: interface for the Chess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HESS_H__56426346_2EEF_4DDE_B2B4_C75329A01264__INCLUDED_)
#define AFX_HESS_H__56426346_2EEF_4DDE_B2B4_C75329A01264__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Chess  
{
public:
	int type;//1.�� 2.ʨ 3.�� 4.�� 5.�� 6.�� 7.è 8.�� ����8��ʾ������Ч (����Ϸ�趨Ϊ9)
	bool color;//false ���� 0����� ; true ���� 1�����
	int x,y;

	Chess();
	virtual ~Chess();

};

#endif // !defined(AFX_HESS_H__56426346_2EEF_4DDE_B2B4_C75329A01264__INCLUDED_)
