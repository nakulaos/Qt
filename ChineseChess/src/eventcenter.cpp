#include "eventcenter.h"

EventCenter::EventCenter()
{
	
}
/*
void EventCenter::show()
{
	w.show();
}
*/

void EventCenter::moveChess(int fromCol, int fromRow, int toCol, int toRow)
{
	qDebug()<<"已进入evententer movechess";
	this->getChessGame()->move(fromCol,fromRow,toCol,toRow);
}

void EventCenter::startGame()
{
	m_game = new ChessGame;
	m_w = new GameWindow(*this);
	m_w->show();
	
}

ChessGame* EventCenter::getChessGame()
{
	// TODO: 在此处插入 return 语句
	return m_game;
}
