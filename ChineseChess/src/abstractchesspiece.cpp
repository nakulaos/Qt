#include"abstractchesspiece.h"
#include<QDebug>

AbstractChessPiece::AbstractChessPiece(const int col, const int row, int team, ChessBoard& chessboard)
	:AbstractPiece(col,row,team),mboard(chessboard)
{
	//black 0  red 1
	//memset(mboard,0,sizeof(mboard));
	//添加进基于阵容的动态数组
	if(team==0)
	{
		mboard.getBlackPieces().push_back(this);
	}
	else
	{
		mboard.getRedPieces().push_back(this);
	}

	//添加进基于坐标的固定数组
	mboard.getChess(col,row)=this;
	//qDebug()<<"初始化  team col row"<<mboard.getChess(row,col)->getTeam()<<"   "
	//<<mboard.getChess(row,col)->getCol()<<" "<<mboard.getChess(row,col)->getRow();
}

bool AbstractChessPiece::move(int toCol, int toRow)
{
	qDebug()<<"已经进入abstractChesspieces move 0";
	if(canMoveTo(toCol,toRow))
	{
		qDebug()<<"已经进入abstractChesspieces move 1";
		//原来位置的棋子设置为空
		mboard.getChess(this->getCol(),this->getRow())=nullptr;
		this->setCol(toCol);
		this->setRow(toRow);
		qDebug()<<"已经进入abstractChesspieces move 2";
		mboard.removeChess(this->getCol(),this->getRow());
		qDebug()<<"已经进入abstractChesspieces move 4";
		mboard.getChess(this->getCol(),this->getRow())=this;
		qDebug()<<"已经进入abstractChesspieces move 3";
		return true;
	}
	return false;
}
