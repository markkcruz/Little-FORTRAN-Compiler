/* Implementation of Recursive-Descent Parser
 * parse.cpp
 * Programming Assignment 2
 * Spring 2021
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "parse.h"

static int error_count = 0;
map<string, bool> defVar;
map<string, Token> SymTable;

namespace Parser {
    bool pushed_back = false;
    LexItem	pushed_token;

    static LexItem GetNextToken(istream& in, int& line) {
        if( pushed_back ) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) {
        if( pushed_back ) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }

}

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
    ++error_count;
    cout << line << ": " << msg << endl;

}



//Program is: Prog = PROGRAM IDENT {Decl} {Stmt} END PROGRAM IDENT
bool Prog(istream& in, int& line)
{
    bool dl = false, sl = false;
    LexItem tok = Parser::GetNextToken(in, line);
    //cout << "in Prog" << endl;

    if (tok.GetToken() == PROGRAM) {
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == IDENT) {
            dl = Decl(in, line);
            if( !dl  )
            {
                ParseError(line, "Incorrect Declaration in Program");
                return false;
            }
            sl = Stmt(in, line);
            if( !sl  )
            {
                ParseError(line, "Incorrect Statement in program");
                return false;
            }
            tok = Parser::GetNextToken(in, line);

            if (tok.GetToken() == END) {
                tok = Parser::GetNextToken(in, line);

                if (tok.GetToken() == PROGRAM) {
                    tok = Parser::GetNextToken(in, line);

                    if (tok.GetToken() == IDENT) {
                        return true;
                    }
                    else
                    {
                        ParseError(line, "Missing Program Name");
                        return false;
                    }
                }
                else
                {
                    ParseError(line, "Missing PROGRAM at the End");
                    return false;
                }
            }
            else
            {
                ParseError(line, "Missing END of Program");
                return false;
            }
        }
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    return false;
}

//Decl = Type : VarList
//Type = INTEGER | REAL | CHAR
bool Decl(istream& in, int& line) {
    bool status = false;
    LexItem tok;
    //cout << "in Decl" << endl;
    LexItem t = Parser::GetNextToken(in, line);

    if(t == INTEGER || t == REAL || t == CHAR) {
        tok = t;
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == COLON) {
            status = IdList(in, line, t);
            //cout<< tok.GetLexeme() << " " << (status? 1: 0) << endl;
            if (status)
            {
                status = Decl(in, line);
                return status;
            }
        }
        else{
            ParseError(line, "Missing Colon");
            return false;
        }
    }

    Parser::PushBackToken(t);
    return true;
}

//Stmt is either a PrintStmt, ReadStmt, IfStmt, or an AssigStmt
//Stmt = AssigStmt | IfStmt | PrintStmt | ReadStmt
bool Stmt(istream& in, int& line) {
    bool status;
    //cout << "in Stmt" << endl;
    LexItem t = Parser::GetNextToken(in, line);

    switch( t.GetToken() ) {

        case PRINT:
            status = PrintStmt(in, line);
            //cout << "status: " << (status? true:false) <<endl;
            if(status)
                status = Stmt(in, line);
            break;

        case IF:
            status = IfStmt(in, line);
            if(status)
                status = Stmt(in, line);
            break;

        case IDENT:
            Parser::PushBackToken(t);
            status = AssignStmt(in, line);
            if(status)
                status = Stmt(in, line);
            break;

        case READ:
            status = ReadStmt(in, line);
            //cout << "status: " << (status? true:false) <<endl;
            if(status)
                status = Stmt(in, line);
            break;

        default:
            Parser::PushBackToken(t);
            return true;
    }

    return status;
}

//PrintStmt:= print, ExpreList
bool PrintStmt(istream& in, int& line) {
    //bool ex = false ;
    LexItem t;
    //cout << "in PrintStmt" << endl;
    if( (t=Parser::GetNextToken(in, line)) != COMA ) {

        ParseError(line, "Missing a Comma");
        return false;
    }

    bool ex = ExprList(in, line);

    if( !ex ) {
        ParseError(line, "Missing expression after print");
        return false;
    }

    //Evaluate: print out the list of expressions values

    return ex;
}

//IfStmt:= if (Expr) then {Stmt} END IF
bool IfStmt(istream& in, int& line) {
    bool ex=false ;
    LexItem t;
    //cout << "in IfStmt" << endl;
    if( (t=Parser::GetNextToken(in, line)) != LPAREN ) {

        ParseError(line, "Missing Left Parenthesis");
        return false;
    }

    ex = LogicExpr(in, line);
    if( !ex ) {
        ParseError(line, "Missing if statement Logic Expression");
        return false;
    }

    if((t=Parser::GetNextToken(in, line)) != RPAREN ) {

        ParseError(line, "Missing Right Parenthesis");
        return false;
    }

    if((t=Parser::GetNextToken(in, line)) != THEN ) {

        ParseError(line, "Missing THEN");
        return false;
    }

    bool st = Stmt(in, line);
    if( !st ) {
        ParseError(line, "Missing statement for IF");
        return false;
    }

    //Evaluate: execute the if statement

    if((t=Parser::GetNextToken(in, line)) != END ) {

        ParseError(line, "Missing END of IF");
        return false;
    }
    if((t=Parser::GetNextToken(in, line)) != IF ) {

        ParseError(line, "Missing IF at End of IF statement");
        return false;
    }

    return true;
}

bool ReadStmt(istream& in, int& line)
{
    //bool ex = false ;
    LexItem t;
    //cout << "in ReadStmt" << endl;
    if( (t=Parser::GetNextToken(in, line)) != COMA ) {

        ParseError(line, "Missing a Comma");
        return false;
    }

    bool ex = VarList(in, line);

    if( !ex ) {
        ParseError(line, "Missing Variable after Read Statement");
        return false;
    }

    //Evaluate: print out the list of expressions values

    return ex;
}
//IdList:= IDENT {,IDENT}
bool IdList(istream& in, int& line, LexItem type) {
    bool status = false;
    string identstr;
    //cout << "in IdList" << endl;
    LexItem tok = Parser::GetNextToken(in, line);
    if(tok == IDENT)
    {
        //set IDENT lexeme to the type tok value
        identstr = tok.GetLexeme();
        if (!(defVar.find(identstr)->second))
        {
            defVar[identstr] = true;
            SymTable[identstr] = type.GetToken();
        }
        else
        {
            ParseError(line, "Variable Redefinition");
            return false;
        }

    }
    else
    {
        ParseError(line, "Missing Variable");
        return false;
    }

    tok = Parser::GetNextToken(in, line);

    if (tok == COMA) {
        status = IdList(in, line, tok);
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    else{
        Parser::PushBackToken(tok);
        return true;
    }
    return status;
}

//VarList
bool VarList(istream& in, int& line)
{
    bool status = false;
    string identstr;
    //cout << "in VarList" << endl;
    status = Var(in, line);

    if(!status)
    {
        ParseError(line, "Missing Variable");
        return false;
    }

    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == COMA) {
        status = VarList(in, line);
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    else{
        Parser::PushBackToken(tok);
        return true;
    }
    return status;
}

//Var:= ident
bool Var(istream& in, int& line)
{
    //called only from the AssignStmt function
    string identstr;
    //cout << "in Var" << endl;
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == IDENT){
        identstr = tok.GetLexeme();
        if (!(defVar.find(identstr)->second))
        {
            ParseError(line, "Undeclared Variable");
            return false;

        }
        return true;
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    return false;
}

//AssignStmt:= Var = Expr
bool AssignStmt(istream& in, int& line) {
    //cout << "in AssignStmt" << endl;
    bool varstatus = false, status = false;
    LexItem t;

    varstatus = Var( in, line);
    //cout << "varstatus:" << varstatus << endl;

    if (varstatus){
        t = Parser::GetNextToken(in, line);
        //cout << t.GetLexeme() << endl;
        if (t == ASSOP){
            status = Expr(in, line);
            if(!status) {
                ParseError(line, "Missing Expression in Assignment Statment");
                return status;
            }

        }
        else if(t.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << t.GetLexeme() << ")" << endl;
            return false;
        }
        else {
            ParseError(line, "Missing Assignment Operator =");
            return false;
        }
    }
    else {
        ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
        return false;
    }
    return status;
}

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
    bool status = false;
    //cout << "in ExprList" << endl;
    status = Expr(in, line);
    if(!status){
        ParseError(line, "Missing Expression");
        return false;
    }

    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == COMA) {
        status = ExprList(in, line);
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    else{
        Parser::PushBackToken(tok);
        return true;
    }
    return status;
}

//Expr:= Term {(+|-) Term}
bool Expr(istream& in, int& line) {
    //cout << "in Expr" << endl;
    bool t1 = Term(in, line);
    LexItem tok;

    if( !t1 ) {
        return false;
    }

    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    while ( tok == PLUS || tok == MINUS )
    {
        t1 = Term(in, line);
        if( !t1 )
        {
            ParseError(line, "Missing operand after operator");
            return false;
        }

        tok = Parser::GetNextToken(in, line);
        if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }

        //Evaluate: evaluate the expression for addition or subtraction
    }
    Parser::PushBackToken(tok);
    return true;
}

//Term:= SFactor {(*|/) SFactor}
bool Term(istream& in, int& line) {
    //cout << "in Term" << endl;
    bool t1 = SFactor(in, line);
    LexItem tok;
    //cout << "status of factor1: " << t1<< endl;
    if( !t1 ) {
        return false;
    }

    tok	= Parser::GetNextToken(in, line);
    if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    while ( tok == MULT || tok == DIV  )
    {
        t1 = SFactor(in, line);
        //cout << "status of factor2: " << t1<< endl;
        if( !t1 ) {
            ParseError(line, "Missing operand after operator");
            return false;
        }

        tok	= Parser::GetNextToken(in, line);
        if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
        //Evaluate: evaluate the expression for multiplication or division
    }
    Parser::PushBackToken(tok);
    return true;
}

//SFactor = Sign Factor | Factor
bool SFactor(istream& in, int& line)
{
    LexItem t = Parser::GetNextToken(in, line);
    bool status;
    int sign = 0;
    if(t == MINUS )
    {
        sign = -1;
    }
    else if(t == PLUS)
    {
        sign = 1;
    }
    else
        Parser::PushBackToken(t);

    status = Factor(in, line, sign);
    return status;
}
//LogicExpr = Expr (== | <) Expr
bool LogicExpr(istream& in, int& line)
{
    //cout << "in Logic Expr" << endl;
    bool t1 = Expr(in, line);
    LexItem tok;

    if( !t1 ) {
        return false;
    }

    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    if ( tok == LTHAN  || tok == EQUAL)
    {
        t1 = Expr(in, line);
        if( !t1 )
        {
            ParseError(line, "Missing expression after relational operator");
            return false;
        }
        return true;
    }
    Parser::PushBackToken(tok);
    return true;
}

//Factor := ident | iconst | rconst | sconst | (Expr)
bool Factor(istream& in, int& line, int sign) {
    //cout << "in Factor" << endl;
    LexItem tok = Parser::GetNextToken(in, line);


    if( tok == IDENT ) {
        //check if the var is defined
        //int val;
        string lexeme = tok.GetLexeme();
        if (!(defVar.find(lexeme)->second))
        {
            ParseError(line, "Undefined Variable");
            return false;
        }
        return true;
    }
    else if( tok == ICONST ) {

        return true;
    }
    else if( tok == SCONST ) {

        return true;
    }
    else if( tok == RCONST ) {

        return true;
    }
    else if( tok == LPAREN ) {
        bool ex = Expr(in, line);
        if( !ex ) {
            ParseError(line, "Missing expression after (");
            return false;
        }
        if( Parser::GetNextToken(in, line) == RPAREN )
            return ex;

        ParseError(line, "Missing ) after expression");
        return false;
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    ParseError(line, "Unrecognized input");
    return 0;
}



