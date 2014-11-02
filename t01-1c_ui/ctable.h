#ifndef CTABLE_H
#define CTABLE_H

#include <QTableWidget>
#include <QStringList>
#include <QItemSelectionModel>
#include <vector>
#include <iostream>

#define NUMBER_FIELD \
	0
#define NUMBER_HEADER \
	"Number"
#define NUMBER_COLUMN_WIDTH \
	51
#define TODO_FIELD \
	1
#define TODO_HEADER \
	"To-Do"
#define TODO_COLUMN_WIDTH \
	222
#define CATEGORY_FIELD \
	2
#define CATEGORY_HEADER \
	"Category"
#define CATEGORY_COLUMN_WIDTH \
	120
#define START_TIME_FIELD \
	3
#define START_TIME_HEADER \
	"Start"
#define START_TIME_COLUMN_WIDTH \
	118
#define END_TIME_FIELD \
	4
#define END_TIME_HEADER \
	"Deadline/End"
#define END_TIME_COLUMN_WIDTH \
	118
#define COMPLETE_FIELD \
	5
#define COMPLETE_HEADER \
	"Complete?"
#define COMPLETE_COLUMN_WIDTH \
	63

using namespace std;

class CTable : public QTableWidget
{
    Q_OBJECT
public:
    CTable();
    CTable(QWidget *par);
	

private:
    void initialiseHighlight();
    void keyPressEvent(QKeyEvent *event);

public slots:
	void createTableData(vector<vector<string>> listData);
private slots:
    void selectRowSlot(const QModelIndex & selected, const QModelIndex & deselected);

};


#endif // CTABLE_H
