//@author A0116410Y
#ifndef CCOMPLETER_H
#define CCOMPLETER_H

#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QCompleter>

class CCompleter : public QCompleter
{
    Q_OBJECT
public:
    CCompleter();
    CCompleter(const QStringList& words, QObject * parent);
    QString word();
	void update(QStringList suggestions);
private:
    QStringList m_list;
    QStringListModel m_model;
    QString m_word;

};

#endif // CCOMPLETER_H
