#include "ctable.h"
#include <QHeaderView>
#include <QTableView>
#include <QKeyEvent>

CTable::CTable()
{
}
CTable::CTable(QWidget *par)
{
    setParent(par);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    initialiseHighlight();
    verticalHeader()->setVisible(false);
    verticalHeader()->setDefaultSectionSize(20);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setColumnCount(6);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader()->setFont(QFont("Segoe UI", 8));
    setColumnWidth(0,  51);
    setColumnWidth(1,  222);
    setColumnWidth(2,  120);
    setColumnWidth(3,  118);
    setColumnWidth(4,  118);
    setColumnWidth(5,  63);
    QStringList header;
    header << "Number" << "To-Do" << "Category" << "Start" << "Deadline/End" << "Complete?";
    setHorizontalHeaderLabels(header);
}

void CTable::createTableData()
{
    vector<vector<string>> list;
    vector<string> list1 = {"eat haggis", "yuk", "1700", "1900", "no"};
    list.push_back(list1);
    clearContents();
	setRowCount(0);
    int listSize = list.size();
    for (int i = 0; i < listSize; ++i) {
        insertRow(i);
        QTableWidgetItem *num =
                        new QTableWidgetItem(QString::number(i + 1));
        setItem(i,0,num);
        for (int j = 0; j < 5; ++j) {
            QString stringGet = QString::fromStdString(list[i][j]);
            QTableWidgetItem *item =
                            new QTableWidgetItem(stringGet);
            setItem(i,j + 1, item);
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
