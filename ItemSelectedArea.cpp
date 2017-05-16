#include "ItemSelectedArea.h"
#define PATH "/home/maxfromperek/QtProjects/game/fonts/"

ItemSelectedArea::ItemSelectedArea(QRectF& rect, QString& s)
{
    m_name = s;
    m_isHover = false;
    m_isEnableHoverEvents = true;
    m_rect = new QRectF();
    m_rect->setRect(rect.x(),rect.y(),rect.width(),rect.height());
    m_pixmap = new QPixmap(QString(PATH)+"kitchen.jpg");
    setAcceptHoverEvents(true);
}

ItemSelectedArea::~ItemSelectedArea()
{
    delete m_rect;
    delete m_pixmap;
}

void ItemSelectedArea::advance(int step)
{

}

void ItemSelectedArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(*m_pixmap);

    painter->drawRect(*m_rect);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

QRectF ItemSelectedArea::boundingRect() const
{
    return *m_rect;
}

void ItemSelectedArea::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_isEnableHoverEvents)
    {
        //при наведении на итем метод меняет картинку
        delete m_pixmap;
        m_pixmap = new QPixmap(QString(PATH)+"kitchenHover.jpg");
        m_isHover = true;
        update();
        emit signalHoverEnterEvent(10);
    }
}

void ItemSelectedArea::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_isEnableHoverEvents)
    {
        //при удалении курсора за пределы итема метод меняет картинку
        delete m_pixmap;
        m_pixmap = new QPixmap(QString(PATH)+"kitchenO.jpg");
        m_isHover = false;
        update();
        emit signalHoverLeaveEvent(10);
    }
}

void ItemSelectedArea::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit signalPressEvent(10);
}

 void ItemSelectedArea::setPixmapLevelDone()
 {
     //при удалении курсора за пределы итема метод меняет картинку
     delete m_pixmap;
     m_pixmap = new QPixmap(QString(PATH)+"lvlDone.jpg");
     update();
 }

