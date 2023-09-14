#include"chesspiece.h"
#include<QDebug>
Rook::Rook(int col,int row,int team,ChessBoard& chessBoard)
	:AbstractChessPiece(col,row,team,chessBoard)
{
	this->setChineseName("車");

}


bool Rook::canCrossTheRiver() const 
{
	return true;
}


bool Rook::canMoveTo(int toCol,int toRow) const
{
	/*目的地没有棋子，或者有对面棋子*/
	if(mboard.getChess(toCol,toRow) ==nullptr
		|| mboard.getChess(toCol,toRow)->getTeam()!=this->getTeam())
	{
		if(mboard.getChessNumInSameLine(this->getCol(),this->getRow(),toCol,toRow)==0)
		{
			return true;
		}
	}
	return false;

}


Horse::Horse(int col,int row,int team,ChessBoard& chessBoard)
	:AbstractChessPiece(col,row,team,chessBoard)
{
	this->setChineseName("馬");
}

bool Horse::canCrossTheRiver() const 
{
	return true;
}

bool Horse::canMoveTo(int toCol,int toRow) const
{
	/*col  y，row x*/
	/*定义马前行的落点*/
	/*第一个为y 第二个坐标为x*/
	static const int canJumpPoint[8][2]=
	{
		{2,1},{2,-1},
		{1,2},{1,-2},
		{-1,2},{-1,-2},
		{-2,1},{-2,-1},
	};

	/*马被绊脚的落点*/
	static const int horseObstacle[8][2]
	{
		{1,0},{1,0},
		{0,1},{0,-1},
		{0,1},{0,-1},
		{-1,0},{-1,0},
	};


	if(mboard.getChess(toCol,toRow)==nullptr
		|| mboard.getChess(toCol,toRow)->getTeam()!=this->getTeam())
	{
		/*判断落脚点是否正确，以及是否被绊脚*/
		for(int i=0;i<8;i++)
		{
			if((this->getCol()+canJumpPoint[i][0]==toCol)
			&&(this->getRow()+canJumpPoint[i][1]==toRow)
			&&(mboard.getChess(this->getCol()+horseObstacle[i][0],this->getRow()+horseObstacle[i][1])==nullptr)
			)
			{
				return true;
			}
		}

		return false;

	}

	else
	{
		return false;
	}
}

Cannon::Cannon(int col,int row,int team,ChessBoard& chessBoard)
	:AbstractChessPiece(col,row,team,chessBoard)
{
	this->setChineseName("炮");
}

bool Cannon::canCrossTheRiver()const
{
	return true;
}

bool Cannon::canMoveTo(int toCol,int toRow) const
{
	//炮的走法，直线移动，不吃子
	if(mboard.getChess(toCol,toRow)==nullptr)
	{
		qDebug()<<"已经进入cannon canmoveto 1";
		qDebug()<<"getchesssameline返回值"<<mboard.getChessNumInSameLine(this->getCol(),this->getRow(),toCol,toRow);
		if(mboard.getChessNumInSameLine(this->getCol(),this->getRow(),toCol,toRow)==0)
		{
			qDebug()<<"已经进入cannon canmoveto 2";
			return true;
		}
		else
		{
			qDebug()<<"已经进入cannon canmoveto 3";
			return false;
		}
	}
	/*目的地有棋子，且不是自己阵容的*/
	else if(mboard.getChess(toCol,toRow)!=nullptr&&mboard.getChess(toCol,toRow)->getTeam()!=this->getTeam())
	{
		/*中间只有一个棋子*/
		if(mboard.getChessNumInSameLine(this->getCol(),this->getRow(),toCol,toRow)==1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

Elephant::Elephant(int col,int row,int team,ChessBoard& chessBoard)
	:AbstractChessPiece(col,row,team,chessBoard)
{
	if(this->getTeam()==0)
	{
		this->setChineseName("象");
	}
	else if(this->getTeam()==1)
	{
		this->setChineseName("相");
	}
}

bool Elephant::canCrossTheRiver()const
{
	return false;
}

bool Elephant::canMoveTo(int toCol,int toRow)const
{
	static const int canJumpPoint[4][2]
	{
		{2,2},{2,-2},
		{-2,2},{-2,-2},
	};
	static const int elephantObstacle[4][2]
	{
		{1,1},{1,-1},
		{-1,1},{-1,-1},
	};

	if(mboard.getChess(toCol,toRow)==nullptr
		|| mboard.getChess(toCol,toRow)->getTeam()!=this->getTeam())
	{
		/*判断是否属于我方的区域*/
		if(mboard.WhoArea(toCol,toRow)==this->getTeam())
		{
			/*判断落脚点是否正确，以及是否被绊脚*/
			for(int i=0;i<4;i++)
			{

				if((this->getCol()+canJumpPoint[i][0]==toCol)
				&&(this->getRow()+canJumpPoint[i][1]==toRow)
				&&(mboard.getChess(this->getCol()+elephantObstacle[i][0],this->getRow()+elephantObstacle[i][1]))==nullptr
				)
				{
					return true;
				}

			}

		}
	}
	return false;
}


Adviser::Adviser(int col,int row,int team,ChessBoard& chessBoard)
	:AbstractChessPiece(col,row,team,chessBoard)
{
	this->setChineseName("士");
}

bool Adviser::canCrossTheRiver()const
{
	return false;
}

bool Adviser::canMoveTo(int toCol,int toRow)const
{
	static const int canJumpPoint[4][2]=
	{
		{1,1},{1,-1},
		{-1,1},{-1,-1}
	};


	if(mboard.getChess(toCol,toRow)==nullptr
		|| mboard.getChess(toCol,toRow)->getTeam()!=this->getTeam())
	{
		if(this->getTeam()==mboard.WhoArea(toCol,toRow)&&mboard.isNineArea(toCol,toRow)==true)
		{
			for(int i=0;i<4;i++)
			{

				if((this->getCol()+canJumpPoint[i][0]==toCol)
				&&(this->getRow()+canJumpPoint[i][1]==toRow))
				{
					return true;
				}

			}
		}
	}
	return false;
}

Pawn::Pawn(int col,int row,int team,ChessBoard& chessBoard)
	:AbstractChessPiece(col,row,team,chessBoard)
{
	if(this->getTeam()==0)
	{
		this->setChineseName("卒");
	}
	else if(this->getTeam()==1)
	{
		this->setChineseName("兵");
	}
}

bool Pawn::canCrossTheRiver()const
{
	return true;
}

bool Pawn::canMoveTo(int toCol,int toRow)const
{
	if(mboard.getChess(toCol,toRow)==nullptr
		|| mboard.getChess(toCol,toRow)->getTeam()!=this->getTeam())
	{
		int direction=(this->getTeam()==0)?1:-1;
		if(this->getTeam()==mboard.WhoArea(this->getCol(),this->getRow()))
		{
			/*没过河,只能往前走*/
			if(this->getCol()+direction==toCol
			&& this->getRow()==toRow)
			{
				return true;
			}
		}
		else
		{
			const int canJumpPoint[3][2]=
			{
				{direction,0},
				{0,1},
				{0,-1},
			};
			

			for(int i=0;i<3;i++)
			{
				if((this->getCol()+canJumpPoint[i][0]==toCol)
				&&(this->getRow()+canJumpPoint[i][1]==toRow))
				{
					return true;
				}
			}
		}

	}
	return false;
}

King::King(int col,int row,int team,ChessBoard& chessBoard)
	:AbstractChessPiece(col,row,team,chessBoard)
{
	if(this->getTeam()==0)
	{
		this->setChineseName("将");
	}
	else if(this->getTeam()==1)
	{
		this->setChineseName("帅");
	}
}

bool King::canCrossTheRiver()const
{
	return false;
}

bool King::canMoveTo(int toCol,int toRow)const
{
	static const int canJumpPoint[4][2]=
	{
		{0,1},{0,-1},
		{1,0},{-1,0}
	};



	if(mboard.getChess(toCol,toRow)==nullptr
		|| mboard.getChess(toCol,toRow)->getTeam()!=this->getTeam())
	{
		if(this->getTeam()==mboard.WhoArea(toCol,toRow)&&mboard.isNineArea(toCol,toRow)==true)
		{
			//在我方九宫格里
			for(int i=0;i<4;i++)
			{

				if((this->getCol()+canJumpPoint[i][0]==toCol)
				&&(this->getRow()+canJumpPoint[i][1]==toRow))
				{
					return true;
				}
				

			}
		}
	}
	return false;
}