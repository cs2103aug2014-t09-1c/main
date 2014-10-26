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
	connect(ui->lineEdit, SIGNAL(emitFeedback(QString)), this, SLOT(sendFeedbackToController(QString)));
	connect(ui->lineEdit, SIGNAL(emitSuggestionSelected(string, string)), this, SLOT(getSuggestionResponse(string, string)));
	connect(this, SIGNAL(sendSuggestionContentsToCompleter(QStringList)), ui->lineEdit, SLOT(updateCompleter(QStringList)));
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

void MainWindow::getSuggestionResponse(string selection, string lineText)
{
	control.executeSuggestionSelection(selection, lineText);
	updateTableData();
}

void MainWindow::sendFeedbackToController(QString text)
{
	string inputText = text.toUtf8().constData();
	vector<string> suggestionBoxList = control.populateSuggestionBox(inputText);
	QStringList suggestions;
	foreach(string str, suggestionBoxList) {
		if (!str.empty()) {
			QString string = QString::fromStdString(str);
			suggestions << string;
		}
	}
	emit sendSuggestionContentsToCompleter(suggestions);
}
