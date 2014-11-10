//@author A0116410Y
#ifndef CLINEEDIT_H
#define CLINEEDIT_H

#include "ccompleter.h"
#include <QKeyEvent>
#include <QLineEdit>

using namespace std;

class CLineEdit: public QLineEdit
{
    Q_OBJECT
public:
    CLineEdit(QWidget *parent = 0);
    ~CLineEdit();

    void setCompleter(CCompleter *c);
    CCompleter *completer() const;

protected:
    void keyPressEvent(QKeyEvent *e);
	void moveToNextEntry();

private slots:
	void insertCompletion(const QString& completion);
    void sendToParser();
	void updateCompleter(QStringList suggestions);
	void updateLineText(string text);

signals:
	void toSetText(const QString & text);
	void emitFeedback(QString feedback, bool isEnterPressed);
	void sendText(string text);
	void emitSuggestionSelected(string selection, string lineText);

private:
    CCompleter *c;
};

#endif // CLINEEDIT_H
