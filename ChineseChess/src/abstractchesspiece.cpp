#include"abstractchesspiece.h"

AbstractChessPiece::AbstractChessPiece(const int col, const int row, int team, ChessBoard& chessboard)
	:AbstractPiece(col,row,team),mboard(chessboard)
{
	//black 0  red 1

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
	mboard.getChess(row,col);
}

bool AbstractChessPiece::move(int toCol, int toRow)
{
	if(canMoveTo(toCol,toRow))
	{
		//原来位置的棋子设置为空
		mboard.getChess(this->getCol(),this->getRow())=nullptr;
		this->setCol(toCol);
		this->setRow(toRow);
		mboard.removeChess(this->getCol(),this->getRow());
		mboard.getChess(this->getCol(),this->getRow())=this;
		return true;
	}
	return false;
}
