//@author A0116410Y
#include "cmenubar.h"
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>

CMenuBar::CMenuBar()
{
    moving = false;
}
CMenuBar::CMenuBar(QWidget *par)
{
    setParent(par);
    moving = false;
    setMouseTracking(false);
}

void CMenuBar::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);
    if((event->button() == Qt::LeftButton)) {
        moving = true;
        offset = event->pos();
    }
}

void CMenuBar::mouseMoveEvent(QMouseEvent *event)
{
    QLabel::mouseMoveEvent(event);
    if(moving)
        parentWidget()->parentWidget()->move(event->globalPos() - offset);
}

void CMenuBar::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    if(event->button() == Qt::LeftButton) {
        moving = false;
    }
}
