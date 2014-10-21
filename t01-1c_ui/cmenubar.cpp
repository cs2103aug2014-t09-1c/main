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
    //setMovable(false);
    //setFloatable(false);
    //setFixedHeight(20);
    //setContextMenuPolicy(Qt::CustomContextMenu);
    //setStyleSheet("background-color: blue;");

    //QLabel* title = new QLabel("TEST");
    //title->setStyleSheet("background-color: green;");
    //title->setAlignment(Qt::AlignHCenter);
    //addWidget(title);
}

void CMenuBar::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);
    if((event->button() == Qt::LeftButton) /*&& !actionAt(event->pos())*/) {
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
