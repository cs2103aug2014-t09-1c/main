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
	void updateConsoleOutput();

protected:
	void keyPressEvent(QKeyEvent *e);

private slots:
	void sendInputToController(string text);
	void getSuggestionResponse(string selection, string lineText);
	void sendFeedbackToController(QString text, bool isEnterPressed);
	void getProgressBarValueAdd();

signals:
	void sendTableData(vector<vector<string>> data);
	void sendToSuggestionBox(QStringList suggestions);
	void sendSuggestionContentsToCompleter(QStringList list);
	void sendToLineEditAutoComplete(string text);
	void sendMaxToProgressBar(int maximum);
	void sendValToProgressBar(int value);	
	void sendToConsoleOutput(const QString&);

};

#endif // MAINWINDOW_H
