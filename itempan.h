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
    QPixmap* m_vapor;
    QPixmap* m_cap;
    QPixmap* m_aggB;
    QPixmap* m_aggW;
    QPixmap* m_fire;

    QTimer* timBubles;
    QTimer* timBublesStatic;
    QTimer* timFireMedium;
    QTimer* timFireHard;
    QTimer* timAggB;
    QTimer* timAggW;


    QTimer* timVapor;
    QTimer* mainTimer;


    int tickTimBubles;
    int tickTimVapor;
    int tickTimFireMedium;
    int tickTimFireHard;
    int tickAggB;
    int tickAggW;

    int speedOfBoiling;
    int speedOfVapor;
    int numOfBubles;

    int tickOfMainTimer;

    QVector<QRectF> bubles;
    QVector<QRectF> bublesStatic;
    QVector<int> numberOfBubles;
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
    void generateStaticBubles();

    void setHardFire();
    void setMediumFire();
    void setLowFire();
    void setBubles();
    void setStaticBubles();
    void setAggB();
    void setAggW();
    void setVapor();
    void setCap();
public slots:
    void s_timBubles();
    void s_timBublesStatic();
    void s_timVapor();
    void s_timFireMedium();
    void s_timFireHard();
    void s_timAggB();
    void s_timAggW();
signals:
  void signalPressEvent(int);
};


#endif // ITEMPAN_H
