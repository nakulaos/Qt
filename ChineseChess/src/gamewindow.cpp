#include "gamewindow.h"
#include<qalgorithms.h>
#include<eventcenter.h>
#include<QDebug>

int GameWindow::doubleTransform(double num)
{
	if(num-int(num)>=0.5)
	{
		return int(num)+1;
	}
	else

	{
		return int(num);
	}
}

GameWindow::GameWindow(EventCenter &event) : m_eventcenter(event)
{
	this->setChessR(45.0);
	this->setDistance(90.0);
	this->setOffset(60.0);

	connect(this,&GameWindow::finishMoveed,&m_eventcenter,&EventCenter::moveChess);
}

void GameWindow::paintEvent(QPaintEvent *event)
{
	//定义绘制操作
	QPainter painter(this);
	//设置抗锯齿渲染
	painter.setRenderHint(QPainter::Antialiasing,true);
	//重新调整绘图大小
	this->resize(900,960);
	/*
	int side=qMin(this->width(),this->height());
	painter.scale(side/960.0,side/960.0);
	*/
	//绘制10条横线
	for(int i=0;i<=9;i++)
	{
		painter.drawLine(QPoint(this->getChessOffset(),this->getChessOffset()+i*this->getDistance()),
		QPoint(this->getChessOffset()+8*this->getDistance(),this->getChessOffset()+i*this->getDistance()));
	}
	//绘制9条竖线
	for(int i=0;i<=8;i++)
	{	//第0条和第八条都是连续的的，其他中间断掉的
		if(i==0 || i==8)
		{
			painter.drawLine(QPoint(this->getChessOffset()+i*this->getDistance(),this->getChessOffset()),
			QPoint(this->getChessOffset()+i*this->getDistance(),this->getChessOffset()+9*this->getDistance()));
		}
		else
		{
			painter.drawLine(QPoint(this->getChessOffset()+i*this->getDistance(),this->getChessOffset()),
			QPoint(this->getChessOffset()+i*this->getDistance(),this->getChessOffset()+4*this->getDistance()));
			painter.drawLine(QPoint(this->getChessOffset()+i*this->getDistance(),this->getDistance()*5+this->getChessOffset()),
			QPoint(this->getChessOffset()+i*this->getDistance(),this->getChessOffset()+9*this->getDistance()));
		}
	}

	//绘制四条斜线
	painter.drawLine(QPoint(this->getChessOffset()+3*this->getDistance(),this->getChessOffset()),
		QPoint(this->getChessOffset()+5*this->getDistance(),this->getChessOffset()+2*this->getDistance()));
	painter.drawLine(QPoint(this->getChessOffset()+3*this->getDistance(),this->getChessOffset()+2*this->getDistance()),
		QPoint(this->getChessOffset()+5*this->getDistance(),this->getChessOffset()));
	painter.drawLine(QPoint(this->getChessOffset()+3*this->getDistance(),this->getChessOffset()+7*this->getDistance()),
		QPoint(this->getChessOffset()+5*this->getDistance(),this->getChessOffset()+9*this->getDistance()));
	painter.drawLine(QPoint(this->getChessOffset()+3*this->getDistance(),this->getChessOffset()+9*this->getDistance()),
		QPoint(this->getChessOffset()+5*this->getDistance(),this->getChessOffset()+7*this->getDistance()));

	//绘制楚河汉界四个字
	QRect rect1(this->getChessOffset()+this->getDistance(),this->getChessOffset()+4*this->getDistance(),
		this->getDistance(),this->getDistance());
	QRect rect2(this->getChessOffset()+2*this->getDistance(),this->getChessOffset()+4*this->getDistance(),
		this->getDistance(),this->getDistance());
	QRect rect3(this->getChessOffset()+5*this->getDistance(),this->getChessOffset()+4*this->getDistance(),
		this->getDistance(),this->getDistance());
	QRect rect4(this->getChessOffset()+6*this->getDistance(),this->getChessOffset()+4*this->getDistance(),
		this->getDistance(),this->getDistance());

	painter.setFont(QFont("FangSong",this->getChessR()*5/6,800));
	painter.drawText(rect1,"楚",QTextOption(Qt::AlignCenter));
	painter.drawText(rect2,"河",QTextOption(Qt::AlignCenter));
	painter.drawText(rect3,"汉",QTextOption(Qt::AlignCenter));
	painter.drawText(rect4,"界",QTextOption(Qt::AlignCenter));

	drawChessPieces(painter);
}

void GameWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button()!=Qt::LeftButton)
	{
		return;
	}
	QPoint realPoint = event->pos();
	qDebug()<<"realPoint----"<<"yCol:"<<realPoint.y()<<"     xRow:"<<realPoint.x();
	int abstractRow=doubleTransform((realPoint.x()-this->getChessOffset())/this->getDistance());
	int abstractCol=doubleTransform((realPoint.y()-this->getChessOffset())/this->getDistance());

	this->selectedLocation.push_back(abstractCol);
	this->selectedLocation.push_back(abstractRow);

	if(this->selectedLocation.size()==4)
	{
		qDebug()<<"selectLocation----"<<"yCol xRow  "<<this->selectedLocation[0]<<this->selectedLocation[1]
			<<this->selectedLocation[2]<<this->selectedLocation[3];
		emit finishMoveed(this->selectedLocation[0],this->selectedLocation[1],
			this->selectedLocation[2],this->selectedLocation[3]);
		this->selectedLocation.clear();
		this->repaint();
	}
	else
	{
		emit finishSeleted();
        this->repaint();
	}
	
	
}

void GameWindow::drawChessPieces(QPainter &painter)
{
	const ChessBoard& board=this->m_eventcenter.getChessGame()->getBoard();
	//绘制黑方棋子
	for(auto it =board.getConstBlackPieces().begin();
		it!=board.getConstBlackPieces().end();it++)
	{
		int yCol = (*it)->getCol();
		int xRow = (*it)->getRow();
		//int team = (*it)->getTeam();
		QPoint temp(this->getChessOffset()+xRow*this->getDistance(),this->getChessOffset()+yCol*this->getDistance());
		QRect rect(temp.x()-this->getChessR(),temp.y()-this->getChessR(),this->getDistance(),this->getDistance());

		painter.setPen(QColor(0,0,0));
		painter.drawEllipse(temp,this->getChessR(),this->getChessR());
		painter.drawText(rect,(*it)->getName(),QTextOption(Qt::AlignCenter));
	}

	for(auto it =board.getConstRedPieces().begin();
		it!=board.getConstRedPieces().end();it++)
	{
		int yCol = (*it)->getCol();
		int xRow = (*it)->getRow();
		//int team = (*it)->getTeam();
		QPoint temp(this->getChessOffset()+xRow*this->getDistance(),this->getChessOffset()+yCol*this->getDistance());
		QRect rect(temp.x()-this->getChessR(),temp.y()-this->getChessR(),this->getDistance(),this->getDistance());

		painter.setPen(QColor(255,0,0));
		painter.drawEllipse(temp,this->getChessR(),this->getChessR());
		painter.drawText(rect,(*it)->getName(),QTextOption(Qt::AlignCenter));
	}
}

void GameWindow::setChessR(double r)
{
	m_ChessR=r;
}

void GameWindow::setOffset(double offset)
{
	m_Offset=offset;
}

void GameWindow::setDistance(double distance)
{
	m_distance=distance;
}

double GameWindow::getChessR() const
{
	return m_ChessR;
}

double GameWindow::getChessOffset() const
{
	return m_Offset;
}

double GameWindow::getDistance() const
{
	return m_distance;
}

ChessGame* GameWindow::getChessGame() const
{
	// TODO: 在此处插入 return 语句
	return this->m_eventcenter.getChessGame();
}
