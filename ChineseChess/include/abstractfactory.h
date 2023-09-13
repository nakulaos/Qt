#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include"chessboard.h"
#include"chesspiece.h"



class chessFactory
{
public:
	virtual AbstractPiece* createRook(int col,int row,ChessBoard& board)=0;
	virtual AbstractPiece* createHorse(int col,int row,ChessBoard& board)=0;
	virtual AbstractPiece* createElephant(int col,int row,ChessBoard& board)=0;
	virtual AbstractPiece* createAdviser(int col,int row,ChessBoard& board)=0;
	virtual AbstractPiece* createKing(int col,int row,ChessBoard& board)=0;
	virtual AbstractPiece* createCannon(int col,int row,ChessBoard& board)=0;
	virtual AbstractPiece* createPawn(int col,int row,ChessBoard& board)=0;
};


/*工厂方法模式
class AbstractFactory
{
	virtual bool createBlackPiece(int col,int row,ChessBoard& ChessBoar)=0;
	virtual bool createRedPiece(int col,int row,ChessBoard& ChessBoard)=0;
};
*/



#endif
