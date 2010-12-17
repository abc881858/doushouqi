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
	int type;//1.象 2.狮 3.虎 4.豹 5.狗 6.狼 7.猫 8.鼠 大于8表示棋子无效 (本游戏设定为9)
	bool color;//false 上面 0号玩家 ; true 下面 1号玩家
	int x,y;

	Chess();
	virtual ~Chess();

};

#endif // !defined(AFX_HESS_H__56426346_2EEF_4DDE_B2B4_C75329A01264__INCLUDED_)
