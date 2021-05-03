/* Implementation of Recursive-Descent Parser
 * parse.cpp
 * Programming Assignment 2
 * Spring 2021
*/

/*
 * Grammar Rules
 * Prog = PROGRAM IDENT {Decl} {Stmt} END PROGRAM IDENT
 * Decl = (INTEGER|REAL|CHAR):IdList
 * IdList = IDENT{,IDENT}
 * Stmt = AssigStmt|IfStmt|PrintStmt
 * PrintStmt=PRINT,ExprList
 * IfStmt=IF(LogicExpr)THEN{Stmt}ENDIF
 * AssignStmt = Var = Expr
 * ExprList=Expr{,Expr}
 * Expr = Term {(+|-)Term}
 * Term = SFactor{(*|/)SFactor}
 * SFactor = SignFactor|Factor
 * LogicExpr = Expr (==|<) Expr
 * Var = IDENT
 * Sign= +|-
 * Factor = IDENT|ICONST|RCONST|SCONST| (Expr)
*/


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "parserInt.h"
// A map container that keeps record of the DEFINED variables in the parsed program.
// The key of the defVar is a variable name, and the value is a Boolean that is set to 'true' when the first time the variable has been declared in a declaration statement, otherwise it is false
map<string, bool> defVar;

// A map container that keeps a recorded for each DECLARED variable in the parsed program and its corresponding type.
// The key of the SymTable is a variable name, and the value is a Token that is set to the type token (e.g., INTEGER, REAL, or CHAR) when the variable is declared in a declaration statement.
map<string, Token> SymTable;

map<string, Value> TempsResults; //Container of temporary locations of Value objects for results of expressions, variables values and constants
queue <Value> * ValQue; //declare a pointer variable to a queue of Value objects

//Global variable for left side of assignment statement.
LexItem assignment_variable;

// Flags for if we should add, multiply, subtract, or divide!
bool addFlag = false;
bool subtractFlag = false;
bool multiplyFlag = false;
bool divideFlag = false;


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

static int error_count = 0;

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

	// Check if the beginning program name is the same as the ending one.
    LexItem programName;

	if (tok.GetToken() == PROGRAM) {
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == IDENT) {
            programName = tok; // Saving program name
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
					    // Check if the program name declared at the beginning is the same as this ident
					    if (tok.GetLexeme() == programName.GetLexeme()) {
                            return true;
					    } else { // parseerror, not the same program nameS
					        ParseError(line, "Incorrect Program Name");
					        return false;
					    }
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

	LexItem t = Parser::GetNextToken(in, line);

    // Store the variable that is an Ident so we can assign the value after expression is done.
    //LexItem assignedToken = t; // Variable we are assigning the value to

    //Value value(5);
	switch( t.GetToken() ) {

	case PRINT:
		status = PrintStmt(in, line);

		if(status)
			status = Stmt(in, line);
		break;

	case IF:
		status = IfStmt(in, line);
		if(status)
			status = Stmt(in, line);
		break;

	case IDENT:



        assignment_variable = t;


		Parser::PushBackToken(t);
        status = AssignStmt(in, line);
        // Now put this assigned value into the TempsResults
        // Maybe do this in expression


		if(status)
			status = Stmt(in, line);
		break;

	case READ:
		status = ReadStmt(in, line);

		if(status)
			status = Stmt(in, line);
		break;

	default:
		Parser::PushBackToken(t);
		return true;
	}

	return status;
}


// Checks the returned value, if it returns false an error message is printed such as "Missing expression after print" Then the PrintStmt function returns false value
// Evaluation: the funciton prints out the list of expression's values an returns successfully
// Proviedes the checking of what the expression lists.
//PrintStmt:= print, ExprList
bool PrintStmt(istream& in, int& line) {
    LexItem t;
    /*create an empty queue of Value objects.*/
    ValQue = new queue<Value>;
    if ((t=Parser::GetNextToken(in, line)) != COMA) {
        ParseError(line, "Missing a Comma");
        return false;
    }
    bool ex = ExprList(in, line);
    if (!ex) {
        ParseError(line, "Missing expression after print");
        while(!(*ValQue).empty()) {
            ValQue->pop();
        }
        delete ValQue;
        return false;
    }
    // Evaluate: print out the list of expressions' values
    while (!(*ValQue).empty()) {
        Value nextVal = (*ValQue).front();
        cout << nextVal;
        ValQue->pop();
    }
    cout <<endl;
    return ex;
}// PrintStmt

//IfStmt:= if (Expr) then {Stmt} END IF
bool IfStmt(istream& in, int& line) {
	bool ex=false ;
	LexItem t;

	if( (t=Parser::GetNextToken(in, line)) != LPAREN ) {

		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	// Declare a Value type token to move down the chain of command
	Value retVal; // The boolean value that will indicate whether or not to output the statements yo
	ex = LogicExpr(in, line, retVal);
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

	// if the retVal bool is true, then do these statements. Else, skip until we hit the end token.
    bool st = true;
	if (retVal.GetBool()){
	    // true, so do the statements
        bool st = Stmt(in, line);
    } else {
	    // Kill the tokens until we hit END.
        while((t=Parser::GetNextToken(in, line)) != END ){
            // do nothing lol
        }
        Parser::PushBackToken(t);
	}




	if( !st ) {
		ParseError(line, "Missing statement for IF");
		return false;
	}



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

	LexItem t;

	if( (t=Parser::GetNextToken(in, line)) != COMA ) {

		ParseError(line, "Missing a Comma");
		return false;
	}

	bool ex = VarList(in, line);

	if( !ex ) {
		ParseError(line, "Missing Variable after Read Statement");
		return false;
	}



	return ex;
}



//IdList:= IDENT {,IDENT}
bool IdList(istream& in, int& line, LexItem & tok) {
    LexItem type = tok;
    bool status = false;
	string identstr;

	tok = Parser::GetNextToken(in, line);
    identstr = tok.GetLexeme();
	if(tok == IDENT)
	{
		//set IDENT lexeme to the type tok value
		identstr = tok.GetLexeme();
		if ((defVar.find(identstr) == defVar.end()))
		{
			defVar[identstr] = true;
			SymTable[identstr] = type.GetToken();

			// TempsResults map Insertion ??? Maybe

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

	LexItem token = Parser::GetNextToken(in, line);

	if (token == COMA) {
		status = IdList(in, line, type);
	}
	else if(token.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << token.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(token);
		return true;
	}
	return status;
}

//VarList
bool VarList(istream& in, int& line)
{
	bool status = false;
	string identstr;

	LexItem placeHolderTok;

	status = Var(in, line, placeHolderTok);

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
bool Var(istream& in, int& line, LexItem & tok)
{
	//called only from the AssignStmt function
	string identstr;

	tok = Parser::GetNextToken(in, line);

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

	bool varstatus = false, status = false;
	LexItem t;

    LexItem placeHolderTok;

    Value value;

	varstatus = Var( in, line, placeHolderTok);


	if (varstatus){
		t = Parser::GetNextToken(in, line);

		if (t == ASSOP){
            // Declare a Value type token to move down the chain of command

			status = Expr(in, line, value);
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

	// truncating now.

    //cout << SymTable[assignment_variable.GetLexeme()];
	// Then we must truncate the value.
    if ((SymTable[assignment_variable.GetLexeme()] == INTEGER) && (value.IsReal())) {
        Value newValue = static_cast<int>(value.GetReal());
        value = newValue;
    }


	// Now insert the value of this assignment statement into the variable that called this assignment statement. "t.GetLexeme()"
    TempsResults.insert(std::pair<string, Value>(assignment_variable.GetLexeme(),value));
	return status;
}

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;

    // Declare a Value type token to move down the chain of command
    Value value;
	status = Expr(in, line, value);
	if(!status){
		ParseError(line, "Missing Expression");
		return false;
	}
	// Push that "thing to print" into the queue yo
	ValQue->push(value);

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
bool Expr(istream& in, int& line, Value & retVal) {
    Value val1, val2;
    bool t1 = Term(in, line, val1);
    LexItem tok;
    if(!t1) {
        return false;
    }
    retVal = val1;

    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() == ERR) {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    while (tok == PLUS || tok == MINUS) {
        t1 = Term(in, line, val2);
        if (!t1) {
            ParseError(line, "Missing operand after operator");
            return false;
        }
        // evaluate the expression for addition or subtraction and update the retVal object.
        // Check if the operation of PLUS/MINUS is legal for the type of operands
        if (retVal.GetType() == VCHAR || val2.GetType() == VCHAR) {
            ParseError(line, "Run-Time Error-Illegal Mixed Type Operands");
            return false;
        } else {
            if (tok == PLUS) {
                retVal = retVal + val2;
            }
            else if(tok == MINUS) {
                retVal = retVal - val2;
            }
        }
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == ERR) {
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }
    Parser::PushBackToken(tok);
    return true;
} // Expr

//Term:= SFactor {(*|/) SFactor}
bool Term(istream& in, int& line, Value & retVal) {
    Value val1, val2;
	bool t1 = SFactor(in, line, val1);
	LexItem tok;

	if( !t1 ) {
		return false;
	}
    retVal = val1;

	tok	= Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
	}
	while ( tok == MULT || tok == DIV  ) {

	    /*
	    // check for mult and set flag to mult
	    if (tok == MULT) {
            multiplyFlag = true;
        }
	    // check for div and set flag to div
	    if (tok == DIV) {
            divideFlag = true;
        }
        */

		t1 = SFactor(in, line, val2);
		if( !t1 ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}

		// Check if val2 is zero. If it is, return a ParseError.

		if (val2.IsInt()) {
            if (val2.GetInt() == 0) {
                ParseError(line, "Run-Time Error-Illegal Division by Zero");
                return false;
            }
        }

        // evaluate the expression for addition or subtraction and update the retVal object.
        // Check if the operation of PLUS/MINUS is legal for the type of operands
        if (retVal.GetType() == VCHAR || val2.GetType() == VCHAR) {
            ParseError(line, "Run-Time Error-Illegal Mixed Type Operands");
            return false;
        } else {
            if (tok == MULT) {
                retVal = retVal * val2;
            }
            else if(tok == DIV) {
                retVal = retVal / val2;
            }
        }


		tok	= Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}

	}
	Parser::PushBackToken(tok);
	return true;
}

//SFactor = Sign Factor | Factor
bool SFactor(istream& in, int& line, Value & retVal)
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

	status = Factor(in, line, sign, retVal);
	return status;
}
//LogicExpr = Expr (== | <) Expr
bool LogicExpr(istream& in, int& line, Value & retVal)
{
    Value val1, val2;
	bool t1 = Expr(in, line, val1);
	LexItem tok;

	if( !t1 ) {
		return false;
	}
    retVal = val1;

	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if ( tok == LTHAN  || tok == EQUAL)
	{
		t1 = Expr(in, line, val2);
		if( !t1 )
		{
			ParseError(line, "Missing expression after relational operator");
			return false;
		}

		// Check if val1 and val2 are the same type. If they are not, then output a parseerror. (test case invlogexpr)
		if (!((val1.IsReal() && (val2.IsReal()) || (val1.IsChar() && (val2.IsChar()) || (val1.IsInt()&& (val2.IsInt())))))) {
		    ParseError(line, "Run-Time Error-Illegal Mixed Type operation");
		    return false;
		}

		// Do < boolean
		if ( tok == LTHAN) {
            Value booleanRetVal = val1 < val2;
            retVal = booleanRetVal;
		} else { // (tok == EQUAL)
		    // Do == boolean
            Value booleanRetVal = val1 == val2;
		    retVal = booleanRetVal;
		}

		return true;
	}
	Parser::PushBackToken(tok);
	return true;
}

//Factor := ident | iconst | rconst | sconst | (Expr)
bool Factor(istream& in, int& line, int sign, Value & retVal) {

	LexItem tok = Parser::GetNextToken(in, line);

    // Check if retVal is not an error (Then theres something in it)
    //if (retVal.IsErr())

	if( tok == IDENT ) {
	    string identstr = tok.GetLexeme();
	    // Check if IDENT is in TempsResults. If it is, then lets proceed. Else it is a parseerror of undefinedVar
        if (!(TempsResults.find(identstr) == TempsResults.end())) {
            // Good. The IDENT has a value. Lets do math with it.
            /*
            if (addFlag) {
                retVal = retVal + TempsResults[tok.GetLexeme()];
                addFlag = false;
            }
            if (subtractFlag) {
                retVal = retVal - TempsResults[tok.GetLexeme()];
                subtractFlag = false;
            }
            if (multiplyFlag) {
                retVal = retVal * TempsResults[tok.GetLexeme()];
                multiplyFlag = false;
            }
            if (divideFlag) {
                retVal = retVal / TempsResults[tok.GetLexeme()];
                divideFlag = false;
            }
            */
            retVal = TempsResults[tok.GetLexeme()];
            if (sign != 0) {
                if(retVal.IsInt()) {
                    retVal.SetInt(retVal.GetInt() * sign);
                }
                if(retVal.IsReal()) {
                    retVal.SetReal(retVal.GetReal() * sign);
                }
            }




        } else {
            ParseError(line, "Undefined Variable");
            return false;
        }






		//check if the var is defined
		string lexeme = tok.GetLexeme();
		if (!(defVar.find(lexeme)->second))
		{
			ParseError(line, "Undefined Variable");
			return false;
		}
		return true;
	}
	else if( tok == ICONST ) {
		Value value(stoi(tok.GetLexeme()));
		retVal = value;
        if (sign != 0) {
            retVal.SetInt(retVal.GetInt() * sign);
        }
		return true;
	}
	else if( tok == SCONST ) {
        Value value((tok.GetLexeme()));
        retVal = value;
		return true;
	}
	else if( tok == RCONST ) {
        Value value(stof(tok.GetLexeme()));
        retVal = value;
        if (sign != 0) {
            retVal.SetReal(retVal.GetReal() * sign);
        }
        return true;
	}
	else if( tok == LPAREN ) {
		bool ex = Expr(in, line, retVal);
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



