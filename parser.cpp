#include "parser.h"

Parser::Parser(QVector<Token> tokens)
{
    this.tokens = tokens;
}

void Parser::parse()
{
    counter = 0;
    has_error = false; 
    root = NULL;
    while(counter < tokens.size() && !has_error) {
        // Call the helper function to extend the root and
        // create the parse tree
    }
}