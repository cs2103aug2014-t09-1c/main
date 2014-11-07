#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ProgramController.h"

#define COMMAND_LIST \
	"Commands: home, all, add, edit, delete, complete, uncomplete, undo, redo, search, clip, slot"
#define ADD_LABEL_FORMAT \
	"add [<name>][<date (day/DDMMYY)>][<time (deadline: HHMM /timed: HHMM-HHMM>][<category>]"
#define EDIT_LABEL_FORMAT \
	"edit <number> [<name>][<date (day/DDMMYY)>][<time (deadline: HHMM /timed: HHMM-HHMM>][<category>]"
#define DELETE_LABEL_FORMAT \
	"delete <number> / delete <from> to <to>"
#define COMPLETE_LABEL_FORMAT \
	"complete <number> / complete <from> to <to>"
#define UNCOMPLETE_LABEL_FORMAT \
	"uncomplete <number> / uncomplete <from> to <to>"
#define SEARCH_LABEL_FORMAT \
	"search <keywords>"
#define CLIP_LABEL_FORMAT \
	"clip <number>"
#define SLOT_LABEL_FORMAT \
	"slot [<date (day/DDMMYY)>][<desired time: HHMM-HHMM>][<desired duration: HHMM>]"
#define EMPTY_TODAY_TODO \
	"Nothing to complete today."


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
	void determineCommandLabel(const QString& text);

signals:
	void sendTableData(vector<vector<string>> data);
	void sendToSuggestionBox(QStringList suggestions);
	void sendSuggestionContentsToCompleter(QStringList list);
	void sendToLineEditAutoComplete(string text);
	void sendMaxToProgressBar(int maximum);
	void sendValToProgressBar(int value);	
	void sendToConsoleOutput(const QString&);
	void setCommandLabel(const QString&);

};

#endif // MAINWINDOW_H
