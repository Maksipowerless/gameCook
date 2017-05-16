#ifndef MYVIEW_H
#define MYVIEW_H

#include<QGraphicsView>
#include<QMouseEvent>
#include<QGraphicsItem>

class MyView : public QGraphicsView {
    Q_OBJECT

    QPointF m_mousePosition;
public:
    MyView(QGraphicsScene* pScene, QWidget* pwgt = 0)
        : QGraphicsView(pScene, pwgt)
    {
        m_mousePosition = QPointF(0,0);
    }
    MyView(QWidget* pwgt = 0)
         : QGraphicsView(pwgt)
    {

    }

    inline QPointF getMousePosition(){return m_mousePosition;}

    void mouseMoveEvent(QMouseEvent* event){

         m_mousePosition = event->pos();
        QGraphicsView::mouseMoveEvent(event);
    }

    void mousePressEvent(QMouseEvent* event){
        QGraphicsView::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event){
        QGraphicsView::mouseReleaseEvent(event);
    }
};




#endif // MYVIEW_H
