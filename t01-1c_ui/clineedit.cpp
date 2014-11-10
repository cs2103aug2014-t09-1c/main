//@author A0116410Y
#include "clineedit.h"
#include <QAbstractItemView>
#include "ui_mainwindow.h"
#include "QLabel"

using namespace std;

CLineEdit::CLineEdit(QWidget *parent)
: QLineEdit(parent), c(0)
{
    setFont(QFont("Segoe UI", 15));
    CCompleter * completer = new CCompleter(QStringList(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    setCompleter(completer);
    connect(this, SIGNAL(returnPressed()),this, SLOT(sendToParser()));
	connect(this, SIGNAL(toSetText(const QString&)), this, SLOT(setText(const QString&)));
}

CLineEdit::~CLineEdit()
{
}

void CLineEdit::sendToParser()
{
	QString originalText = text();
	string inputText = originalText.toUtf8().constData();
	emit sendText(inputText);
	clear();
	emit emitFeedback(originalText, true);
}

void CLineEdit::setCompleter(CCompleter *completer)
{
    if (c){
        QObject::disconnect(c, 0, this, 0);
    }

        c = completer;

    if (!c){
        return;
    }

    c->setWidget(this);
	connect(completer, SIGNAL(activated(const QString&)), this, SLOT(insertCompletion(const QString&)));
}

CCompleter *CLineEdit::completer() const
{
    return c;
}

void CLineEdit::insertCompletion(const QString & completion)
{
	string choiceString = completion.toUtf8().constData();
	string inputText = text().toUtf8().constData();
	emit emitSuggestionSelected(choiceString, inputText);
    QString& s = QString("");
    setText(s);
    //selectAll();
}


void CLineEdit::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
		case Qt::Key_Semicolon:
			e->ignore();		
			moveToNextEntry();
			return;
	}
	if (c && c->popup()->isVisible() && c->popup()->currentIndex().row() >= 0) {
    // The following keys are forwarded by the completer to the widget
        switch (e->key())
        {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
			e->ignore();
			return;				// Let the completer do default behaviour
        }
    }
    bool isShortcut = (e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E;
    if (!isShortcut)
    QLineEdit::keyPressEvent(e); // Don't send the shortcut (CTRL-E) to the text edit.

    if (!c) {
        return;
    }

    bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!isShortcut && !ctrlOrShift && e->modifiers() != Qt::NoModifier) {
        c->popup()->hide();
        return;
    }

	emit emitFeedback(text(), false);
    c->popup()->setCurrentIndex(c->completionModel()->index(-1, 0));
}

void CLineEdit::updateCompleter(QStringList suggestions)
{
	c->update(suggestions);
}

void CLineEdit::updateLineText(string text)
{
	const QString string = QString::fromStdString(text);
	emit toSetText(string);
	moveToNextEntry();
}

void CLineEdit::moveToNextEntry()
{
	QString openingType = "[";
	QString closingType = "]";
	int nextEntryPos = text().indexOf(openingType, cursorPosition());
	if (nextEntryPos < 0) {
		nextEntryPos = text().indexOf(openingType, 0);
	}
	if (nextEntryPos >= 0) {
		setCursorPosition(nextEntryPos + 1);
		int entryLength = text().indexOf(closingType, cursorPosition()) - nextEntryPos;
		cursorForward(true, entryLength - 1);
	}
}
