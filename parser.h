#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QString>
#include "token.h"

class Parser
{
private:
    QVector<Token> tokens;
    int counter;

public:
    struct Node{
        Node* left;
        Node* right;
        Node* next;
        Node* elsePart;
        QString type;
        QString value;
        Node(QString tokenType = "", QString tokenValue = "");
    } *root;

    Parser(QVector<Token> tokens);

    void parse();

    bool has_error;

    // TODO: Add the signature of the helper functions of parse()
    // the functions should return void
    // if there is an error in the parse tree: the functions should
    // set the has_error bool and return.
    // Otherwise, the function should extend the root Node and
    // create the parse tree
    void match(QString inputToken);
    Node* term(void);
    Node* factor(void);
    Node* exp(void);
    Node* simpleExp(void);
    Node* Repeat_stmt(void);
    Node* Assign_stmt(void);
    Node* Read_stmt(void);
    Node* Write_stmt(void);
    Node* if_stmt(void);
    Node* stmt_seq(void);
    Node* statement(void);


};

#endif // PARSER_H
