#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <QGraphicsRectItem>
#include <QPen>
#include <QFont>
#include <QLabel>

class Rectangle: public QGraphicsRectItem
{
private:
    int xCord;
    int yCord;
public:
    Rectangle(int x, int y, QString type, QString name = "");
    int getXCord() const;
    int getYCord() const;
};

#endif // RECTANGLE_H
