#ifndef CHESSVOICE_H
#define CHESSVOICE_H

#include<QObject>
#include<QMediaPlayer>
#include<QSoundEffect>


class ChessVoice:public QObject
{
	Q_OBJECT

public:
    explicit ChessVoice(QObject *parent=nullptr);
	//~ChessVoice();

	void voiceWin();
	void voiceSelect();
	void voiceEat();
	void voiceBack();
	void voiceGeneral();
	void voiceMove();
private:
	QMediaPlayer *m_win;
	QMediaPlayer *m_select;
	QMediaPlayer *m_move;
	QMediaPlayer *m_eat;
	QMediaPlayer *m_back;
	QMediaPlayer *m_general;

};


#endif // CHESSVOICE_H
