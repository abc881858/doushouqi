// Managers.cpp: implementation of the Managers class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TEST.h"
// #include "TESTView.h"
// #include "TESTDoc.h"
#include "NetControl.h"
#include "Managers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Managers::Managers()
{
	int i,j;

	for(i=0;i<16;i++)
	{
		nChessinfo[i].type=9;
	}

	for(i=0;i<7;i++)
	{
		for(j=0;j<9;j++)
		{
			map[i][j]=0;
		}
	}

	Game_State=-1;
	PointCh=NULL;
	LossCh=NULL;
	isEat = false;
	PlayerAc=-1;
}

Managers::~Managers()
{
	
}

void Managers::GameStart()
{
	int i,j;

	for(i=0;i<7;i++)
	{
		for(j=0;j<9;j++)
		{
			map[i][j]=0;
		}
	}

	for(i=0; i<8; i++)
	{
		nChessinfo[i].color=true;
	}

	for(i=8; i<16; i++)
	{
		nChessinfo[i].color=false;
	}

	map[0][6]=2;
	nChessinfo[0].type=1;//1.象
	nChessinfo[0].x=0;
	nChessinfo[0].y=6;

	map[2][6]=2;
	nChessinfo[1].type=6;//6.狼
	nChessinfo[1].x=2;
	nChessinfo[1].y=6;

	map[4][6]=2;
	nChessinfo[2].type=4;//4.豹
	nChessinfo[2].x=4;
	nChessinfo[2].y=6;

	map[6][6]=2;
	nChessinfo[3].type=8;//8.鼠
	nChessinfo[3].x=6;
	nChessinfo[3].y=6;


	map[1][7]=2;
	nChessinfo[4].type=7;//7.猫
	nChessinfo[4].x=1;
	nChessinfo[4].y=7;

	map[5][7]=2;
	nChessinfo[5].type=5;//5.狗
	nChessinfo[5].x=5;
	nChessinfo[5].y=7;

	map[0][8]=2;
	nChessinfo[6].type=3;//3.虎
	nChessinfo[6].x=0;
	nChessinfo[6].y=8;

	map[6][8]=2;
	nChessinfo[7].type=2;//2.狮
	nChessinfo[7].x=6;
	nChessinfo[7].y=8;

//////////////////////////////////////////////////////////////////////////
	map[6][2]=1;
	nChessinfo[8].type=1;//1.象(上方)
	nChessinfo[8].x=6;
	nChessinfo[8].y=2;
	
	map[4][2]=1;
	nChessinfo[9].type=6;//6.狼
	nChessinfo[9].x=4;
	nChessinfo[9].y=2;
	
	map[2][2]=1;
	nChessinfo[10].type=4;//4.豹
	nChessinfo[10].x=2;
	nChessinfo[10].y=2;
	
	map[0][2]=1;
	nChessinfo[11].type=8;//8.鼠
	nChessinfo[11].x=0;
	nChessinfo[11].y=2;
	
	
	map[5][1]=1;
	nChessinfo[12].type=7;//7.猫
	nChessinfo[12].x=5;
	nChessinfo[12].y=1;
	
	map[1][1]=1;
	nChessinfo[13].type=5;//5.狗
	nChessinfo[13].x=1;
	nChessinfo[13].y=1;
	
	map[6][0]=1;
	nChessinfo[14].type=3;//3.虎
	nChessinfo[14].x=6;
	nChessinfo[14].y=0;
	
	map[0][0]=1;
	nChessinfo[15].type=2;//2.狮
	nChessinfo[15].x=0;
	nChessinfo[15].y=0;

	
	PointCh=NULL;

	Game_State=0;
/*	isEat = false;*/
	LossCh=NULL;
}


bool Managers::DoMsg(int x, int y, int action)
{
	if (Game_State<0 || Game_State>1)
	{
		return false;
	}

	if (action==1 && Game_State==PlayerAc)
	{
		if(PointCh == NULL)
		{
			if(map[x][y]-1 == Game_State) //如果我动我的棋子
			{
				PointCh=Search(x,y);
				return true;
			}
			else
			{
				return false;
			}
		}
		else// (PointCh != NULL)
			if( (PointCh->color && Game_State==1) || (!PointCh->color && Game_State==0) )
			{//点的是我的棋子, 并且是我的回合
				if( PointCh->x == x && PointCh->y == y )
				{
					PointCh=NULL;
					return true;
				}
				else
					if( Moveto(PointCh,x,y) )
					{
						Updata();
						return true;
					}
					else
						if( map[x][y]-1 == Game_State )
						{
							PointCh=Search(x,y);
							return true;
						}
						else
						{
							PointCh=NULL;
							return false;
						}
			}
			else
			{
				PointCh=NULL;
				return false;
			}
	}
// 	else
// 		if(action==0 && Game_State==PlayerAc)
// 		{
// 			if(PointCh!=NULL)
// 			{
// // 				if(Moveto(PointCh,x,y,false))
// // 				{
// // 					return true;
// // 					//在(x,y)处高亮显示
// // 				}
// 			}
// 		}

	return false;
}

bool Managers::River(int x, int y)// (x, y) 不是河流的话返回 true
{
	if ( (x==1 || x==2 || x==4 || x==5) && (y==3 || y==4 || y==5) )
	{
		return false;
	}
	return true;
}

bool Managers::Jump(Chess ch, int x, int y)
{
	if (ch.x==x && (x==1 || x==2 || x==4 || x==5) )//竖跳
	{
		if ( ch.y==2 && y==6 )//从上往下
		{
			for (int i=1;i<4;i++)
			{
				if (map[x][y-i] != 0)
				{
					return false;
				}
			}
			return true;
		}
		if ( ch.y==6 && y==2 )//从下往上
		{
			for (int i=1;i<4;i++)
			{
				if (map[x][y+i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	}

	if (ch.y==y && (y==3 || y==4 || y==5) )//横跳
	{
		if ( ch.x==0 && x==3 )//从左往右跳
		{
			for (int i=1;i<3;i++)
			{
				if (map[x-i][y] != 0)
				{
					return false;
				}
			}
			return true;
		}
		if ( ch.x==3 && x==6 )//从左往右跳
		{
			for (int i=1;i<3;i++)
			{
				if (map[x-i][y] != 0)
				{
					return false;
				}
			}
			return true;
		}
		if ( ch.x==6 && x==3 )//从右往左跳
		{
			for (int i=1;i<3;i++)
			{
				if (map[x+i][y] != 0)
				{
					return false;
				}
			}
			return true;
		}
		if ( ch.x==3 && x==0 )//从右往左跳
		{
			for (int i=1;i<3;i++)
			{
				if (map[x+i][y] != 0)
				{
					return false;
				}
			}
			return true;
		}
	}

	return false;
}

bool Managers::Right(Chess *PointCh, int x, int y)
{
	LossCh=Search(x,y);

	if (PointCh==NULL)
		return false;

	if((map[x][y]==1 && !PointCh->color) || (map[x][y]==2 && PointCh->color))
	{
		//移动我方的棋子到我的棋子上, 不允许
		return false;
	}

	if (LossCh==NULL)
	{
		if( PointCh->type < 9 )
			return true;
		else
			return false;
	}
	else//判断能否吃子
	{
		if ( PointCh->type!=1 && PointCh->type <= LossCh->type )//不是大象
		{
			isEat = true;
			return true;
		}
		if ( PointCh->type==1 && LossCh->type < 8 )
		{
			isEat = true;
			return true;
		}
		if ( PointCh->type==8 && LossCh->type==1 )
		{//老鼠在河中不能吃陆上的大象
			if (River(PointCh->x,PointCh->y))
			{
				isEat = true;
				return true;
			}
		}
		return false;
	}
}

bool Managers::Moveto(Chess *PointCh, int x, int y)
{
	Chess &ch = *PointCh;

	if ( (ch.type < 9) && Right(PointCh, x, y) )
 	{
 		if(((abs(ch.x-x)==1 && ch.y==y) || (abs(ch.y-y)==1 && ch.x==x)) && River(x,y))
 		{
			map[ch.x][ch.y]=0;

			if(ch.color)
			{
				map[x][y]=2;
			}
			else
			{
				map[x][y]=1;
			}

			ch.x=x;
			ch.y=y;

			return true;
	    }
		else
			if ( ( (abs(ch.x-x)==1 && ch.y==y) || (abs(ch.y-y)==1 && ch.x==x) ) && ch.type==8 )
			{
				map[ch.x][ch.y]=0;
				if(ch.color)
					map[x][y]=2;
				else
					map[x][y]=1;
				ch.x=x;
				ch.y=y;
				
				return true;
			}
			else
				if ((ch.type==2 || ch.type==3) && Jump(ch,x,y))//还有老鼠在河中 不能跳
				{
					map[ch.x][ch.y]=0;
					if(ch.color)
						map[x][y]=2;
					else
						map[x][y]=1;
					ch.x=x;
					ch.y=y;

					return true;
				}
				else
				{
					return false;
				}
	}

	return false;
}

void Managers::Updata()//处理吃子问题
{

	if (map[3][0]==2)
	{
		Game_State=3;

		CString str;
		str.Format("play2 Win!");
		AfxMessageBox(str);

	}
	else
		if (map[3][8]==1)
		{
			Game_State=2;

			CString str;
			str.Format("play1 Win!");
			AfxMessageBox(str);
		}
		else
		{
			Game_State = ( Game_State + 1 ) % 2;
		}

	if(LossCh != NULL )
	{
		LossCh->type = 9;
	}

	PointCh=NULL;
}

Chess * Managers::Search(int x, int y)
{
	int i;
	for(i=0; i<16; i++)
	{
		if(nChessinfo[i].x==x && nChessinfo[i].y==y && nChessinfo[i].type<9)
		{
			return nChessinfo+i;
		}
	}

	return NULL;
}







