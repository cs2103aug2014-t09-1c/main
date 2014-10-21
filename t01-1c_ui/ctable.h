#ifndef CTABLE_H
#define CTABLE_H

#include <QTableWidget>
#include <QStringList>
#include <QItemSelectionModel>
#include <vector>
#include <iostream>

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
