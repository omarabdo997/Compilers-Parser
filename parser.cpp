#include "parser.h"

Parser::Parser(vector<Token> tokens)
{
    this->tokens = tokens;
}

void Parser::parse()
{
    counter = 0;
    has_error = false;
    root = nullptr;
    root = stmt_seq();
    if (counter != tokens.size()){
        has_error = true;
    }
}


void Parser:: match(QString inputToken)
{
    if(inputToken == tokens.at(counter).getValue()) // if the input of the function is the value
    {
        counter++;
    }
    else if(inputToken == tokens.at(counter).getType()) // if the input of the function is the type
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
    while(counter + 1 < tokens.size() && (tokens.at(counter).getValue() == "*" || tokens.at(counter).getValue() == "/"))
    {  Node* newtemp = new Node("op", "(" + tokens.at(counter).getValue() + ")");
       match(tokens.at(counter).getValue());
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
    if(tokens.at(counter).getType() == "NUMBER")
    {
        temp = new Node("const", "(" + tokens.at(counter).getValue()+ ")");
        match(tokens.at(counter).getType());
    }
    else if(tokens.at(counter).getType() == "IDENTIFIER")
    {
        temp = new Node("id","("+ tokens.at(counter).getValue() + ")");
        match(tokens.at(counter).getType());
    }
    else if(tokens.at(counter).getValue() == "(")
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
    while(counter <tokens.size() && (tokens.at(counter).getValue() == "+" || tokens.at(counter).getValue() == "-"))
    {
        Node* newtemp = new Node("op", "(" + tokens.at(counter).getValue() + ")");
        match(tokens.at(counter).getValue());
        newtemp->left = temp;
        newtemp->right = term();
        temp = newtemp;
    }
   return temp;
}


//assign-stmt -> identifier := exp
Parser::Node* Parser::Assign_stmt()
{
  QString value = tokens.at(counter).getValue();
  match("IDENTIFIER");
  QString op_type = tokens.at(counter).getType();
  match("ASSIGN");
  Node* temp = new Node(op_type.toLower(),"("+value+")");
  temp->left= exp();
  return temp;
}


//repeat-stmt -> repeat stmt-sequence until exp
Parser::Node* Parser::Repeat_stmt()
{
  QString value = tokens.at(counter).getValue();
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
 QString value = tokens.at(counter).getValue();
 match("READ");
 QString id = tokens.at(counter).getValue();
 match("IDENTIFIER");
 Node* temp = new Node(value,"("+id+")");
 return temp;
}


//Write_stmt-> write exp
Parser::Node* Parser::Write_stmt()
{
  QString value = tokens.at(counter).getValue();
  match("WRITE");
  Node* temp = new Node(value,"");
  temp->left = exp();
  temp->right = nullptr;
  return temp;
}


//exp -> simple-exp  [comparison-op  simple-exp]
Parser::Node* Parser::exp(){
    Node* temp= simpleExp();
    if(counter >= tokens.size()) {
        return temp;
    }
    if(tokens.at(counter).getValue() == "<" || tokens.at(counter).getValue() == ">" || tokens.at(counter).getValue() == "=")
    {
        Node* newtemp = new Node("op", "(" + tokens.at(counter).getValue() + ")");
        match(tokens.at(counter).getValue());
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
    if(tokens.at(counter - 1).getType()== "SEMICOLON")
    {
        has_error = true;
        return nullptr;
    }
    if(tokens.at(counter).getType()=="ELSE")
    {
       match(tokens.at(counter).getType());
       temp->elsePart = stmt_seq();
    }
    match("END");
    return temp;
}


//statement -> if stmt | repeat stmt | assign stmt | read stmt | write stmt
Parser::Node* Parser::statement()
{
    if(tokens.at(counter).getType() == "IF"){
            return if_stmt();
    }else if (tokens.at(counter).getType() == "REPEAT"){
            return Repeat_stmt();
    }else if (tokens.at(counter).getType() == "READ"){
            return Read_stmt();
    }else if (tokens.at(counter).getType() == "WRITE"){
            return Write_stmt();
    }else if (tokens.at(counter).getType() == "IDENTIFIER"){
             return Assign_stmt();
    }
     else return nullptr;
}


// stmt-sequence -> statement {;statement}
Parser::Node* Parser::stmt_seq()
{
     Node* temp = nullptr;
     temp = statement();
     while(counter < tokens.size() && tokens.at(counter).getType()=="SEMICOLON")
     {

        match(tokens.at(counter).getType());
        if(counter == tokens.size())
        {
               has_error= true;
               return nullptr;
        }
        Node* next = temp;
        while(next->next != nullptr) {
            next = next->next;
        }
        next->next = statement();
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
