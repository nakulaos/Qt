#include"eventcenter.h"
#include<QApplication>

int main(int argc,char* argv[])
{
	QApplication a(argc,argv);
	EventCenter e;
	e.startGame();
	return a.exec();
}