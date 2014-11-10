//@author A0116410Y
#include "ccombobox.h"
#include <QLineEdit>

CComboBox::CComboBox()
{

}

CComboBox::CComboBox(QGroupBox *par)
{
    setParent(par);
    setEditable(true);
    lineEdit()->setStyleSheet("QLineEdit {padding: 2px ; border-image: url(:/Button/Resources/BORDER_COMBO.png);}");
    lineEdit()->setFont(QFont("Segoe UI", 15));
    connect(this, SIGNAL(editTextChanged(QString)),this,SLOT(textChanged(QString)));
}

void CComboBox::textChanged(QString edit)
{
    showPopup();
    setEditable(true);
}
