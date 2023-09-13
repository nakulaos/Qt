#include "eventcenter.h"

EventCenter::EventCenter():w(*this)
{
	
}

void EventCenter::show()
{
	w.show();
}

void EventCenter::moveChess(int fromCol, int fromRow, int toCol, int toRow)
{
	this->getChessGame().move(fromCol,fromRow,toCol,toRow);
}

ChessGame &EventCenter::getChessGame()
{
	// TODO: 在此处插入 return 语句
	return game;
}
