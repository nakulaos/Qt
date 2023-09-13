#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include"abstractpiece.h"
#include"chessboard.h"

class Rook:public AbstractChessPiece
{
public:
	Rook(int col,int row,int team,ChessBoard& chessboard);

	virtual bool canCrossTheRiver()const override;
	virtual bool canMoveTo(int toCol,int toRow)const override;
	
};

class Horse:public AbstractChessPiece
{
public:
	Horse(int col,int row,int team,ChessBoard& chessboard);

	virtual bool canCrossTheRiver()const override;
	virtual bool canMoveTo(int toCol,int toRow)const override;
};

class Cannon:public AbstractChessPiece
{
public:
	Cannon(int col,int row,int team,ChessBoard& chessboard);

	virtual bool canCrossTheRiver()const override;
	virtual bool canMoveTo(int toCol,int toRow)const override;
};

class Elephant:public AbstractChessPiece
{
public:
	Elephant(int col,int row,int team,ChessBoard& chessboard);

	virtual bool canCrossTheRiver()const override;
	virtual bool canMoveTo(int toCol,int toRow)const override;
};

class Adviser:public AbstractChessPiece
{
public:
	Adviser(int col,int row,int team,ChessBoard& chessboard);

	virtual bool canCrossTheRiver()const override;
	virtual bool canMoveTo(int toCol,int toRow)const override;
};

class Pawn:public AbstractChessPiece
{
public:
	Pawn(int col,int row,int team,ChessBoard& chessboard);

	virtual bool canCrossTheRiver()const override;
	virtual bool canMoveTo(int toCol,int toRow)const override;

};

class King:public AbstractChessPiece
{
public:
	King(int col,int row,int team,ChessBoard& chessboard);

	virtual bool canCrossTheRiver()const override;
	virtual bool canMoveTo(int toCol,int toRow)const override;
};

#endif
