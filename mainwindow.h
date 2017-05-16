#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QVector>

#include <QMainWindow>
#include<QWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QMouseEvent>
#include<QLabel>
#include<QPair>
#include<QPushButton>
#include<QTimer>
#include<QTime>
#include<QThread>
#include<QMessageBox>
#include<QApplication>
#include<QTextEdit>

#include"myscene.h"
#include"myview.h"
#include"ItemSelectedArea.h"
#include"itembutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    bool isEnableToClickButton;

    MyView* view;

    MyScene* sceneKitchen;//главная сцена игры
    MyScene* sceneOven;//cцена с плитой
    MyScene* sceneStove;

    QGraphicsPixmapItem* fontOfKitchen;//фон кухни(обычный)
    QGraphicsPixmapItem* curtain;

    QVector<QPair<QRectF, QString> > vectorOfRectsF;
    QVector<ItemSelectedArea*> vectorOfSelectedAreas;//вектор с объектами сцены, при наведении на которые изменяется фон
    QVector<ItemButton*> vectorOfOvenButtons;//вектор с кнопками на плите
    QVector<int> sequenceOfNumbersButtons;//последовательность, в которой необходимо включать кнопки

    QLabel* l_selectedArea;

    QTextEdit* te_rules;

    QPushButton* b_startShineButtons;
    QPushButton* b_startGame;
    QPushButton* b_rules;
    QPushButton* b_quit;
    QPushButton* b_back;


    QTimer* tim_toggleButtonsRed;
    QTimer* tim_toggleButtonsGreen;
    QTimer* tim_setRedButtons;
    QTimer* tim_MoveCurtain;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fillVectorOfRectsF();
    void fillVectorOfSelectedAreasAddOnScene();
    void generateSceneOven();
    void generateMainScene();
    void generateSceneStove();
    void levelDone(QString str);

public slots:
    void s_setLabelTextOnHoverEnterEvent();
    void s_setLabelTextOnHoverLeaveEvent();
    void s_setNewScene();
    void s_checkSequenceOfClickedButton();

    void s_startTimerShineButtons();
    void s_toggleButtonsRed();
    void s_toggleButtonsGreen();
    void s_setRedButtons();
    void s_moveCurtain();
    void s_startMoveCurtain();
    void s_rules();
    void s_getBack();

    ////////////////////  ancillary funtions ////////////////////////
    void createRectangle(QPolygon& poly,const int x, const int y, const int w, const int h);
};

#endif // MAINWINDOW_H
