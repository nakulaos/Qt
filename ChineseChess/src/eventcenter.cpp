#include "eventcenter.h"
#include<QMessageBox>

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


	int state=this->getChessGame()->getWinner();
	

	if(state==-2)
	{
		return;
	}
	else if(state==0)
	{
		QMessageBox* mbox=new QMessageBox;
		mbox->setWindowTitle(tr("提示"));
		mbox->setText(tr("本局结束，黑方胜利!"));
		mbox->setFont(QFont("FangSong", 16, QFont::Bold));
		mbox->exec();
		emit getState(1);
	}
	else if(state==1)
	{
		QMessageBox* mbox=new QMessageBox;
		mbox->setWindowTitle(tr("提示"));
		mbox->setText(tr("本局结束，红方胜利!"));
		mbox->setFont(QFont("FangSong", 16, QFont::Bold));
        mbox->show();
		emit getState(1);

	}
	else if(state==-1)
	{
		QMessageBox* mbox=new QMessageBox;
		mbox->setWindowTitle(tr("提示"));
		mbox->setText(tr("本局结束，红方平局!"));
		mbox->setFont(QFont("FangSong", 16, QFont::Bold));
        mbox->show();

	}
}

void EventCenter::startGame()
{
	m_game = new ChessGame;
	m_w = new GameWindow(*this);
	m_w->show();
	connect(this,&EventCenter::getState,m_w,&GameWindow::close);


}

ChessGame* EventCenter::getChessGame()
{
	// TODO: 在此处插入 return 语句
	return m_game;
}



