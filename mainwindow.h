#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextStream>
#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <iostream>
#include <QTextEdit>
#include <cmath>
#include <math.h>

enum startCorner {
    leftbot,
    lefttop,
    righttop,
    rightbot
};
enum startDirection{
    lefty,
    up,
    righty,
    down,
};

struct coordPoint {
    float x = 0;
    float y = 0;

    coordPoint(float x_val = 0, float y_val = 0) : x(x_val), y(y_val) {}

    friend QDebug operator<<(QDebug debug, const coordPoint& p) {
        QDebugStateSaver saver(debug);
        debug.nospace() << "(" << p.x << ", " << p.y << ")";
        return debug;
    }
};
struct cof {
    float k = 0;
    float b = 0;
    bool is_vertical = false;

    cof(float x_val = 0, float y_val = 0) : k(x_val), b(y_val) {}

    friend QDebug operator<<(QDebug debug, const cof& p) {
        QDebugStateSaver saver(debug);
        debug.nospace() << "(" << p.k << ", " << p.b << ")";
        return debug;
    }
};

class Bout
{
public:
    QVector<coordPoint>front_move(QVector<coordPoint> boatPoints,startDirection direction,int size,float k0, float k1, float k2, float k3, float b0, float b1, float b2, float b3, float a0, float a2,startCorner corner)//функция сдвигает все катера прямо на растояние равное мин дистанции от катеров до граници
    {
        if (boatPoints.isEmpty()) {
                    return boatPoints;
                }
        int current_size = boatPoints.size();
        coordPoint point;
        float median;
        switch (direction) {
        case lefty:
            for (int i=current_size-size;current_size>i;i++)
            {
                point=boatPoints[i];
            }
            if(a2!=0 or a0!=0){
                point.x=a2;
            }
            else{
                median = std::max(std::min((point.y - b3) / k3, (point.y - b2) / k2), std::min(std::max((point.y - b3) / k3, (point.y - b2) / k2), (point.y - b1) / k1));
                point.x=median;
            }
            boatPoints.append(point);
            break;
        case up:
            for (int i=current_size-size;current_size>i;i++)
            {
                point=boatPoints[i];
            }
            if(a2!=0 or a0!=0){
                median = point.x*k3+b3;
                point.y=median;
            }
            else{
                median = std::max(std::min(point.x*k3+b3, point.x*k0+b0), std::min(std::max(point.x*k3+b3, point.x*k0+b0), point.x*k2+b2));
                point.y=median;
            }
            boatPoints.append(point);
            break;
        case righty:
            for (int i=current_size-size;current_size>i;i++)
            {
                point=boatPoints[i];
            }
            if(a2!=0 or a0!=0){
                point.x=a0;
            }
            else{
                median = std::max(std::min((point.y - b3) / k3, (point.y - b0) / k0), std::min(std::max((point.y - b3) / k3, (point.y - b0) / k0), (point.y - b1) / k1));
                point.x=median;
            }
            boatPoints.append(point);
            break;
        case down:
            for (int i=current_size-size;current_size>i;i++)
            {
                point=boatPoints[i];
            }
            if(a2!=0 or a0!=0){
                median = point.x*k1+b1;
                point.y=median;
            }
            else{
                median = std::max(std::min(point.x*k1+b1, point.x*k0+b0), std::min(std::max(point.x*k1+b1, point.x*k0+b0), point.x*k2+b2));
                point.y=median;
            }
            boatPoints.append(point);
            break;
        default:
             qDebug() << "Не корректный ввод данных направления 2";
        }
        return boatPoints;
    }
    cof cofsearch(coordPoint o0,coordPoint o1)
    {
        float k;
        float b;
        cof cofkb;

        if(o0.x==o1.x)
        {
            cofkb.is_vertical=true;
        }
        else
        {
        k=((o0.y-o1.y)/(o0.x-o1.x));
        b=(o1.y-k*o1.x);
        cofkb.k=k;
        cofkb.b=b;
        };
        return cofkb;
    }
    QVector<coordPoint>shift_move(QVector<coordPoint> boatPoints,float shift,startDirection startDirection, startCorner corner,int size,float k0, float k1, float k2, float k3, float b0, float b1, float b2, float b3, float a0, float a2)//функция делает сдвиг всех катеров на растояние равное их количеству
    {
        int current_size = boatPoints.size();
        coordPoint point;
        for(int i=current_size-size;current_size>i;i++)//изменение координат
        {
             point=boatPoints[i];
            switch (corner)//1-направо 2-вверх 3-вниз 4-налево
            {
            case leftbot:
                if(startDirection==up)
                {
                     point.x+=shift;//смещение направо
                    if(a2!=0 or a0!=0){
                        point.y=point.x*k3+b3;
                    }
                    else{
                     point.y = std::max(std::min(point.x*k1+b1, point.x*k0+b0), std::min(std::max(point.x*k1+b1, point.x*k0+b0), point.x*k2+b2));
                    }
                    break;
                }
                if(startDirection==righty)
                {
                    point.y+=shift;//смещение вверх
                    if(a2!=0 or a0!=0){
                        point.x=a0;
                    }
                    else{
                        point.x = std::max(std::min((point.y - b3) / k3, (point.y - b1) / k1), std::min(std::max((point.y - b3) / k3, (point.y - b1) / k1), (point.y - b0) / k0));
                    }
                    break;
                }
            case lefttop:
                if(startDirection==down)
                {
                    point.x+=shift;//смещение направо
                    if(a2!=0 or a0!=0){
                        point.y=point.x*k1+b1;
                    }
                    else{
                        point.y = std::max(std::min(point.x*k1+b1, point.x*k0+b0), std::min(std::max(point.x*k1+b1, point.x*k0+b0), point.x*k3+b3));
                    }
                    break;
                }
                if(startDirection==righty)
                {
                    point.y-=shift;//смещение вниз
                    if(a2!=0 or a0!=0){
                        point.x=a0;
                    }
                    else{
                        point.x = std::max(std::min((point.y - b3) / k3, (point.y - b1) / k1), std::min(std::max((point.y - b3) / k3, (point.y - b1) / k1), (point.y - b0) / k0));
                    }
                    break;
                }
            case righttop:
                if(startDirection==lefty)
                {
                    point.y-=shift;//смещение вниз
                    if(a2!=0 or a0!=0){
                        point.x=a2;
                    }
                    else{
                        point.x = std::max(std::min((point.y - b3) / k3, (point.y - b1) / k1), std::min(std::max((point.y - b3) / k3, (point.y - b1) / k1), (point.y - b2) / k2));
                    }
                    break;
                }
                if(startDirection==down)
                {
                    point.x-=shift;//смещение на лево
                    if(a2!=0 or a0!=0){
                        point.y=point.x*k1+b1;
                    }
                    else{
                    point.x = std::max(std::min((point.y - b3) / k3, (point.y - b1) / k1), std::min(std::max((point.y - b3) / k3, (point.y - b1) / k1), (point.y - b2) / k2));
                    }
                    break;
                }
            case rightbot:
                if(startDirection==lefty)
                {
                    point.y+=shift;//смещение вверх
                    if(a2!=0 or a0!=0){
                        point.x=a2;
                    }
                    else{
                        point.x = std::max(std::min((point.y - b3) / k3, (point.y - b2) / k2), std::min(std::max((point.y - b3) / k3, (point.y - b2) / k2), (point.y - b0) / k0));
                    }
                    break;
                }
                if(startDirection==up)
                {
                    point.x-=shift;//смещение на лево
                    if(a2!=0 or a0!=0){
                        point.y=point.x*k3+b3;
                    }
                    else{
                        point.x = std::max(std::min((point.y - b3) / k3, (point.y - b1) / k1), std::min(std::max((point.y - b3) / k3, (point.y - b1) / k1), (point.y - b2) / k2));
                    }
                    break;
                }
            default:
                 qDebug() << "Не корректный ввод данных направления 3";
            }
            boatPoints.append(point);
        }
        return boatPoints;
    }
};





class MyWindow : public QMainWindow {
    Q_OBJECT
public:
    MyWindow(QWidget *parent = nullptr);
private:
    QWidget *centralWidget;
    QTextEdit *textEdit; // Пример виджета
};

#endif // MAINWINDOW_H
