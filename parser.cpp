#include "parser.h"

Parser::Parser(QVector<Token> tokens)
{
    this->tokens = tokens;
}

void Parser::parse()
{
    counter = 0;
    has_error = false;

    while(counter < tokens.size() && !has_error) {
        // Call the helper function to extend the root and
        // create the parse tree
    }
}


void Parser:: match(QString inputToken)
{
    if(inputToken == tokens[counter].getValue()) // if the input of the function is the value
    {
        counter++;
    }
    else if(inputToken == tokens[counter].getType()) // if the input of the function is the type
    {
        counter++;
    }
    else
    {
        has_error = true;
    }
}

//########################## EBNF RULES ####################################
/*
 program -> stmt sequence
 stmt-sequence -> statement {;statement}
 statement -> if stmt | repeat stmt | assign stmt | read stmt | write stmt
 if-stmt -> if exp then stmt-sequence [else stmt-sequence] end
 repeat-stmt -> repeat stmt-sequence until exp
 assign-stmt -> identifier := exp
 read-stmt -> read identifier
 write-stmt -> write exp
 exp -> simple-exp  [comparison-op  simple-exp]
 comparison-op ->   < | > | =
 simple-exp -> term { addop term }
 term -> factor { mulop factor}
 mulop -> * | /
 factor -> (exp) | number | identifier
 addop -> + | -
 */



// term -> factor { mulop factor}
Parser::Node* Parser:: term(void)
{
    Node* temp = nullptr;
    temp = factor();
    while(counter + 1 < tokens.size() && (tokens[counter].getValue() == "*" || tokens[counter].getValue() == "/"))
    {  Node* newtemp = new Node("op", "(" + tokens[counter].getValue() + ")");
       match(tokens[counter].getValue());
       newtemp->left = temp;
       newtemp->right = factor();
       temp = newtemp;
    }
    return temp;
}

// factor -> (exp) | number | identifier
Parser::Node* Parser:: factor(void)
{
    Node* temp = nullptr;
    if(tokens[counter].getType() == "NUMBER")
    {
        temp = new Node("const", "(" + tokens[counter].getValue()+ ")");
        temp->left = nullptr;
        temp->right = nullptr;
        match(tokens[counter].getType());
    }
    else if(tokens[counter].getType() == "IDENTIFIER")
    {
        temp = new Node("id","("+ tokens[counter].getValue() + ")");
        temp->left = nullptr;
        temp->right = nullptr;
        match(tokens[counter].getType());
    }
    else if(tokens[counter].getValue() == "(")
    {
        match("(");
        temp = exp();
        match(")");
    }
    else
    {
        has_error = true;
    }
     return temp;
}

//simple-exp -> term { addop term }
Parser::Node* Parser:: simpleExp(void)
{
    Node* temp = term();
    while(counter <tokens.size() && (tokens[counter].getValue() == "+" || tokens[counter].getValue() == "-"))
    {
        Node* newtemp = new Node("op", "(" + tokens[counter].getValue() + ")");
        match(tokens[counter].getValue());
        newtemp->left = temp;
        newtemp->right = term();
        temp = newtemp;
    }
   return temp;
}




//exp -> simple-exp  [comparison-op  simple-exp]
Parser::Node* Parser::exp(){
    Node* temp= simpleExp();
    if(tokens[counter].getValue() == "<" || tokens[counter].getValue() == ">" || tokens[counter].getValue() == "=")
    {
        Node* newtemp = new Node("op", "(" + tokens[counter].getValue() + ")");
        match(tokens[counter].getValue());
        newtemp->left = temp;
        newtemp->right = simpleExp();
        temp = newtemp;
    }
    return temp;
}



Parser::Node::Node(QString tokenType, QString tokenValue)
{
    type = tokenType;
    value = tokenValue;
}
