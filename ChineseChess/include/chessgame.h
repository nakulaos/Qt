#ifndef CHESSGAME_H
#define CHESSGAME_H
#include"chesspiece.h"
#include"chessboard.h"
#include"chessvoice.h"


//enum class Result{win,failer,draw};

class ChessGame
{
private:
	ChessBoard board;
	int result;
	const int Red=1;
	const int Black=0;
	int nextPlayer;
public:
	ChessGame();

	bool move(int fromCol,int fromRow,int toCol,int toRow);
	const ChessBoard& getBoard()const;
	int getWinner()const;
	int getNextPlayer()const;


	void setNextPlayer(int player);

	enum class Result{win,failer,draw};
};


#endif