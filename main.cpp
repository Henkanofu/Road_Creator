#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QVector>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
//Сдвиг работает классно а фронт мув работает только по горезонтали или вертикали сделай так чтобы он работаел и под углом
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWindow window;
    window.show();

    Bout boatCalculator;

    QVector<coordPoint> boatPoints;
    QVector<coordPoint> newboatPoints;
    coordPoint point;

    coordPoint o0;//координаты расставлены в порядке по часовой начаная с самой верхней правой точки
    o0.x=10;
    o0.y=10;
    coordPoint o1;
    o1.x=10;
    o1.y=0;
    coordPoint o2;
    o2.x=0;
    o2.y=0;
    coordPoint o3;
    o3.x=0;
    o3.y=10;
    cof kb;
    float pogrez =0.1;
    float k0;
    float k1;
    float k2;
    float k3;
    float b0;
    float b1;
    float b2;
    float b3;
    float a0=0;
    float a2=0;
    startCorner currentCorner = rightbot;
    startDirection currentDirection = lefty;
    startDirection newDirection =currentDirection;
    bool err=false;
    boatPoints.append(o1);
    int size=boatPoints.size();

    kb=boatCalculator.cofsearch(o0,o1);//пойск Коэффициента для всех сторон
    if(kb.is_vertical==true)
    {
        a0=o0.x;
    }
    else {
        k0=kb.k;
        b0=kb.b;
    }
    kb=boatCalculator.cofsearch(o1,o2);
    k1=kb.k;
    b1=kb.b;
    kb=boatCalculator.cofsearch(o3,o2);
    if(kb.is_vertical==true)
    {
        a2=o2.x;
    }
    else {
        k2=kb.k;
        b2=kb.b;
    }
    kb=boatCalculator.cofsearch(o3,o0);
    k3=kb.k;
    b3=kb.b;

    while (err!=true) {
        currentDirection=newDirection;
        newboatPoints = boatCalculator.front_move(boatPoints,currentDirection,size,k0,k1,k2,k3,b0,b1,b2,b3,a0,a2,currentCorner);
        boatPoints = boatCalculator.shift_move(newboatPoints,size,currentDirection,currentCorner,size,k0,k1,k2,k3,b0,b1,b2,b3,a0,a2);
        switch (newDirection)//смена направления движения после сдвига
        {
            case lefty:
            if (currentCorner==rightbot)
            {
                newDirection=righty;
                currentCorner=leftbot;
            }
            else if(righttop) {
                newDirection=righty;
                currentCorner=lefttop;
            }
                break;
            case up:
            if (currentCorner==leftbot)
            {
                newDirection=down;
                currentCorner=lefttop;
            }
            else if(rightbot) {
                newDirection=down;
                currentCorner=righttop;
            }
                break;
            case righty:
            if (currentCorner==leftbot)
            {
                newDirection=lefty;
                currentCorner=rightbot;
            }
            else if(lefttop) {
                newDirection=lefty;
                currentCorner=righttop;
            }
                break;
            case down:
            if (currentCorner==lefttop)
            {
                newDirection=up;
                currentCorner=leftbot;
            }
            else if(righttop) {
                newDirection=up;
                currentCorner=rightbot;
            }
                break;
            default:
                qDebug() << "Не корректный ввод данных направления 1";
        }
        for(int i=boatPoints.size()-2;i<boatPoints.size();i++)
        {
            point=boatPoints[i];
            if (a0!=0){

                if((a0!=0 and point.x>a0+pogrez)or(a2!=0 and point.x<a2-pogrez) or (point.y>point.x*k3+b3) or(point.y<point.x*k1+b1))
                {
                err=true;
                break;
                }
            }
            else{
                if((point.y==point.x*k3+b3 or point.y<=point.x*k1+b1 or point.x<=(point.y-b0)/k0 or point.x==(point.y-b2)/k2)and point.x+point.y<=o0.x+o0.y)//проверка что катера не вышли за граници
                {
                    err=false;
                }
                else
                {
                err=true;
                break;
                }
            }
            if(point.x<0 or point.y<0){
                err=true;
            }

        }
    }
    boatPoints.remove(boatPoints.size()-1,1);

    qDebug() << "boatPoints:" << boatPoints;//вывод координат марщрута для катеров
    return app.exec();
}
