#ifndef CHESSVOICE_H
#define CHESSVOICE_H

#include<QObject>
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
	QSoundEffect *m_win;
	QSoundEffect *m_select;
	QSoundEffect *m_move;
	QSoundEffect *m_eat;
	QSoundEffect *m_back;
	QSoundEffect *m_general;

};


#endif // CHESSVOICE_H
