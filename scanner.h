#ifndef SCANNER_H
#define SCANNER_H
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <QDebug>
#include <QString>
using namespace std;

struct Token_And_Type{
string type;
string value;
Token_And_Type(string value,string type):value(value),type(type)
{

}
Token_And_Type()
{

}
};

class scanner
{

public:
    virtual ~scanner();
    scanner();
    vector<string> read_code_file();
    void Scan_Process(vector<string> s);
    void print_Token_TYPE();
    vector<Token_And_Type> get_Tokens();
    void Write_in_file();
    string process_line(string );


    vector<Token_And_Type> getToken_Type() const;

private:

    void organize_Tokens();
    vector< vector<string> >processing_file();
    string capitalize(string);
    string map_special_character(string);
    bool isNumber(string);
    bool is_special_character(string);
    void scan_output();
    bool is_Reserved_keyword(string symbol);
private:
    string file_name;
    ofstream out_code;
    bool file_found = false;
    vector<string>code;
    vector<vector<string> >processed_code;
    vector<Token_And_Type>Token_Type;
    vector<string> reserved_keywords = {"if","then","repeat","until","read","write","end","else"};
    vector<string> special_chars= {"{","}",":=","*","/","+","-","<",">","<=",">=",";","=","(",")"};
};

#endif // SCANNER_H
