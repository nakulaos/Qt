#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include<QPushButton>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

public:
    Ui::StartWindow *ui;

protected:
	QPushButton* m_pushButton[3];

public slots:
	void showNewSelectPattern();
};

#endif // STARTWINDOW_H
