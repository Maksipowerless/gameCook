#include "itempan.h"
#include "mainwindow.h"

#define PATH "/home/maxfromperek/QtProjects/game/fonts/"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    lvlDone =0;
    steps =0;
    points = 8;
    isEnableToClickButton = true;
    qsrand (QDateTime::currentMSecsSinceEpoch());
    showFullScreen();
    view = new MyView(this);
    view->setGeometry(0,0,1366,768);
    view->showFullScreen();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setMouseTracking(true);
    generateMainScene();
    generateSceneOven();
    generateSceneStove();
    view->setScene(sceneKitchen);

    curtain = sceneKitchen->addPixmap(QPixmap(QString(PATH)+"curtain.jpg"));
    tim_MoveCurtain = new QTimer;
    tim_MoveCurtain->setInterval(3);
    connect(tim_MoveCurtain, SIGNAL(timeout()), this, SLOT (s_moveCurtain()));

    b_startGame = new QPushButton("ИГРАТЬ");
    b_startGame->setGeometry(550,157,200,100);
    sceneKitchen->addWidget(b_startGame);
    connect(b_startGame, SIGNAL(clicked()), this, SLOT(s_startMoveCurtain()));

    b_rules = new QPushButton("ПРАВИЛА ИГРЫ");
    b_rules->setGeometry(550,277,200,100);
    connect(b_rules, SIGNAL(clicked()), this, SLOT(s_rules()));

    b_quit = new QPushButton("ВЫХОД");
    b_quit->setGeometry(550,397,200,100);
    sceneKitchen->addWidget(b_quit);
    connect(b_quit, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    b_back = new QPushButton("НАЗАД");
    b_back->setGeometry(550,600,200,100);
    sceneKitchen->addWidget(b_back);
    connect(b_back, SIGNAL(clicked()), this, SLOT(s_getBack()));
    b_back->hide();

    te_rules = new QTextEdit;
    te_rules->setGeometry(500,160,300,400);
    te_rules->setText("Здравствуй, юный повар! Покажи как хорошо ты готовишь. Проходи мини игры. Для каждой написаны свои правила. Для того, чтобы выбрать мини-игру "
                      "кликай на предметы кухни. Удачи!!");
    sceneKitchen->addWidget(b_rules);
    sceneKitchen->addWidget(te_rules);
    te_rules->hide();
}

MainWindow::~MainWindow()
{

}

void MainWindow::fillVectorOfRectsF()
{
    //метод заполняет vectorOfRectsF прямоуголниками, которые используются как форма итемов ItemSelectedArea
    vectorOfRectsF << QPair<QRectF,QString>(QRectF(790,350,100,170),QString("Духовка"))
            << QPair<QRectF,QString>(QRectF(625,405,65,55),QString("Плита"))
            << QPair<QRectF,QString>(QRectF(250,420,170,50),QString("Кран"))
            << QPair<QRectF,QString>(QRectF(0,590,460,175),QString("Cтол"));
}

void MainWindow::fillVectorOfSelectedAreasAddOnScene()
{
    //метод заолняет vectorOfSelectedAreas и добалвяет их на сцену (сначала необходимо выполнить метод fillVectorOfRectsF)
    for(int i=0; i<vectorOfRectsF.size(); i++)
    {
        vectorOfSelectedAreas.push_back(new ItemSelectedArea(vectorOfRectsF[i].first,vectorOfRectsF[i].second));
        sceneKitchen->addItem(vectorOfSelectedAreas[i]);
    }
}

void MainWindow::generateMainScene()
{
    sceneKitchen = new MyScene;
    fontOfKitchen = sceneKitchen->addPixmap(QPixmap(QString(PATH)+"kitchenO.jpg"));

    fillVectorOfRectsF();
    fillVectorOfSelectedAreasAddOnScene();

    l_selectedArea = new QLabel;
    l_selectedArea->setGeometry(1100,300,80,20);
    l_selectedArea->setText(QString(""));
    l_selectedArea->hide();
    sceneKitchen->addWidget(l_selectedArea);


    for(int i=0; i< vectorOfSelectedAreas.size(); i++)
        connect(vectorOfSelectedAreas[i], SIGNAL(signalHoverEnterEvent(int)), this,
                SLOT(s_setLabelTextOnHoverEnterEvent()));

    for(int i=0; i< vectorOfSelectedAreas.size(); i++)
        connect(vectorOfSelectedAreas[i], SIGNAL(signalHoverLeaveEvent(int)), this,
                SLOT(s_setLabelTextOnHoverLeaveEvent()));

    for(int i=0; i< vectorOfSelectedAreas.size(); i++)
        connect(vectorOfSelectedAreas[i], SIGNAL(signalPressEvent(int)), this,
                SLOT(s_setNewScene()));
}

void MainWindow::generateSceneStove()
{
    sceneStove = new MyScene;
    QPixmap pixmapStove(QString(PATH)+"stove.jpg");
    sceneStove->addPixmap(pixmapStove);

    qreal x=300, y=300, h = 700, w = 500;
    QRectF r(x,y,h,w);
    pan = new ItemPan(r);
    sceneStove->addItem(pan);
    pan->moveBy(10,70);

    agg1 = new ItemButton(r,1);
    sceneStove->addItem(agg1);
    agg1->setEgg();
    agg1->moveBy(500,0);

    agg2 = new ItemButton(r,1);
    sceneStove->addItem(agg2);
    agg2->setEgg();
    agg2->moveBy(540,40);

    QRectF rect(460,250,380,327);
    sold = new ItemButton(rect,1);
    sceneStove->addItem(sold);
    sold->setSolonka();
    sold->moveBy(500,250);

    rect = QRectF(460,250,350,350);
    cap = new ItemButton(rect,1);
    sceneStove->addItem(cap);
    cap->setCap();
    cap->moveBy(400,500);

    tim_Stove = new QTimer();
    tim_Stove->setInterval(2000);
    connect(tim_Stove, SIGNAL(timeout()), this, SLOT (s_timStove()));

    b_startStove = new QPushButton("СТАРТ");
    b_startStove->setGeometry(1087,20,200,50);
    sceneStove->addWidget(b_startStove);
    connect(b_startStove, SIGNAL(clicked()), this, SLOT(s_clickStart()));

    b_stoveOn = new QPushButton("ВКЛ плиту");
    b_stoveOn->setGeometry(1087,260,200,50);
    sceneStove->addWidget(b_stoveOn);

    b_stoveOff = new QPushButton("ВЫКЛ плиту");
    b_stoveOff->setGeometry(1087,320,200,50);
    sceneStove->addWidget(b_stoveOff);

    b_fireMedium = new QPushButton("Средний огонь");
    b_fireMedium->setGeometry(1087,380,200,50);
    sceneStove->addWidget(b_fireMedium);

    b_fireHard = new QPushButton("Сильный огонь");
    b_fireHard->setGeometry(1087,440,200,50);
    sceneStove->addWidget(b_fireHard);
}

void MainWindow::generateSceneOven()
{
    sceneOven = new MyScene;
    QPixmap pixmapOven(QString(PATH)+"oven.jpg");
    sceneOven->addPixmap(pixmapOven);


    //создание кнопок на сцене
    qreal x=300, y=300, h = 100, w = 100;
    int count =0;
    for(int i=0; i<3; i++)
    {
        y = 280 + i*100;
        for(int j=0; j<3; j++)
        {
            x = 340 + j*100;
            QRectF r(x,y,h,w);
            ItemButton* butt = new ItemButton(r,count);
            sceneOven->addItem(butt);
            vectorOfOvenButtons.push_back(butt);
            vectorOfOvenButtons.last()->moveBy(x,y);
            count++;
        }
    }

    for(int i=0; i<vectorOfOvenButtons.size(); i++)
        connect(vectorOfOvenButtons[i], SIGNAL(signalPressEvent(int)), this,
                SLOT(s_checkSequenceOfClickedButton()));

    b_startShineButtons = new QPushButton("СТАРТ");
    b_startShineButtons->setGeometry(1087,20,200,50);
    connect(b_startShineButtons, SIGNAL(clicked()), this, SLOT(s_startTimerShineButtons()));
    sceneOven->addWidget(b_startShineButtons);

    tim_toggleButtonsGreen = new QTimer();
    tim_toggleButtonsGreen->setInterval(800);
    connect(tim_toggleButtonsGreen, SIGNAL(timeout()), this, SLOT (s_toggleButtonsGreen()));

    tim_toggleButtonsRed = new QTimer();
    tim_toggleButtonsRed->setInterval(500);
    connect(tim_toggleButtonsRed, SIGNAL(timeout()), this, SLOT (s_toggleButtonsRed()));

    tim_setRedButtons = new QTimer();
    tim_setRedButtons->setInterval(800);
    connect( tim_setRedButtons, SIGNAL(timeout()), this, SLOT (s_setRedButtons()));

}


void MainWindow::levelDone(QString str)
{
    QMessageBox msBox;
    msBox.setWindowTitle("Поздравляю");
    msBox.setText("ВЫ ПРОШЛИ УРОВЕНЬ!!!");
    msBox.exec();
    for(int i=0; i < vectorOfSelectedAreas.size(); i++)
    {
        if(vectorOfSelectedAreas[i]->getName() == str )
        {
            disconnect(vectorOfSelectedAreas[i], SIGNAL(signalHoverEnterEvent(int)), this,
                       SLOT(s_setLabelTextOnHoverEnterEvent()));

            disconnect(vectorOfSelectedAreas[i], SIGNAL(signalHoverLeaveEvent(int)), this,
                       SLOT(s_setLabelTextOnHoverLeaveEvent()));

            disconnect(vectorOfSelectedAreas[i], SIGNAL(signalPressEvent(int)), this,
                       SLOT(s_setNewScene()));

            vectorOfSelectedAreas[i]->setDisableHoverEvents();
            vectorOfSelectedAreas[i]->setPixmapLevelDone();
            break;
        }
    }
    view->setScene(sceneKitchen);
}

void MainWindow::gameDone()
{
    sceneKitchen->addPixmap(QPixmap(QString(PATH)+"curtain.jpg"));
    QFont f("Times",100);
    QString str("Ты прошел игру! \n");

    if(points > 5)
    {
        str+= QString("Ты большой молодец!");
    }
    else if(points > 2)
    {
         str+= QString("Ты неплохо справился!");
    }
    else
    {
        str+= QString("Ты можешь и лучше!");
    }

    QGraphicsTextItem* text = sceneKitchen->addText(str);
    text->moveBy(30,100);
    text->setFont(f);

    delete b_quit;
    delete b_startGame;
    delete b_rules;
    b_quit = new QPushButton("ВЫХОД");
    b_quit->setGeometry(550,500,200,100);
    sceneKitchen->addWidget(b_quit);
    connect(b_quit, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
}

///////////////////// slots ////////////////////////////

void MainWindow::s_setLabelTextOnHoverEnterEvent()
{
    //метод пробегает по всем итемам и устанавливает имя метки именем выделенного итема(итем из vectorOfSelectedAreas)
    QString str;
    for(int i=0; i<vectorOfSelectedAreas.size(); i++)
    {
        if(vectorOfSelectedAreas[i]->isHover())
        {
            str = vectorOfSelectedAreas[i]->getName();
            break;
        }
    }
    l_selectedArea->setText(str);
    l_selectedArea->move(view->getMousePosition().rx()+10, view->getMousePosition().ry()+10);
    l_selectedArea->show();
}

void MainWindow::s_setLabelTextOnHoverLeaveEvent()
{
    //метод скрывает метку при отведении фокуса на итем
    l_selectedArea->setText(QString(""));
    l_selectedArea->hide();
}

void MainWindow::s_setNewScene()
{
    //метод при нажатии на итем устанавливает соответствующую сцену
    QString str;
    for(int i=0; i<vectorOfSelectedAreas.size(); i++)
    {
        if(vectorOfSelectedAreas[i]->isHover())
        {
            str = vectorOfSelectedAreas[i]->getName();
        }
    }

    if(str == vectorOfRectsF[0].second)
    {
        view->setScene(sceneOven);

        delete te_commands;
        te_commands = new QTextEdit;
        te_commands->setGeometry(1050,100, 290, 130);
        te_commands->setText("В этой мини-игре тебе нужно запоминать очердность нажатия кнопок. После нажатия на кнопку СТАРТ 5 кнопок будут подсвечиваться. Нажимай их в такой же последовательности. Удачи!");
        te_commands->setReadOnly(true);
        sceneOven->addWidget(te_commands);
    }
    else if(str == vectorOfRectsF[1].second)
    {
        view->setScene(sceneStove);

        delete te_commands;
        te_commands = new QTextEdit;
        te_commands->setGeometry(1050,100, 290, 130);
        te_commands->setText("Cледуй инструкции, которая будет появляться в этом окошке. Для начала мини-игры нажми старт.");
        te_commands->setReadOnly(true);
        sceneStove->addWidget(te_commands);

    }
    else if(str == vectorOfRectsF[2].second)
    {

    }
    else if(str == vectorOfRectsF[3].second)
    {

    }

}

void MainWindow:: s_startTimerShineButtons()
{
    if(sequenceOfNumbersButtons.isEmpty())
    {
        b_startShineButtons->hide();
        sequenceOfNumbersButtons.clear();
        isEnableToClickButton = false;
        for(int i=0; i< vectorOfOvenButtons.size(); i++)
            vectorOfOvenButtons[i]->setNoClicked();

        tim_toggleButtonsGreen->start();
    }
}

void MainWindow::s_timStove()
{
    switch (steps) {
    case 1:
        te_commands->setText(te_commands->toPlainText() + QString("Поставь сильный огонь"));
        break;
    case 2:
        te_commands->setText(te_commands->toPlainText() + QString("Посоли воду"));
        break;
    case 3:
        te_commands->setText(te_commands->toPlainText() + QString("Закинь яйца"));
        break;
    case 5:
        te_commands->setText(te_commands->toPlainText() + QString("Закрой крышкой"));
        break;
    case 6:
        te_commands->setText(te_commands->toPlainText() + QString("Поставь средний огонь"));
        break;
    case 7:
        te_commands->setText(te_commands->toPlainText() + QString("Выключи плиту"));
        break;
    default:
        break;
    }

    tim_Stove->stop();
}

//добавляет в вектор номера кнопок(5), перекрашивает их в красный, запускает таймер для перекраски в зеленый
//после этого выключает таймеры
void MainWindow::s_toggleButtonsGreen()
{
    int num = 0;
    do{
        num = qrand()%9;
    }
    while(sequenceOfNumbersButtons.contains(num));

    tim_toggleButtonsRed->start();
    vectorOfOvenButtons[num]->setGreenButton();
    sequenceOfNumbersButtons.push_back(num);

    if(sequenceOfNumbersButtons.size() == 5)
        tim_toggleButtonsGreen->stop();

}

//перекрышивае кнопки обратно в красный
void MainWindow:: s_toggleButtonsRed()
{
    vectorOfOvenButtons[sequenceOfNumbersButtons.last()]->setRedButton();
    if(sequenceOfNumbersButtons.size() == 5)
        isEnableToClickButton = true;
    tim_toggleButtonsRed->stop();
}

//проверка на правильность ввода последовательности кнопок
void MainWindow::s_checkSequenceOfClickedButton()
{
    int number = 0;
    if(isEnableToClickButton && sequenceOfNumbersButtons.isEmpty() == false)
    {
        for(int i=0; i<vectorOfOvenButtons.size(); i++)
        {
            if(vectorOfOvenButtons[i]->isClicked())
            {
                number = vectorOfOvenButtons[i]->getNumber();
                break;
            }
        }

        int ckeckNumber = sequenceOfNumbersButtons.takeFirst();
        if(number == ckeckNumber)
        {
            vectorOfOvenButtons[number]->setSmileButton();
        }
        else
        {
            vectorOfOvenButtons[number]->setErrorButton();
            sequenceOfNumbersButtons.clear();
            tim_setRedButtons->start();

            isEnableToClickButton = false;
            QMessageBox msBox;
            msBox.setWindowTitle("УПС");
            msBox.setText("ПОПРОБУЙ ЕЩЕ РАЗ ...");
            msBox.exec();
            b_startShineButtons->show();
            points--;
            return;
        }


        if(sequenceOfNumbersButtons.isEmpty())
        {
            tim_setRedButtons->start();
            levelDone("Духовка");
            lvlDone++;
            if(lvlDone == 2)
                gameDone();
        }
    }
}

void MainWindow::s_setRedButtons()
{
    for(int i=0; i< vectorOfOvenButtons.size(); i++)
        vectorOfOvenButtons[i]->setRedButton();
    tim_setRedButtons->stop();
}

void MainWindow::s_clickStart()
{
    b_startStove->hide();
    te_commands->setText("Включи плиту");
    connect(b_stoveOn, SIGNAL(clicked()), this, SLOT(s_events()));

}

//проверет очередность событий
void MainWindow::s_events()
{
    if(steps == 0 && te_commands->toPlainText().contains("Включи плиту"))
    {    
        setGreenButton(b_stoveOn);
        steps++;
        disconnect(b_stoveOn, SIGNAL(clicked()), this, SLOT(s_events()));
        tim_Stove->start();
        te_commands->setText(te_commands->toPlainText() + QString(" (сделано)\n"));
        connect(b_fireHard, SIGNAL(clicked()), this, SLOT(s_events()));

        return;
    }

    if(steps == 1 && te_commands->toPlainText().contains("Поставь сильный огонь"))
    {
        setGreenButton(b_fireHard);
        steps++;
        disconnect(b_fireHard, SIGNAL(clicked()), this, SLOT(s_events()));
        tim_Stove->start();
        te_commands->setText(te_commands->toPlainText() + QString(" (сделано)\n"));
        pan->setHardFire();
        connect(sold, SIGNAL(signalPressEvent(int)), this, SLOT(s_events()));

        return;
    }

    if(steps == 2 && te_commands->toPlainText().contains("Посоли воду"))
    {
        steps++;
        delete sold;
        tim_Stove->start();
        te_commands->setText(te_commands->toPlainText() + QString(" (сделано)\n"));
        pan->setStaticBubles();
        connect(agg2, SIGNAL(signalPressEvent(int)), this, SLOT(s_events()));

        return;
    }

    if(steps == 3 && te_commands->toPlainText().contains("Закинь яйца"))
    {
        steps++;
        delete agg2;
        pan->setBubles();
        connect(agg1, SIGNAL(signalPressEvent(int)), this, SLOT(s_events()));
        pan->setAggW();
        return;
    }

    if(steps == 4 && te_commands->toPlainText().contains("Закинь яйца"))
    {
        steps++;
        tim_Stove->start();
        delete agg1;
        te_commands->setText(te_commands->toPlainText() + QString(" (сделано)\n"));
        pan->setVapor();
        pan->setAggB();
        connect(cap, SIGNAL(signalPressEvent(int)), this, SLOT(s_events()));
        return;
    }

    if(steps == 5 && te_commands->toPlainText().contains("Закрой крышкой"))
    {
        steps++;
        te_commands->setText(te_commands->toPlainText() + QString(" (сделано)\n"));
        pan->setCap();
        tim_Stove->start();
        connect(b_fireMedium, SIGNAL(clicked()), this, SLOT(s_events()));
        delete cap;
        return;
    }
    if(steps == 6 && te_commands->toPlainText().contains("Поставь средний огонь"))
    {
        setGreenButton(b_fireMedium);
        steps++;
        te_commands->setText(te_commands->toPlainText() + QString(" (сделано)\n"));
        tim_Stove->start();
        pan->setMediumFire();
        disconnect(b_fireMedium, SIGNAL(clicked()), this, SLOT(s_events()));
        connect(b_stoveOff, SIGNAL(clicked()), this, SLOT(s_events()));
        return;
    }
    if(steps == 7 && te_commands->toPlainText().contains("Выключи плиту"))
    {
        setGreenButton(b_stoveOff);
        te_commands->setText(te_commands->toPlainText() + QString(" (сделано)\n"));
        pan->setLowFire();
        levelDone("Плита");
        lvlDone++;
        if(lvlDone == 2)
            gameDone();
    }

}

void MainWindow::s_moveCurtain()
{
    curtain->moveBy(3,0);
    if(curtain->pos().rx() > 1000)
    {
        tim_MoveCurtain->stop();
        sceneKitchen->removeItem(curtain);
        delete curtain;
    }
}

void MainWindow::s_startMoveCurtain()
{
    b_startGame->hide();
    b_rules->hide();
    b_quit->hide();
    tim_MoveCurtain->start();
}

void MainWindow::s_rules()
{
    b_startGame->hide();
    b_quit->hide();
    b_back->show();
    te_rules->show();
}

void MainWindow::s_getBack()
{
    b_startGame->show();
    b_quit->show();
    b_back->hide();
    te_rules->hide();
}

////////////////////  ancillary funtions ////////////////////////

void MainWindow:: createRectangle(QPolygon& poly,const int x, const int y, const int w, const int h){
    //метод рисует прямоугольник poly с началоа в точке (x,y) с длиной w и высотой h
    poly << QPoint(x,y) << QPoint(x+w,y)<< QPoint(x+w,y+h)<< QPoint(x,y+h)<< QPoint(x,y);
}

void MainWindow::setGreenButton(QPushButton* btn)
{
    QPalette myPalette = btn->palette();
    myPalette.setColor( btn->backgroundRole(), QColor(0,250,0) );
    btn->setPalette(myPalette);
}
