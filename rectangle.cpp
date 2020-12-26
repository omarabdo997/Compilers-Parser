#include "rectangle.h"

int Rectangle::getXCord() const
{
    return xCord;
}

int Rectangle::getYCord() const
{
    return yCord;
}

Rectangle::Rectangle(int x, int y, QString type, QString name): QGraphicsRectItem(x, y, 100, 60), xCord(x), yCord(y)
{
    QColor blue(52, 152, 219);
    QPen outlinePen(blue);
    outlinePen.setWidth(0);
    QFont font("Times", 15, QFont::Bold);

    QBrush brush(blue);
    QGraphicsTextItem* nameText = new QGraphicsTextItem(name,this);
    int xmove = name.length()<=3 ? 40:10;
    nameText->setX(x+xmove);
    nameText->setY(y+25);
    nameText->setFont(font);
    QGraphicsTextItem* typeText = new QGraphicsTextItem(type,this);
    xmove = type.length()<=3 ? 40:10;
    typeText->setX(x+xmove);
    typeText->setY(y+5);
    typeText->setFont(font);
    this->setPen(outlinePen);
    this->setBrush(brush);
}
