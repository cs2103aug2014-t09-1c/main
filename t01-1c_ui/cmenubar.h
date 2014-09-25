#ifndef CMENUBAR_H
#define CMENUBAR_H

#include <QLabel>

class QPoint;
class QMouseEvent;
class QWidget;

class CMenuBar : public QLabel
{
public:
    CMenuBar();
    CMenuBar(QWidget *par);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint offset;
    bool moving;
};

#endif // CMENUBAR_H
