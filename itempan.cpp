#include"itempan.h"

#define PATH "/home/maxfromperek/QtProjects/game/fonts/"
#define PATHWATER "/home/maxfromperek/QtProjects/game/fonts/water/"
#define PATHAGGS "/home/maxfromperek/QtProjects/game/fonts/aggs/"
#define PATHFIRE "/home/maxfromperek/QtProjects/game/fonts/fire/"

ItemPan::ItemPan(QRectF& rect)
{
    speedOfBoiling = 100;
    numOfBubles = 150;
    speedOfVapor = 150;
    tickOfMainTimer = 0;
    tickTimFireMedium = 0;
    tickTimFireHard = 0;
    tickAggB = 0;
    tickAggW = 0;

    m_rect = new QRectF();
    m_rect->setRect(0,0,rect.width(),rect.height());
    m_pixmap = new QPixmap(QString(PATH) + "pan.png");

    m_background = new QPixmap(QString(PATH) + "panVV.png");
    m_vater = new QPixmap(QString(PATH) + "vater.jpg");
    m_vapor = new QPixmap();
    m_cap = new QPixmap();
    m_aggB = new QPixmap(QString(PATHAGGS));
    m_aggW = new QPixmap(QString(PATHAGGS));
    m_fire = new QPixmap(QString(PATHFIRE));

    timBubles = new QTimer();
    timBubles->setInterval(speedOfBoiling);
    connect(timBubles, SIGNAL(timeout()), this, SLOT (s_timBubles()));

    timBublesStatic = new QTimer();
    timBublesStatic->setInterval(100);
    connect(timBublesStatic, SIGNAL(timeout()), this, SLOT (s_timBublesStatic()));

    timVapor = new QTimer();
    timVapor->setInterval(speedOfVapor);
    connect(timVapor, SIGNAL(timeout()), this, SLOT (s_timVapor()));

    timFireMedium = new QTimer();
    timFireMedium->setInterval(speedOfBoiling);
    connect(timFireMedium, SIGNAL(timeout()), this, SLOT (s_timFireMedium()));

    timFireHard = new QTimer();
    timFireHard->setInterval(speedOfBoiling);
    connect(timFireHard, SIGNAL(timeout()), this, SLOT (s_timFireHard()));

    timAggW = new QTimer();
    timAggW->setInterval(speedOfBoiling);
    connect(timAggW, SIGNAL(timeout()), this, SLOT (s_timAggW()));

    timAggB = new QTimer();
    timAggB->setInterval(speedOfBoiling);
    connect(timAggB, SIGNAL(timeout()), this, SLOT (s_timAggB()));

    mainTimer = new QTimer();
    mainTimer->setInterval(2000);
    connect(mainTimer, SIGNAL(timeout()), this, SLOT (s_timMain()));
    mainTimer->start();

    tickTimBubles = -1;
    tickTimVapor = -1;
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

    //отрисовка яиц
    painter->setBrush(m_aggB->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);
    painter->setBrush(m_aggW->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);

    //отрисовка воды
    painter->setBrush(QColor(175, 238, 238, 60));
    painter->drawEllipse(140,60,450,350);

    //отрисовка пузырей
    painter->setBrush(Qt::NoBrush);
    for(int i = 0; i < bubles.size(); i++)
    {
        int opacity = rand()%100 + 50;
        painter->setPen(QColor(255,255,255,opacity));
        painter->drawEllipse(bubles[i]);
    }

    for(int i = 0; i < bublesStatic.size(); i++)
    {
        painter->setPen(QColor(255,255,255,100));
        painter->drawEllipse(bublesStatic[i]);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_background->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);

    // painter->setOpacity(10);
    painter->setBrush(m_vapor->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);

    painter->setBrush(m_cap->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);

    painter->setBrush(m_fire->scaled(m_rect->width(),m_rect->height()));
    painter->drawRect(*m_rect);

    Q_UNUSED(option);
    Q_UNUSED(widget);

}

//обновляет по таймеру пузырьки и брызги воды
void ItemPan::s_timBubles()
{
    tickTimBubles++;
    if(tickTimBubles == 0)
    {
        m_background->load(QString(PATHWATER) + "panV1.png");
        update();
    }
    else if(tickTimBubles == 1)
    {
        m_background->load(QString(PATHWATER) + "panV2.png");
        update();
    }
    else
    {
        m_background->load(QString(PATHWATER) + "panV3.png");
        tickTimBubles = -1;
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

void ItemPan::s_timBublesStatic()
{
    int rand = qrand()%90;
    if(rand < bublesStatic.size())
        numberOfBubles.push_back(rand);

    for(int i=0; i < numberOfBubles.size(); i++)
        bublesStatic[numberOfBubles[i]].moveTo(bublesStatic[numberOfBubles[i]].x(), bublesStatic[numberOfBubles[i]].y() - 3);


    for(int i = 0; i < bublesStatic.size(); i++)
    {
        if(bublesStatic[i].y() < 200)
        {
            bublesStatic.remove(i);
            numberOfBubles.removeOne(i);
        }
    }

    generateStaticBubles();
    update();
}

void ItemPan::s_timVapor()
{
    tickTimVapor++;
    if(tickTimVapor == 0)
    {
        m_vapor->load(QString(PATH) + "vapor.png");
        update();
    }
    else if(tickTimVapor == 1)
    {
        m_vapor->load(QString(PATH) + "vapor1.png");
        update();
    }
    else
    {
        m_vapor->load(QString(PATH) + "vapor2.png");
        tickTimVapor = -1;
        update();
    }
}

void ItemPan::s_timFireMedium()
{
    tickTimFireMedium++;
    if(tickTimFireMedium == 0)
    {
        m_fire->load(QString(PATHFIRE) + "fireL1.png");
        update();
    }
    else if(tickTimFireMedium == 1)
    {
        m_fire->load(QString(PATHFIRE) + "fireL2.png");
        update();
    }
    else
    {
        m_fire->load(QString(PATHFIRE) + "fireL3.png");
        tickTimFireMedium = -1;
        update();
    }
}

void ItemPan::s_timFireHard()
{
    tickTimFireHard++;
    if(tickTimFireHard == 0)
    {
        m_fire->load(QString(PATHFIRE) + "fireM1.png");
        update();
    }
    else if(tickTimFireHard == 1)
    {
        m_fire->load(QString(PATHFIRE) + "fireM2.png");
        update();
    }
    else
    {
        m_fire->load(QString(PATHFIRE) + "fireM3.png");
        tickTimFireHard = -1;
        update();
    }
}

void ItemPan::s_timAggB()
{
    tickAggB++;
    if(tickAggB == 0)
    {
        m_aggB->load(QString(PATHAGGS) + "aggB1.png");
        update();
    }
    else if(tickAggB == 1)
    {
        m_aggB->load(QString(PATHAGGS) + "aggB2.png");
        update();
    }
    else
    {
        m_aggB->load(QString(PATHAGGS) + "aggB3.png");
        tickAggB = -1;
        update();
    }
}

void ItemPan::s_timAggW()
{
    tickAggW++;
    if(tickAggW == 0)
    {
        m_aggW->load(QString(PATHAGGS) + "aggW1.png");
        update();
    }
    else if(tickAggW == 1)
    {
        m_aggW->load(QString(PATHAGGS) + "aggW2.png");
        update();
    }
    else
    {
        m_aggW->load(QString(PATHAGGS) + "aggW3.png");
        tickAggW = -1;
        update();
    }
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
        int x = qrand()%420;
        int y = qrand()%260;
        int r = qrand()%10 + 4;

        QRectF rect(150+x,y+130,r,r);
        bubles.push_back(rect);
    }
}

void ItemPan::generateStaticBubles()
{
    while(bublesStatic.size() < 20)
    {
        int x = qrand()%420;
        int y = qrand()%260;
        int r = qrand()%5 + 4;

        QRectF rect(150+x,y+130,r,r);
        bublesStatic.push_back(rect);
    }
}

void ItemPan::setHardFire()
{
    timFireHard->start();
    timFireMedium->stop();
}

void ItemPan::setMediumFire()
{
    timFireMedium->start();
    timFireHard->stop();
}

void ItemPan::setLowFire()
{
    timFireHard->stop();
    timFireMedium->stop();
}

void ItemPan::setBubles()
{
    for(int i =0; i< bublesStatic.size(); i++)
        bubles.push_back(bublesStatic[i]);
    bublesStatic.clear();
    timBubles->start();
    timBublesStatic->stop();
}

void ItemPan::setStaticBubles()
{
    timBublesStatic->start();
}

void ItemPan::setAggB()
{
    m_aggB = new QPixmap(QString(PATHAGGS) + "aggB1.png");
    timAggB->start();
}

void ItemPan::setAggW()
{
    m_aggW = new QPixmap(QString(PATHAGGS) + "aggW1.png");
    timAggW->start();
}

void ItemPan::setVapor()
{
    timVapor->start();
}

void ItemPan::setCap()
{
     m_cap = new QPixmap(QString(PATH)+"cap.png");
     bubles.clear();
     timVapor->stop();
     timAggB->stop();
     timAggW->stop();
     m_vapor->load(QString(""));
     update();
}


