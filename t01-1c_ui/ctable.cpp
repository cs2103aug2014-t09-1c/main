//@author A0116410Y
#include "ctable.h"
#include <QHeaderView>
#include <QTableView>
#include <QKeyEvent>
#include <vector>
#include <QPainter>

const QString& numHeader = NUMBER_HEADER;
const QString& toDoHeader = TODO_HEADER;
const QString& categoryHeader = CATEGORY_HEADER;
const QString& startHeader = START_TIME_HEADER;
const QString& endHeader = END_TIME_HEADER;
const QString& completeHeader = COMPLETE_HEADER;

CTable::CTable()
{
}
CTable::CTable(QWidget *par)
{
    setParent(par);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
	setTableFormat();
	setTableHeaders();
	setWordWrap(true);
}

void CTable::setTableFormat()
{
	initialiseHighlight();
	verticalHeader()->setVisible(false);
	verticalHeader()->setDefaultSectionSize(20);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setColumnCount(6);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	horizontalHeader()->setFont(QFont("Segoe UI", 8));
	setColumnWidth(NUMBER_FIELD, NUMBER_COLUMN_WIDTH);
	setColumnWidth(TODO_FIELD, TODO_COLUMN_WIDTH);
	setColumnWidth(CATEGORY_FIELD, CATEGORY_COLUMN_WIDTH);
	setColumnWidth(START_TIME_FIELD, START_TIME_COLUMN_WIDTH);
	setColumnWidth(END_TIME_FIELD, END_TIME_COLUMN_WIDTH);
	setColumnWidth(COMPLETE_FIELD, COMPLETE_COLUMN_WIDTH);
}

void CTable::setTableHeaders()
{
	QStringList header;
	header << numHeader << toDoHeader << categoryHeader << startHeader << endHeader << completeHeader;
	setHorizontalHeaderLabels(header);
}

void CTable::createTableData(vector<vector<string>> listData)
{
	vector<vector<string>> list = listData;
    clearContents();
	setRowCount(0);
    int listSize = list.size();
    for (int i = 0; i < listSize; ++i) {
        insertRow(i);
        QTableWidgetItem *num = new QTableWidgetItem(QString::number(i + 1));
		num->setFlags(num->flags() ^ Qt::ItemIsEditable);
		num->setTextAlignment(Qt::AlignCenter);
        setItem(i,NUMBER_FIELD,num);
        for (int j = 0; j < 5; ++j) {
            QString stringGet = QString::fromStdString(list[i][j]);
			stringGet = wrapLongString(stringGet);
            QTableWidgetItem *item = new QTableWidgetItem(stringGet);
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			if (j != 0) {
				item->setTextAlignment(Qt::AlignCenter);
			}
			if (j == 4) {
				if (stringGet == "Lapsed") {
					item->setBackground(QBrush(Qt::red, Qt::FDiagPattern));
				}
			}
            setItem(i,j + 1, item);
			verticalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
        }
    }
	show();
}

void CTable::initialiseHighlight()
{
    QItemSelectionModel *sm = selectionModel();
    connect (sm,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(selectRowSlot(QModelIndex,QModelIndex)));
}

void CTable::selectRowSlot(const QModelIndex & selected, const QModelIndex & deselected)
{
    QItemSelectionModel *sm = selectionModel();
    emit sm->select(selected,QItemSelectionModel::Columns);
}

void CTable::keyPressEvent(QKeyEvent *event)
{
    QTableWidget::keyPressEvent(event);
    switch (event->key()) {
        case Qt::Key_Tab:
        event->ignore();
    }
}

QString CTable::wrapLongString(QString string)
{
	const int CriticalPos = 25;
	const QString wrapper = "-\n";
	QString iterString = string;
	QString tempString = string;
	int count = 0;
	int endlineAddCorrection = 0;

	while (count < string.length()) {
		QString firstWord = iterString.split(" ").at(0);
		QString firstNewLine = iterString.split("\n").at(0);
		if (firstWord.length() > CriticalPos && firstNewLine.length() >= firstWord.length()) {
			count += CriticalPos;
			tempString.insert(count + endlineAddCorrection, wrapper);
			endlineAddCorrection += wrapper.length();
			iterString = iterString.remove(0, CriticalPos);
		}
		else {
			int nextWordPos = min(firstWord.length(), firstNewLine.length()) + 1;
			iterString = iterString.remove(0, nextWordPos);
			count += nextWordPos;
		}
	}
	return tempString;
}