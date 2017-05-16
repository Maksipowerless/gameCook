#include "itempan.h"
#include "mainwindow.h"

#define PATH "/home/maxfromperek/QtProjects/game/fonts/"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    te_rules->setText("Тебе необходимо приготовить блюдо по рецепту. На каждом этапе тебе будет предложена мини игра. Выигрывай их и зарабатывай очки. Посмотрим на что ты способен");
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
    ItemPan* pan = new ItemPan(r);
    sceneStove->addItem(pan);
    pan->moveBy(10,70);
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
    b_startShineButtons->setGeometry(415,600,150,50);
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
    }
    else if(str == vectorOfRectsF[1].second)
    {
        view->setScene(sceneStove);
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
        sequenceOfNumbersButtons.clear();
        isEnableToClickButton = false;
        for(int i=0; i< vectorOfOvenButtons.size(); i++)
           vectorOfOvenButtons[i]->setNoClicked();

        tim_toggleButtonsGreen->start();
    }
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
    if(isEnableToClickButton)
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
            return;
        }


        if(sequenceOfNumbersButtons.isEmpty())
        {
            tim_setRedButtons->start();
            levelDone("Духовка");
        }
    }
}

void MainWindow::s_setRedButtons()
{
    for(int i=0; i< vectorOfOvenButtons.size(); i++)
        vectorOfOvenButtons[i]->setRedButton();
    tim_setRedButtons->stop();
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
