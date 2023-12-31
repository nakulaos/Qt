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
	ChessVoice* m_voice;
	StartWindow* m_startWindow;

	//ChessVoice m_voice;
	
	


public:
	EventCenter();
	void show();
	void init();
	void moveChess(int fromCol,int fromRow,int toCol,int toRow);
	void startGame();


	ChessGame* getChessGame();
	ChessVoice* getChessVoice();

signals:
	void getState(int value);
};


#endif