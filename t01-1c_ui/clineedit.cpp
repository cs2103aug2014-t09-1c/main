#include "clineedit.h"
#include <QAbstractItemView>


CLineEdit::CLineEdit(QWidget *parent)
: QLineEdit(parent), c(0)
{
    setFont(QFont("Segoe UI", 15));
    CCompleter * completer = new CCompleter(QStringList() << "eat food" << "eat steak", this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    setCompleter(completer);
    connect(this, SIGNAL(returnPressed()),this, SLOT(clear()));
}

CLineEdit::~CLineEdit()
{
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
    connect(completer, SIGNAL(activated(const QModelIndex &)), this, SLOT(insertCompletion(const QModelIndex &)));
}

CCompleter *CLineEdit::completer() const
{
    return c;
}

void CLineEdit::insertCompletion(const QModelIndex & completion)
{
    int number = completion.row();
    QString& s = QString::number(number);
    setText(s);
    selectAll();
}


void CLineEdit::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible()) {
    // The following keys are forwarded by the completer to the widget
        if (c->currentRow() > -1) {
            switch (e->key()) {
                case Qt::Key_Enter:
                case Qt::Key_Return:
                e->ignore();
            }
        }
        switch (e->key())
        {
            //case Qt::Key_Enter:
            //case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
            e->ignore();
            return; // Let the completer do default behavior
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

    c->update(text());
    c->popup()->setCurrentIndex(c->completionModel()->index(-1, 0));
}
