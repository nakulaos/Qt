#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
	
}

StartWindow::~StartWindow()
{
    delete ui;
}


void StartWindow::showNewSelectPattern()
{
	ui->label->hide();
	ui->pushButton_help->hide();
	ui->pushButton_loadingLastGame->hide();
	ui->pushButton_setting->hide();
	ui->pushButton_settingBackgroupPicture->hide();
	ui->pushButton_start->hide();
	ui->pushButton_voiceEffect->hide();
}