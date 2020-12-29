#include "parser.h"

Parser::Parser(QVector<Token> tokens)
{
    this->tokens = tokens;
}

void Parser::parse()
{
    counter = 0;
    has_error = false;
    root = nullptr;
    root = stmt_seq();
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
 repeat-stmt -> repeat stmt-sequence until exp (need state_seq)
 assign-stmt -> identifier := exp (DONE)
 read-stmt -> read identifier (DONE)
 write-stmt -> write exp (DONE)
 exp -> simple-exp  [comparison-op  simple-exp] (DONE)
 comparison-op ->   < | > | = (DONE)
 simple-exp -> term { addop term } (DONE)
 term -> factor { mulop factor} (DONE)
 mulop -> * | / (DONE)
 factor -> (exp) | number | identifier (DONE)
 addop -> + | - (DONE)
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
        match(tokens[counter].getType());
    }
    else if(tokens[counter].getType() == "IDENTIFIER")
    {
        temp = new Node("id","("+ tokens[counter].getValue() + ")");
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


//assign-stmt -> identifier := exp
Parser::Node* Parser::Assign_stmt()
{
  QString value = tokens[counter].getValue();
  match("IDENTIFIER");
  QString op_type = tokens[counter].getType();
  match("ASSIGN");
  Node* temp = new Node(op_type.toLower(),"("+value+")");
  temp->left= exp();
  return temp;
}


//repeat-stmt -> repeat stmt-sequence until exp
Parser::Node* Parser::Repeat_stmt()
{
  QString value = tokens[counter].getValue();
  match("REPEAT");
  Node* temp = new Node(value,"");
  temp->left=stmt_seq();
  match("UNTIL");
  temp->right= exp();
  return temp;
}


//read-stmt -> read identifier
Parser::Node* Parser::Read_stmt()
{
 QString value = tokens[counter].getValue();
 match("READ");
 QString id = tokens[counter].getValue();
 match("IDENTIFIER");
 Node* temp = new Node(value,"("+id+")");
 return temp;
}


//Write_stmt-> write exp
Parser::Node* Parser::Write_stmt()
{
  QString value = tokens[counter].getValue();
  match("WRITE");
  Node* temp = new Node(value,"");
  temp->left = exp();
  temp->right = nullptr;
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


//if-stmt -> if exp then stmt-sequence [else stmt-sequence] end
Parser::Node* Parser::if_stmt()
{
    match("IF");
    Node* temp = new Node("if","");
    temp->left = exp();
    match("THEN");
    temp->right = stmt_seq();
    if(tokens[counter].getType()=="ELSE")
    {
       match(tokens[counter].getType());
       temp->elsePart = stmt_seq();
    }
    match("END");
    return temp;
}


//statement -> if stmt | repeat stmt | assign stmt | read stmt | write stmt
Parser::Node* Parser::statement()
{
    if(tokens[counter].getType() == "IF"){
            return if_stmt();
    }else if (tokens[counter].getType() == "REPEAT"){
            return Repeat_stmt();
    }else if (tokens[counter].getType() == "READ"){
            return Read_stmt();
    }else if (tokens[counter].getType() == "WRITE"){
            return Write_stmt();
    }else if (tokens[counter].getType() == "IDENTIFIER"){
             return Assign_stmt();
    }
     else return nullptr;
}


// stmt-sequence -> statement {;statement}
Parser::Node* Parser::stmt_seq()
{
     Node* temp = nullptr;
     temp = statement();
     while(tokens[counter].getType()=="SEMICOLON" && counter < tokens.size())
     {
        match(tokens[counter].getType());
        if(counter == tokens.size())
        {
               return temp;
        }
        temp->next = statement();
        if(counter == tokens.size())
        {
               return temp;
        }
        if(Parser::has_error)
        {
               return nullptr;
        }
     }

     return temp;
}


Parser::Node::Node(QString tokenType, QString tokenValue)
{
    this->type = tokenType;
    this->value = tokenValue;
    this->left=nullptr;
    this->right=nullptr;
    this->next=nullptr;
    this->elsePart=nullptr;
}
