#include "ccompleter.h"
#include <QAbstractItemView>

CCompleter::CCompleter()
{
}

CCompleter::CCompleter(const QStringList& words, QObject * parent) :
QCompleter(parent), m_list(words), m_model()
{
    setModel(&m_model);
    popup()->setFont(QFont("Segoe UI", 13));
}

void CCompleter::update(QStringList suggestions)
{
	QStringList filtered = suggestions;
    m_model.setStringList(filtered);
    complete();
}

QString CCompleter::word()
{
    return m_word;
}
