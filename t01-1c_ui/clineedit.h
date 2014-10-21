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

private slots:
    void insertCompletion(const QModelIndex &completion);
    void sendToParser();

signals:
	void sendText(string text);

private:
    CCompleter *c;
};

#endif // CLINEEDIT_H
