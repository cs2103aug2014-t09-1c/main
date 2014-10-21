#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ProgramController.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	ProgramController control;
	void updateTableData();

private slots:
	void sendInputToController(string text);

signals:
	void sendTableData(vector<vector<string>> data);
};

#endif // MAINWINDOW_H
