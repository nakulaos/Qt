#include "chessgame.h"


ChessGame::ChessGame():nextPlayer(Red)
{
}

const ChessBoard &ChessGame::getBoard() const
{
	// TODO: 在此处插入 return 语句
	return board;
}

bool ChessGame::move(int fromCol, int fromRow, int toCol, int toRow)
{
	if(board.getChess(fromCol,fromRow)
		&&board.getChess(fromCol,fromRow)->getTeam()==this->getNextPlayer())
	{
		if(board.getChess(fromCol,fromRow)->move(toCol,toRow))
		{
			if(this->getNextPlayer()==Red)
			{
				this->setNextPlayer(Black);
			}
			else
			{
				this->setNextPlayer(Red);
			}
			return true;
		}
		return false;
	}
	return false;
}


int ChessGame::getWinner() const
{
	/*将中*/
	if(board.HongmenBanquet())
	{
		return this->getNextPlayer();
	}

	/*红方帅被吃*/
	if(std::find_if(board.getConstRedPieces().begin(),
	board.getConstRedPieces().end(),
	[](AbstractChessPiece *p)
	{
		return dynamic_cast<King*>(p)!=nullptr;
	})
	==board.getConstRedPieces().end())
	{
		return Black;
	}

	if(std::find_if(board.getConstBlackPieces().begin(),
	board.getConstBlackPieces().end(),
	[](AbstractChessPiece *p)
	{
		return dynamic_cast<King*>(p)!=nullptr;
	})
	==board.getConstBlackPieces().end())
	{
		return Red;
	}
	//都没有棋子过河
	if(std::count_if(board.getConstRedPieces().begin(),
	board.getConstRedPieces().end(),
	[](AbstractChessPiece *p)
	{
		return p->canCrossTheRiver();
	})
	+
	std::count_if(board.getConstBlackPieces().begin(),
	board.getConstBlackPieces().end(),
	[](AbstractChessPiece *p)
	{
		return p->canCrossTheRiver();
	})
	==0
	)
	{
		return -1;
	}
	return -2;
}

int ChessGame::getNextPlayer() const
{
	return nextPlayer;
}

void ChessGame::setNextPlayer(int player)
{
	nextPlayer=player;
}
