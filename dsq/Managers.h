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

	int Game_State;//游戏状态
	//-1、游戏等待中,等待开始
	// 0、游戏中 Player1走棋
	// 1、游戏中 Player2走棋
	// 2、Player1胜利
	// 3、Player2胜利
	// 4、平局

	Chess *LossCh;//指向上一次被吃掉的棋,如果游戏才开始它的值是NULL
	Chess *PointCh;//玩家选中棋,只有选中某个棋子才能移动它

	Chess nChessinfo[16];//记录16个棋子的信息

	int map[7][9];//记录棋盘上的信息
	//0表示位置上什么也没有
	//1表示有上方玩家的棋子
	//2表示有下方玩家的棋子

	int PlayerAc;//当前电脑的玩家

	bool isEat;

	friend class CNetControl;

	Managers();
	virtual ~Managers();

protected:
	void Updata();//处理吃子问题
	bool Moveto(Chess *PointCh, int x, int y);//判断是否能走棋(把PointCh移动到map[x][y]位置)
	Chess * Search(int x, int y);//根据坐标获得棋子
};

#endif // !defined(AFX_MANAGERS_H__5393E183_C873_4721_A3E7_DAEFD74F7BDF__INCLUDED_)
