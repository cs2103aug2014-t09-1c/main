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
	connect(this, SIGNAL(sendToLineEditAutoComplete(string)), ui->lineEdit, SLOT(updateLineText(string)));
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
	bool isForCompleter = false;
	QStringList suggestions;
	string inputText = text.toUtf8().constData();
	if (text.length() >= 5 && text.left(6).contains("search", Qt::CaseInsensitive)) {
		vector<string> suggestionBoxList = control.populateSuggestionBox(inputText);
		
		foreach(string str, suggestionBoxList) {
			if (!str.empty()) {
				QString string = QString::fromStdString(str);
				suggestions << string;
			}
		}
		isForCompleter = true;
	}
	emit sendSuggestionContentsToCompleter(suggestions);
	if (!isForCompleter) {
		string lineEdit = control.updateLineText(inputText);
		if (!lineEdit.empty()) {
			emit sendToLineEditAutoComplete(lineEdit);
		}
	}
}
