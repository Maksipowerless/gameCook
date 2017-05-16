#include"itembutton.h"

#define PATH "/home/maxfromperek/QtProjects/game/fonts/"

ItemButton::ItemButton(QRectF& rect, int num)
{
    m_rect = new QRectF();
    m_rect->setRect(0,0,rect.width(),rect.height());
    m_pixmap = new QPixmap(QString(PATH)+"buttonR.png");
    m_number = num;
    m_isClicked = false;
}

ItemButton::~ItemButton()
{
    delete m_rect;
    delete m_pixmap;
}

void ItemButton::advance(int step)
{

}

void ItemButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_pixmap->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF ItemButton::boundingRect() const
{
    return *m_rect;
}

void ItemButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_isClicked = true;
    emit signalPressEvent(10);

}

void ItemButton::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_isClicked = false;
}

void ItemButton::setGreenButton()
{
    delete m_pixmap;
    m_pixmap = new QPixmap(QString(PATH)+"buttonG.png");
    update();
}

void ItemButton::setRedButton()
{
    delete m_pixmap;
    m_pixmap = new QPixmap(QString(PATH)+"buttonR.png");
    update();
}

void ItemButton::setSmileButton()
{
    delete m_pixmap;
    m_pixmap = new QPixmap(QString(PATH)+"buttonSmile.png");
    update();
}

void ItemButton::setErrorButton()
{
    delete m_pixmap;
    m_pixmap = new QPixmap(QString(PATH)+"buttonERR.png");
    update();
}
