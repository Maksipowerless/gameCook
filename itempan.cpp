#include"itempan.h"

#define PATH "/home/maxfromperek/QtProjects/game/fonts/"
#define PATHWATER "/home/maxfromperek/QtProjects/game/fonts/water/"

ItemPan::ItemPan(QRectF& rect)
{
    speedOfBoiling = 100;
    numOfBubles = 100;

    m_rect = new QRectF();
    m_rect->setRect(0,0,rect.width(),rect.height());
    m_pixmap = new QPixmap(QString(PATH) + "pan.png");

    m_background = new QPixmap(QString(PATH) + "panVV.png");
    m_vater = new QPixmap(QString(PATH) + "vater.jpg");

    tim = new QTimer();
    tim->setInterval(speedOfBoiling);
    connect(tim, SIGNAL(timeout()), this, SLOT (s_tim()));
    tim->start();

    tick = -1;
    generateBubles();
}

ItemPan::~ItemPan()
{
    delete m_rect;
    delete m_pixmap;
}

void ItemPan::advance(int step)
{

}

void ItemPan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_pixmap->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);

    //отрисовка воды
    painter->setBrush(QColor(175, 238, 238, 60));
    painter->drawEllipse(140,60,450,350);

    //отрисовка пузырей
    painter->setPen(QColor(255,255,255,100));
    painter->setBrush(Qt::NoBrush);
    for(int i = 0; i < bubles.size(); i++)
        painter->drawEllipse(bubles[i]);

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_background->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);

    Q_UNUSED(option);
    Q_UNUSED(widget);

     painter->setBrush(QColor(0,0,0));
     QRectF r1(150,130,6,6);
     painter->drawEllipse(r1);
     QRectF r2(570,130,6,6);
     painter->drawEllipse(r2);
     QRectF r3(170,410,6,6);
     painter->drawEllipse(r3);
     QRectF r4(520,410,6,6);
     painter->drawEllipse(r4);

}

void ItemPan::s_tim()
{
    tick++;
    if(tick == 0)
    {
        delete m_background;
        m_background = new QPixmap(QString(PATHWATER) + "panV1.png");
        update();
    }
    else if(tick == 1)
    {
        delete m_background;
        m_background = new QPixmap(QString(PATHWATER) + "panV2.png");
        update();
    }
    else
    {
        delete m_background;
        m_background = new QPixmap(QString(PATHWATER) + "panV3.png");
        tick = -1;
        update();
    }

    for(int i = 0; i < bubles.size(); i++)
    {
        int x = qrand()%20 + 1;
        int y = qrand()%20 + 1;
        int zx = qrand()%3 - 1;
        int zy = qrand()%3 - 1;

        bubles[i].moveTo(bubles[i].x() + zx*x, bubles[i].y() +  zy*y);
        if((bubles[i].x() < 200 || bubles[i].x() > 520 ) || (bubles[i].y() < 170 || bubles[i].y() > 370) )
            bubles.remove(i);
    }
    generateBubles();
}

QRectF ItemPan::boundingRect() const
{
    return *m_rect;
}

void ItemPan::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}

void ItemPan::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

}

void ItemPan::generateBubles()
{

    while(bubles.size() < numOfBubles)
    {
        int x = qrand()%320;
        int y = qrand()%200;
        int r = qrand()%5 + 4;

        QRectF rect(200+x,y+170,r,r);
        bubles.push_back(rect);
    }
}

