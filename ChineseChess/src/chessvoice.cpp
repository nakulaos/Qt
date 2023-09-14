#include "chessvoice.h"
#include<QUrl>
#include<QSoundEffect>

ChessVoice::ChessVoice(QObject *parent):QObject(parent)
{
	m_win = new QSoundEffect(this);
	m_eat = new QSoundEffect(this);
	m_back = new QSoundEffect(this);
	m_move = new QSoundEffect(this);
	m_select = new QSoundEffect(this);
	m_general = new QSoundEffect(this);

	m_win->setSource(QUrl::fromLocalFile(":/sound/WinSound.wav"));
	m_eat->setSource(QUrl::fromLocalFile(":/sound/eatChess.wav"));
	m_back->setSource(QUrl::fromLocalFile(":/sound/backChess.wav"));
	m_move->setSource(QUrl::fromLocalFile(":/sound/selectChess.wav"));
	m_general->setSource(QUrl::fromLocalFile(":/sound/generalSound.wav"));
	m_select->setSource(QUrl::fromLocalFile("selectChess.wav"));

	m_win->setVolume(0.5f);
	m_eat->setVolume(0.5f);
	m_back->setVolume(0.5f);
	m_move->setVolume(0.5f);
	m_select->setVolume(0.5f);
	m_general->setVolume(0.5f);

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