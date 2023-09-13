#include "chessboard.h"
#include"chesspiece.h"
#include"chesspiecesfactory.h"
#include<qalgorithms.h>

#define RED 1
#define BLACK 0

ChessBoard::ChessBoard(int col,int row,QWidget *parent)
	:AbstractBoard(col,row,parent)
{
	//建立两个工厂
	chessFactory *redFactory =new RedChessFactory;
	chessFactory *blackFactory=new BlackChessFactory;

	blackFactory->createKing(0,4,*this);
	blackFactory->createAdviser(0,3,*this);
	blackFactory->createAdviser(0,5,*this);
	blackFactory->createElephant(0,2,*this);
	blackFactory->createElephant(0,6,*this);
	blackFactory->createHorse(0,1,*this);
	blackFactory->createHorse(0,7,*this);
	blackFactory->createRook(0,0,*this);
	blackFactory->createRook(0,8,*this);
	blackFactory->createCannon(2,1,*this);
	blackFactory->createCannon(2,7,*this);
	blackFactory->createPawn(3,0,*this);
	blackFactory->createPawn(3,2,*this);
	blackFactory->createPawn(3,4,*this);
	blackFactory->createPawn(3,6,*this);
	blackFactory->createPawn(3,8,*this);

	redFactory->createKing(9,4,*this);
	redFactory->createAdviser(9,3,*this);
	redFactory->createAdviser(9,5,*this);
	redFactory->createElephant(9,2,*this);
	redFactory->createElephant(9,6,*this);
	redFactory->createHorse(9,1,*this);
	redFactory->createHorse(9,7,*this);
	redFactory->createRook(9,0,*this);
	redFactory->createRook(9,8,*this);
	redFactory->createCannon(7,1,*this);
	redFactory->createCannon(7,7,*this);
	redFactory->createPawn(6,0,*this);
	redFactory->createPawn(6,2,*this);
	redFactory->createPawn(6,4,*this);
	redFactory->createPawn(6,6,*this);
	redFactory->createPawn(6,8,*this);

	/*
	new King(0,4,BLACK,*this);
	new King(9,4,RED,*this);

	new Adviser(0,3,BLACK,*this);
	new Adviser(0,5,BLACK,*this);
	new Adviser(9,3,RED,*this);
	new Adviser(9,5,RED,*this);

	new Elephant(0,2,BLACK,*this);
	new Elephant(0,6,BLACK,*this);
	new Elephant(9,2,RED,*this);
	new Elephant(9,6,RED,*this);

	new Horse(0,1,BLACK,*this);
	new Horse(0,8,BLACK,*this);
	new Horse(9,1,RED,*this);
	new Horse(9,8,RED,*this);

	new Rook(0,0,BLACK,*this);
	new Rook(0,9,BLACK,*this);
	new Rook(9,0,RED,*this);
	new Rook(9,9,RED,*this);

	new Cannon(3,1,BLACK,*this);
	new Cannon(3,7,BLACK,*this);
	new Cannon(7,1,RED,*this);
	new Cannon(7,7,RED,*this);

	new Pawn(4,0,BLACK,*this);
	new Pawn(4,2,BLACK,*this);
	new Pawn(4,4,BLACK,*this);
	new Pawn(4,6,BLACK,*this);
	new Pawn(4,8,BLACK,*this);
	new Pawn(6,0,RED,*this);
	new Pawn(6,2,RED,*this);
	new Pawn(6,4,RED,*this);
	new Pawn(6,6,RED,*this);
	new Pawn(6,8,RED,*this);
	*/
}

ChessBoard::~ChessBoard()
{
	for(AbstractChessPiece *p :this->getRedPieces())
	{
		delete p;
	}

	for(AbstractChessPiece *p :this->getBlackPieces())
	{
		delete p;
	}
}

int ChessBoard::getChessNumInSameLine(int fromCol,int fromRow,int toCol, int toRow)const
{
	int chessSum=0;//计算棋子总数

	if(fromCol==toCol)
	{
		//判断谁是序号较小的那一行
			int minRow=(fromRow>=toRow)?toRow:fromRow;
			int maxRow=(fromRow>=toRow)?fromRow:toRow;
			

		/*判断中间是否有棋子*/
		for(int i=minRow+1;i<maxRow;i++)
		{
			if(this->getChess(fromCol,i))
			{
				chessSum++;
			}
		}
		return chessSum;
	}
	else if(fromRow==toRow)
	{
		int minCol=(fromCol>=toCol)?toCol:fromCol;
		int maxCol=(fromCol>=toCol)?fromCol:toCol;

		for(int i=minCol+1;i<maxCol;i++)
		{
			if(this->getChess(i,fromRow))
			{
				chessSum++;
			}
		}
		return chessSum;
	}
	else
	{
		/*根本不在同一条线上*/
		return -1;
	}
}

int ChessBoard::WhoArea(int col,int row)
{
	if(col<=4)
	{
		//黑0 红1
		return 0;
	}
	else
	{
		return 1;
	}
}

bool ChessBoard::isNineArea(int col,int row)
{
	if((col>=7||col<=2)&&row>=3&&row<=5)
	{
		return true;
	}
	return false;
}

bool ChessBoard::HongmenBanquet() const
{
	auto redKing = std::find_if(this->getConstRedPieces().begin(),
	this->getConstRedPieces().end(),
	[](AbstractChessPiece *p)
	{
		return dynamic_cast<King*>(p)!=nullptr;
	});

	auto blackKing = std::find_if(this->getConstBlackPieces().begin(),
	this->getConstBlackPieces().end(),
	[](AbstractChessPiece *p)
	{
		return dynamic_cast<King*>(p)!=nullptr;
	});

	if(redKing!=this->getConstRedPieces().end()
		&& blackKing!=this->getConstBlackPieces().end())
	{
		if(this->getChessNumInSameLine((*redKing)->getCol(),(*redKing)->getRow(),
		(*blackKing)->getCol(),(*blackKing)->getRow())==0)
		{
			return true;
		}
		return false;
	}
	return false;
}

const QVector<AbstractChessPiece *> &ChessBoard::getConstRedPieces() const
{
	// TODO: 在此处插入 return 语句
	return red;
}

const QVector<AbstractChessPiece *> &ChessBoard::getConstBlackPieces() const
{
	// TODO: 在此处插入 return 语句
	return black;
}

QVector<AbstractChessPiece *> &ChessBoard::getRedPieces()
{
	// TODO: 在此处插入 return 语句
	return red;
}

QVector<AbstractChessPiece *> &ChessBoard::getBlackPieces()
{
	// TODO: 在此处插入 return 语句
	return black;
}

AbstractChessPiece *&ChessBoard::getChess(int col, int row)
{
	// TODO: 在此处插入 return 语句
	return board[col][row];
}

AbstractChessPiece *const &ChessBoard::getChess(int col, int row) const
{
	// TODO: 在此处插入 return 语句
	return board[col][row];
}

void ChessBoard::removeChess(int col, int row)
{
	int team=this->getChess(col,row)->getTeam();
	if(team==0)
	{
		for(auto it=this->getBlackPieces().begin();
		it!=this->getBlackPieces().end();
		it++)
		{
			if((*it)->getCol()==col&&(*it)->getRow()==row)
			{
				this->getBlackPieces().erase(it);
				delete *it;
				break;

			}
		}
	}
	else if(team==1)
	{
		for(auto it=this->getRedPieces().begin();
		it!=this->getRedPieces().end();
		it++)
		{
			if((*it)->getCol()==col&&(*it)->getRow()==row)
			{
				this->getRedPieces().erase(it);
				delete *it;
				break;

			}
		}
		
	}
	this->getChess(col,row)=nullptr;

}
