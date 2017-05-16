#ifndef MYSCENE_H
#define MYSCENE_H

#include<QGraphicsSceneMouseEvent>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QMouseEvent>
#include<QPoint>

class MyScene :public QGraphicsScene{

public:
    MyScene();
    ~MyScene(){}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYSCENE_H
