#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include<QMainWindow>
#include<QPaintEvent>
#include<QPainter>
#include<QPoint>
#include<QWidget>


class EventCenter;
class ChessGame;


//考虑观察者模式

class GameWindow:public QWidget
{
	Q_OBJECT
private:
	//ChessGame& m_game;
	


protected:
	EventCenter& m_eventcenter; 
	double m_ChessR;
	double m_Offset;
	double m_distance;

	bool m_alreadyFinishSelect;
	QVector<double> selectedLocation;

	int doubleTransform(double);

public:
	GameWindow(EventCenter& eventCenter);

	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	void drawChessPieces(QPainter& painter);
	
	void drawLastStep(QPainter& painter);


	void setChessR(double r);
	void setOffset(double offset);
	void setDistance(double distance);

	double getChessR()const;
	double getChessOffset()const;
	double getDistance()const;
	ChessGame* getChessGame()const;



signals:
	void finishMoveed(int fromCol,int fromRow,int toCol,int toRow);	
signals:
	void finishSeleted();



};

#endif