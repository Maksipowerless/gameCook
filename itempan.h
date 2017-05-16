#ifndef ITEMPAN_H
#define ITEMPAN_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include<QGraphicsTextItem>
#include<QTimer>

class ItemPan:public QObject, public QGraphicsItem
{
    Q_OBJECT
    QRectF* m_rect;
    QPixmap* m_pixmap;
    QPixmap* m_background;
    QPixmap* m_vater;

    QTimer* tim;

    int tick;
    int speedOfBoiling;
    int numOfBubles;

    QVector<QRectF> bubles;
protected:
    void advance(int step)Q_DECL_OVERRIDE;
public:
    ItemPan(QRectF& rect);
    ~ItemPan();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void generateBubles();
public slots:
    void s_tim();
signals:
  void signalPressEvent(int);
};


#endif // ITEMPAN_H
