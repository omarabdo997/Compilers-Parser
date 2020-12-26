#include "ellipse.h"

int Ellipse::getXCord() const
{
    return xCord;
}

int Ellipse::getYCord() const
{
    return yCord;
}

Ellipse::Ellipse(int x, int y, QString type, QString name): QGraphicsEllipseItem(x, y, 100, 60), xCord(x), yCord(y)
{
    QColor orange(249, 224, 202);
    QPen outlinePen(orange);
    outlinePen.setWidth(0);
    QFont font("Times", 15, QFont::Bold);

    QBrush brush(orange);
    QGraphicsTextItem* nameText = new QGraphicsTextItem(name,this);
    int xmove = name.length()<=3 ? 30:10;
    nameText->setX(x+xmove);
    nameText->setY(y+25);
    nameText->setFont(font);
    QGraphicsTextItem* typeText = new QGraphicsTextItem(type,this);
    xmove = type.length()<=3 ? 30:10;
    typeText->setX(x+xmove);
    typeText->setY(y+5);
    typeText->setFont(font);
    this->setPen(outlinePen);
    this->setBrush(brush);
}
