#include "chessvoice.h"
#include<QUrl>
#include<QMediaPlayer>

ChessVoice::ChessVoice(QObject *parent):QObject(parent)
{
	m_win->setSource(QUrl(":/sound/WinSound.wav"));
	m_eat->setSource(QUrl(":/sound/eatChess.wav"));
	m_back->setSource(QUrl(":/sound/backChess.wav"));
	m_move->setSource(QUrl(":/sound/selectChess.wav"));
	m_general->setSource(QUrl(":/sound/generalSound.wav"));
	m_select->setSource(QUrl("selectChess.wav"));
}



void ChessVoice::voiceWin()
{
	if(m_win!=nullptr)
	{
		this->m_win->play();
	}
}

void ChessVoice::voiceSelect()
{
	if(m_select!=nullptr)
	{
		this->m_select->play();
	}
}

void ChessVoice::voiceEat()
{
	if(m_eat!=nullptr)
	{
		this->m_eat->play();
	}
}

void ChessVoice::voiceGeneral()
{
	if(m_back!=nullptr)
	{
		this->m_general->play();
	}
}

void ChessVoice::voiceBack()
{
	if(m_back!=nullptr)
	{
		this->m_back->play();
	}
}

void ChessVoice::voiceMove()
{
	if(m_move!=nullptr)
	{
		this->m_move->play();
	}
}