#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H
#include"QWidget"
#include<QVector>
#include"abstractpiece.h"

class AbstractBoard:public QWidget
{
	Q_OBJECT
private:
	int m_col;
	int m_row;
	//QVector<QVector<bool>> ve(m_col,QVector<bool>(m_row));
public:
	explicit AbstractBoard(int col,int row,QWidget *parent=0):QWidget(parent){m_col=col,row=m_row;};
	~AbstractBoard(){};

	
	virtual int getCol(){return m_col;};
	virtual int getRow(){return m_row;};

};




#endif