//@author A0116410Y
#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H

#include <QComboBox>
#include <QGroupBox>

class CComboBox : public QComboBox
{
    Q_OBJECT
public:
    CComboBox();
    CComboBox(QGroupBox *par);
public slots:
    void textChanged(QString edit);

};

#endif // CCOMBOBOX_H
