#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QWidget>
#include<QPainter>
#include<QVector>

#include"abstractboard.h"
#include"abstractchesspiece.h"

class AbstractChessPiece;

class ChessBoard : public AbstractBoard
{
    Q_OBJECT
protected:
	//friend class AbstractChessPiece;
	AbstractChessPiece *board[10][9];
	QVector<AbstractChessPiece*> red,black;

public:
    explicit ChessBoard(int col=10,int row=9,QWidget *parent = nullptr);
	~ChessBoard();

	//virtual void paintEvent(QPaintEvent *event);


	//ChessBoard(QWidget *widget,int row,int col);

	const QVector<AbstractChessPiece*>&  getConstRedPieces() const;
	const QVector<AbstractChessPiece*>&  getConstBlackPieces() const;
	QVector<AbstractChessPiece*>&  getRedPieces() ;
	QVector<AbstractChessPiece*>&  getBlackPieces() ;


	AbstractChessPiece*& getChess(int col,int row);
	AbstractChessPiece* const& getChess(int col,int row)const;

	void removeChess(int col,int row);

	/*判断棋子对应点与另一点中间有几个棋子*/
	/*车炮辅助函数*/
	int getChessNumInSameLine(int FromCol,int FromRow,int toCol,int toRow)const;

	/*判断红黑方区域*/
	int WhoArea(int col,int row);
	/*判断是不是九宫格*/
	bool isNineArea(int col,int row);

	bool HongmenBanquet()const;

	
signals:

};

#endif // CHESSBOARD_H

