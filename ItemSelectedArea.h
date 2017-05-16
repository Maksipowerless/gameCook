#ifndef FONTOFKITCHEN_H
#define FONTOFKITCHEN_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include<QGraphicsTextItem>
#include<QToolTip>

class ItemSelectedArea:public QObject, public QGraphicsItem
{
    Q_OBJECT
    QRectF* m_rect;
    QPixmap* m_pixmap;
    QString m_name;
    bool m_isHover;
    bool m_isEnableHoverEvents;
protected:
    void advance(int step)Q_DECL_OVERRIDE;
public:
    ItemSelectedArea(QRectF& rect, QString& s);
    ~ItemSelectedArea();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void setPixmapLevelDone();
    inline void setDisableHoverEvents(){m_isEnableHoverEvents = false;m_isHover = false;}
    inline bool isHover(){return m_isHover;}
    inline QString getName(){return m_name;}
signals:
  void signalHoverEnterEvent(int);
  void signalHoverLeaveEvent(int);
  void signalPressEvent(int);
};

#endif // FONTOFKITCHEN_H
