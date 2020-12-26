#ifndef Ellipse_H
#define Ellipse_H
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QFont>
#include <QLabel>
class Ellipse: public QGraphicsEllipseItem
{
private:
    int xCord;
    int yCord;
public:
    Ellipse(int x, int y, QString type, QString name = "");
    int getXCord() const;
    int getYCord() const;
};

#endif // Ellipse_H
