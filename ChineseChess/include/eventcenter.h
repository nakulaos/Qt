#ifndef EVENTCENTER_H
#define EVENTCENTER_H

#include"chessgame.h"
#include"chessboard.h"
#include"loginwindow.h"
#include"startwindow.h"
#include"chessvoice.h"
#include"gamewindow.h"
#include<QObject>

class EventCenter:public QObject
{
protected:
	ChessGame* m_game;
	GameWindow* m_w;
	//ChessVoice m_voice;
	
	


public:
	EventCenter();
	void show();
	void moveChess(int fromCol,int fromRow,int toCol,int toRow);
	void startGame();


	ChessGame* getChessGame();


};


#endif