#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qscrollbar.h"

const QString initialise;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	control("example.txt")
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint );
    ui->setupUi(this);
	connect(ui->lineEdit, SIGNAL(sendText(string)), this, SLOT(sendInputToController(string)));
	connect(this, SIGNAL(sendTableData(vector<vector<string>>)), ui->tableWidget, SLOT(createTableData(vector<vector<string>>)));
	connect(ui->lineEdit, SIGNAL(emitFeedback(QString, bool)), this, SLOT(sendFeedbackToController(QString, bool)));
	connect(ui->lineEdit, SIGNAL(emitSuggestionSelected(string, string)), this, SLOT(getSuggestionResponse(string, string)));
	connect(this, SIGNAL(sendSuggestionContentsToCompleter(QStringList)), ui->lineEdit, SLOT(updateCompleter(QStringList)));
	connect(this, SIGNAL(sendToLineEditAutoComplete(string)), ui->lineEdit, SLOT(updateLineText(string)));
	connect(this, SIGNAL(sendMaxToProgressBar(int)), ui->progressBar, SLOT(setMaximum(int)));
	connect(this, SIGNAL(sendValToProgressBar(int)), ui->progressBar, SLOT(setValue(int)));
	connect(this, SIGNAL(sendToConsoleOutput(const QString&)), ui->consoleOutput, SLOT(setText(const QString&)));
	connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(determineCommandLabel(const QString&)));
	connect(this, SIGNAL(setCommandLabel(const QString&)), ui->commandLabel, SLOT(setText(const QString&)));
	updateTableData();
	updateConsoleOutput();
	determineCommandLabel(initialise);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendInputToController(string text)
{
	control.executeEntry(text);
	updateConsoleOutput();
	updateTableData();
}

void MainWindow::updateTableData()
{
	vector<vector<string>> tableData = control.refreshTableDisplay();
	emit sendTableData(tableData);
	getProgressBarValueAdd();
}

void MainWindow::getSuggestionResponse(string selection, string lineText)
{
	control.executeSuggestionSelection(selection, lineText);
	updateConsoleOutput();
	updateTableData();
}

void MainWindow::sendFeedbackToController(QString text, bool isEnterPressed)
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
		string lineEdit = control.updateLineText(inputText, isEnterPressed);
		if (!lineEdit.empty()) {
			emit sendToLineEditAutoComplete(lineEdit);
		}
	}
}

void MainWindow::getProgressBarValueAdd()
{
	pair<int, int> stats = control.getCompletedStatToday();
	if (stats.second > 0) {
		ui->progressBar->setFormat("%v/%m");
		emit sendMaxToProgressBar(stats.second);
		emit sendValToProgressBar(stats.first);
	}
	else {
		ui->progressBar->setFormat("Nothing to do today!");
		emit sendMaxToProgressBar(1);
		emit sendValToProgressBar(1);
	}
}

void MainWindow::updateConsoleOutput()
{
	string output = control.getConsoleString();
	const QString consoleOut = QString::fromStdString(output);
	emit sendToConsoleOutput(consoleOut);
	control.clearConsoleString();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	int currentPos = ui->tableWidget->verticalScrollBar()->value();
	switch (e->key())
	{
	case Qt::Key_Down:
			e->ignore();
			ui->tableWidget->verticalScrollBar()->setValue(currentPos + 1);
			return;
	case Qt::Key_Up:
			e->ignore();
			ui->tableWidget->verticalScrollBar()->setValue(currentPos - 1);
			return;
	}
}

void MainWindow::determineCommandLabel(const QString& text)
{
	QString command = text.split(" ").at(0);
	if (command == ADD_COMMAND) {
		const QString label = ADD_LABEL_FORMAT;
		emit setCommandLabel(label);
	}
	else if (command == EDIT_COMMAND) {
		const QString label = EDIT_LABEL_FORMAT;
		emit setCommandLabel(label);
	}
	else if (command == DELETE_COMMAND) {
		const QString label = DELETE_LABEL_FORMAT;
		emit setCommandLabel(label);
	}
	else if (command == COMPLETE_COMMAND) {
		const QString label = COMPLETE_LABEL_FORMAT;
			emit setCommandLabel(label);
	}
	else if (command == UNCOMPLETE_COMMAND) {
		const QString label = UNCOMPLETE_LABEL_FORMAT;
		emit setCommandLabel(label);
	}
	else if (command == SEARCH_COMMAND) {
			const QString label = SEARCH_LABEL_FORMAT;
			emit setCommandLabel(label);
	}
	else if (command == CLIP_COMMAND) {
		const QString label = CLIP_LABEL_FORMAT;
		emit setCommandLabel(label);
	}
	else if (command == SLOT_COMMAND) {
		const QString label = SLOT_LABEL_FORMAT;
		emit setCommandLabel(label);
	}
	else {
		const QString label = COMMAND_LIST;
		emit setCommandLabel(label);
	}
}
