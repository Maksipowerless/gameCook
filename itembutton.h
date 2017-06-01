#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include<QGraphicsTextItem>

class ItemButton:public QObject, public QGraphicsItem
{
    Q_OBJECT
    QRectF* m_rect;
    QPixmap* m_pixmap;
    int m_number;
    bool m_isClicked;
protected:
    void advance(int step)Q_DECL_OVERRIDE;
public:
    ItemButton(QRectF& rect, int num);
    ~ItemButton();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    bool isClicked(){return m_isClicked;}
    void setNoClicked(){m_isClicked = false;}
    void setGreenButton();
    void setRedButton();
    void setErrorButton();
    void setSmileButton();
    void setEgg();
    void setSolonka();
    void setCap();
    int getNumber(){return m_number;}
signals:
  void signalPressEvent(int);
};

#endif // ITEMBUTTON_H
