#ifndef TOKEN_H
#define TOKEN_H
#include <QString>

class Token
{
private:
    QString value;
    QString type;
public:
    Token(QString value, QString type);
    QString getValue() const;
    void setValue(const QString &value);
    QString getType() const;
    void setType(const QString &value);
};

#endif // TOKEN_H
