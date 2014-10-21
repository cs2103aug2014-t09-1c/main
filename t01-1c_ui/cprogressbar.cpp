#include "cprogressbar.h"

CProgressBar::CProgressBar()
{
}

CProgressBar::CProgressBar(QWidget *par)
{
    setParent(par);
    setFormat("%v/%m");
    setRange(0,100);
    setValue(33);
}
