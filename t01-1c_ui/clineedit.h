#ifndef CLINEEDIT_H
#define CLINEEDIT_H

#include "ccompleter.h"
#include <QKeyEvent>
#include <QLineEdit>

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

private slots:
    void insertCompletion(const QModelIndex &completion);

private:
    CCompleter *c;
};

#endif // CLINEEDIT_H
