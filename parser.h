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
        QString type;
        QString name;
    } root;

    Parser(QVector<Token> tokens);

    void parse();
    
    bool has_error;
    
    // TODO: Add the signature of the helper functions of parse()
    // the functions should return void
    // if there is an error in the parse tree: the functions should 
    // set the has_error bool and return.
    // Otherwise, the function should extend the root Node and
    // create the parse tree
};

#endif // PARSER_H