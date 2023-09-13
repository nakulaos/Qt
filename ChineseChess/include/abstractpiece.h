#ifndef ABSTRACTPIECE_H
#define ABSTRACTPIECE_H

#include<QString>
#include"abstractboard.h"



class AbstractPiece
{
public:
	AbstractPiece(int col,int row,int team,QString name="")
		:mChineseName(name),mTeam(team)
	{
		mRow=row;
		mCol=col;
		mIsDead=false;
	}

	virtual bool move(int col,int row)=0;
	
	//AbstractPieces(AbstractBoard &board,int mRow,int mCol,int mId,int team) ;
	

	int getRow() const {return mRow;} ;
	//int getId() const {return mId;};
	bool isDead() const {return mIsDead;};
	int getTeam() const {return mTeam;};
	int getCol()const{return mCol;};
	QString getName(){return mChineseName;};

	void setDeaeState(bool deadState){mIsDead=!deadState;};
	void setChineseName(QString name){mChineseName=name;};
	void setRow(const int row){mRow=row;};
	void setCol(const int col){mCol=col;};

private:
	int mRow;
	int mCol;
	//int mId;
	bool mIsDead;
	const int mTeam;

	//AbstractBoard& board;

	QString mChineseName;
};
#endif