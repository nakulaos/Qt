#ifndef CHESSPIECESFACTORY_H
#define CHESSPIECESFACTORY_H

#include"abstractfactory.h"

#define BLACK 0
#define RED 1

class RedChessFactory:public chessFactory
{
public:
	virtual AbstractChessPiece* createRook(int col,int row,ChessBoard& board)override
	{
		return new Rook(col,row,RED,board);
	}
	virtual AbstractChessPiece* createHorse(int col,int row,ChessBoard& board)override
	{
		return new Horse(col,row,RED,board);
	}
	virtual AbstractChessPiece* createElephant(int col,int row,ChessBoard& board)override
	{
		return new Elephant(col,row,RED,board);
	}
	virtual AbstractChessPiece* createAdviser(int col,int row,ChessBoard& board)override
	{
		return new Adviser(col,row,RED,board);
	}
	virtual AbstractChessPiece* createKing(int col,int row,ChessBoard& board)override
	{
		return new King(col,row,RED,board);
	}
	virtual AbstractChessPiece* createCannon(int col,int row,ChessBoard& board)override
	{	
		return new Cannon(col,row,RED,board);
	}
	virtual AbstractChessPiece* createPawn(int col,int row,ChessBoard& board)override
	{
		return new Pawn(col,row,RED,board);
	}
};

class BlackChessFactory:public chessFactory	
{
public:
	virtual AbstractChessPiece* createRook(int col,int row,ChessBoard& board)override
	{
		return new Rook(col,row,BLACK,board);
	}
	virtual AbstractChessPiece* createHorse(int col,int row,ChessBoard& board)override
	{
		return new Horse(col,row,BLACK,board);
	}
	virtual AbstractChessPiece* createElephant(int col,int row,ChessBoard& board)override
	{
		return new Elephant(col,row,BLACK,board);
	}
	virtual AbstractChessPiece* createAdviser(int col,int row,ChessBoard& board)override
	{
		return new Adviser(col,row,BLACK,board);
	}
	virtual AbstractChessPiece* createKing(int col,int row,ChessBoard& board)override
	{
		return new King(col,row,BLACK,board);
	}
	virtual AbstractChessPiece* createCannon(int col,int row,ChessBoard& board)override
	{	
		return new Cannon(col,row,BLACK,board);
	}
	virtual AbstractChessPiece* createPawn(int col,int row,ChessBoard& board)override
	{
		return new Pawn(col,row,BLACK,board);
	}
};



/*工厂方法模式
class RookFactory:AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& board) override
	{
		return new Rook(col,row,RED,board);
	}
	virtual bool createRedPiece(int col,int row,ChessBoard& board) override
	{
		return new Rook(col,row,BLACK,board);
	}
};

class HorseFactory:AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& board) override
	{
		return new Horse(col,row,RED,board);
	}
	virtual bool createRedPiece(int col,int row,ChessBoard& board) override
	{
		return new Horse(col,row,BLACK,board);
	}
};


class ElephantFactory:AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& board) override
	{
		return new Elephant(col,row,RED,board);
	}
	virtual bool createRedPiece(int col,int row,ChessBoard& board) override
	{
		return new Elephant(col,row,BLACK,board);
	}
};

class AdviserFactory:AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& board) override
	{
		return new Adviser(col,row,RED,board);
	}
	virtual bool createRedPiece(int col,int row,ChessBoard& board) override
	{
		return new Adviser(col,row,BLACK,board);
	}
};

class KingFactory:AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& board) override
	{
		return new King(col,row,RED,board);
	}
	virtual bool createRedPiece(int col,int row,ChessBoard& board) override
	{
		return new King(col,row,BLACK,board);
	}
};


class CannonFactory:AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& board) override
	{
		return new Cannon(col,row,RED,board);
	}
	virtual bool createRedPiece(int col,int row,ChessBoard& board) override
	{
		return new Cannon(col,row,BLACK,board);
	}
};

class PawnFactory:AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& board) override
	{
		return new Pawn(col,row,RED,board);
	}
	virtual bool createRedPiece(int col,int row,ChessBoard& board) override
	{
		return new Pawn(col,row,BLACK,board);
	}
};

*/


#endif