#ifndef EVENTCENTER_H
#define EVENTCENTER_H

#include"chessgame.h"
#include"chessboard.h"
#include"loginwindow.h"
#include"startwindow.h"
#include"chessvoice.h"
#include"gamewindow.h"
#include<QObject>
#include<QThread>

class EventCenter:public QThread
{
	Q_OBJECT
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

signals:
	void getState(int value);
};


#endif