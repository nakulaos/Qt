#ifndef ABSTRACTCHESSPIECE_H
#define ABSTRACTCHESSPIECE_H

#include"abstractpiece.h"
#include"chessboard.h"

class ChessBoard;

class AbstractChessPiece:public AbstractPiece
{

protected:
	ChessBoard& mboard;
public:
	//black 0  red 1
	AbstractChessPiece(const int col,const int row,int team,ChessBoard& chessboard);
	
	//能不能移动去这个点
	virtual bool canMoveTo(int toCol,int toRow) const =0;

	//能不能过河
	virtual bool canCrossTheRiver()const =0;

	virtual bool move(int toCol,int toRow) override;
};




#endif