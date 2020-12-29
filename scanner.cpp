#include "scanner.h"

scanner::scanner()
{
}

vector<string> scanner::read_code_file()
{
    ifstream input_code;
    vector<string>code_1;
    vector<string>code;
    string input;
    input_code.open(file_name);
    if(input_code.is_open())
    {
        while(!input_code.eof())
        {
            file_found=true;
            getline(input_code,input);
            if(input.length())code.push_back(scanner::process_line(input));
        }
        input_code.close();
    }
    else
    {
        cout<<"File not Found!\n";
        file_found=false;
    }

    return code;
}
string scanner::process_line(string line)
{
    string output="";
    for(int i=0; i<line.length()-1; i++)
    {
        string t ="";
        t+=line[i];
        t+=line[i+1];
        if(is_special_character(t))
        {
            output+=" "+t+" ";
            i+=1;
        }
        else if(is_special_character(t.substr(0,1)))
        {
            output+=" ";
            output+=line[i];
            output+=" ";
        }
        else  output+=line[i];
    }
    output+=line[line.length()-1];
    return output;
}
bool scanner::isNumber(string numb)
{
    bool T=1;
    for(char c:numb)if(c!=' ')T&=isdigit(c);
    return T;

}
void scanner::organize_Tokens()
{
    bool T=true;
    vector<Token_And_Type>Token_Type_modified;
    for(int i=0; i<Token_Type.size(); i++)
    {
        if(Token_Type[i].value!="{"&&Token_Type[i].value!="}")
        {
            if(T)Token_Type_modified.push_back(Token_Type[i]);
        }
        else
        {
            if(Token_Type[i].value=="{")T=false;
            else if(Token_Type[i].value=="}")T=true;
        }
    }
    Token_Type=Token_Type_modified;
}
vector<vector<string> >scanner::processing_file()
{
    vector< vector<string> > process_final;
    for(int i=0; i<code.size(); i++)
    {
        string processing = code[i];
        vector<string>process;
        int b=0;
        for(int j=0; j<processing.length()-1; j++)
        {
            if(processing[j]==' ')b=j+1;
            if(processing[j]!=' '&&(processing[j+1]==' '||processing[j+1]=='{'))
            {
                string preprocess= processing.substr(b,j-b+1);
                if(preprocess[preprocess.length()-1]==';'||preprocess[preprocess.length()-1]=='}')
                {
                    process.push_back(preprocess.substr(0,preprocess.length()-1));
                    process.push_back(preprocess.substr(preprocess.length()-1,1));
                }
                else if(preprocess[0]=='{'&&preprocess.length()>1)
                {
                    process.push_back("{");
                    process.push_back(preprocess.substr(1,preprocess.length()-1));
                }
                else
                {
                    process.push_back(processing.substr(b,j-b+1));
                }
                b=j+1;
            }
        }
        if(processing[processing.length()-1]!=' ')
        {
            if((processing[processing.length()-1]=='}'||processing[processing.length()-1]==';')&&processing.length()>1)
            {
                process.push_back(processing.substr(b,processing.length()-b-1));
                process.push_back(processing.substr(processing.length()-1,1));
            }
            else
            {
                process.push_back(processing.substr(b,processing.length()-b));
            }
        }
        process_final.push_back(process);
    }

    return process_final;
}
void scanner::scan_output()
{

    for(int i=0; i<processed_code.size(); i++)
    {
        vector<string>process = processed_code[i];
        Token_And_Type token = Token_And_Type();
        bool T=true;
        for(int j=0; j<process.size(); j++)
        {
            if(process[j].length()<1)continue;
            token.value=process[j];
            if(is_Reserved_keyword(process[j]))
            {
                token.type=capitalize(process[j]);
            }
            else if(is_special_character(process[j]))
            {
                token.type=map_special_character(process[j]);
            }
            else if(isNumber(process[j]))
            {
                token.type="NUMBER";
            }
            else
            {
                token.type="IDENTIFIER";
            }
            Token_Type.push_back(token);
        }
    }
    organize_Tokens();
}
bool scanner::is_special_character(string symbol)
{
    for(int k =0; k<special_chars.size(); k++)
    {
        if(symbol==special_chars[k])
        {
            return true;
        }
    }
    return false;

}
bool scanner::is_Reserved_keyword(string symbol)
{
    for(int k =0; k<reserved_keywords.size(); k++)
    {
        if(symbol==reserved_keywords[k])
        {
            return true;
        }
    }
    return false;
}

vector<Token_And_Type> scanner::getToken_Type() const
{
    return Token_Type;
}
string scanner::capitalize(string s)
{
    string t="";
    for(char x:s)
    {
        t+=(char)toupper(x);
    }
    return t;
}
vector<Token_And_Type> scanner::get_Tokens(){
return scanner::Token_Type;
}
string scanner::map_special_character(string s)
{
    if(s=="<")return "LESSTHAN";
    else if(s==">")return "BIGGERTHAN";
    else if(s==">=")return  "MORETHANOREQUAL";
    else if(s=="<=")return "LESSTHANOREQUAL";
    else if(s==":=")return "ASSIGN";
    else if(s=="+")return "PLUS";
    else if(s=="-")return "MINUS";
    else if(s=="*")return "MULT";
    else if(s=="{")return "OPENCURLYBRACKET";
    else if(s=="}")return "CLOSECURLYBRACKET";
    else if(s==";")return "SEMICOLON";
    else if(s=="=")return "EQUAL";
    else if(s=="/")return "DIV";
    else if(s=="(")return "OPENBRACKET";
    else if(s==")")return "CLOSEBRACKET";

}
void scanner::Scan_Process(vector<string> s)
{
    code = s;
    processed_code = processing_file();
    scanner::scan_output();
    scanner::print_Token_TYPE();
    scanner::Write_in_file();
}
void scanner::Write_in_file()
{
    out_code.open("Tokens.text");
    for(int i=0;i<Token_Type.size();i++)out_code<<Token_Type[i].value<<","<<Token_Type[i].type<<"\n";
}
void scanner::print_Token_TYPE()
{
    for(int i=0;i<Token_Type.size();i++)cout<<Token_Type[i].value<<","<<Token_Type[i].type<<"\n";
}
scanner::~scanner()
{
    //dtor
}
