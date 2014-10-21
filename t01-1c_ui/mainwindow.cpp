#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	control("example.txt")
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint );
    ui->setupUi(this);
	connect(ui->lineEdit, SIGNAL(sendText(string)), this, SLOT(sendInputToController(string)));
	connect(this, SIGNAL(sendTableData(vector<vector<string>>)), ui->tableWidget, SLOT(createTableData(vector<vector<string>>)));
	updateTableData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendInputToController(string text)
{
	control.executeEntry(text);
	updateTableData();
}

void MainWindow::updateTableData()
{
	vector<vector<string>> tableData = control.refreshTableDisplay();
	emit sendTableData(tableData);
}
