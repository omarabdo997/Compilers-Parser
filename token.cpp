#include "token.h"

Token::Token(QString value, QString type): value(value), type(type)
{

}

QString Token::getValue() const
{
    return value;
}

void Token::setValue(const QString &value)
{
    this->value = value;
}

QString Token::getType() const
{
    return type;
}

void Token::setType(const QString &value)
{
    this->type = value;
}


