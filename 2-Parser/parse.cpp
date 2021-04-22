#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "lex.h"
#include "parse.h"

using namespace std;

/* Grammar Rules
 * Prog = PROGRAM IDENT {Decl} {Stmt} END PROGRAM IDENT   --- #DONE
 * Decl = (INTEGER|REAL|CHAR):IdList                      --- #DONE
 * IdList = IDENT{,IDENT}                                 --- #DONE
 * Stmt = AssigStmt|IfStmt|PrintStmt|ReadStmt
 * PrintStmt=PRINT,ExprList
 * IfStmt=IF(LogicExpr)THEN{Stmt}ENDIF
 * AssignStmt = Var = Expr
 * ReadStmt = READ, VarList
 * ExprList=Expr{,Expr}
 * Expr = Term {(+|-)Term}
 * Term = SFactor{(*|/)SFactor}
 * SFactor = SignFactor|Factor
 * LogicExpr = Expr (==|<) Expr
 * Var = IDENT
 * Sign= +|-
 * Factor = IDENT|ICONST|RCONST|SCONST| (Expr) 'Factor" the botton of the recusive decent parse Contains the base cases
*/
// A map container that keeps record of the DEFINED variables in the parsed program.
// The key of the defVar is a variable name, and the value is a Boolean that is set to 'true' when the first time the variable has been declared in a declaration statement, otherwise it is false
map<string, bool> defVar;

// map to check VAR
//map<string, bool> defVarMatching;


// A map container that keeps a recorded for each DECLARED variable in the parsed program and its corresponding type.
// The key of the SymTable is a variable name, and the value is a Token that is set to the type token (e.g., INTEGER, REAL, or CHAR) when the variable is declared in a declaration statement.
map<string, Token> SymTable;

char ch; // Used for checking next char
int varRedefinition = 0; // used to check if a variable was redeclared
// Flag for checking if no more declaration statements
//bool flagDecl = false;
bool varFlag; // Used to determine if the DECL and IDLIST function are done and we are in statements;

namespace Parser {
    bool pushed_back = false;
    LexItem	pushed_token;
    // Used to get a token
    static LexItem GetNextToken(istream& in, int& line) {
        if( pushed_back ) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    // Used to push back a token
    // NOTE: After a push back, the next time you call Parser::GetNextToken(), you will retrieve the pushed-back token
    // NOTE: An exception is thrown is you push back more than once (using abort())
    static void PushBackToken(LexItem & t) {
        if( pushed_back ) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }

}

// Static int variable for counting errors.
static int error_count = 0;
// Function to return the value of error_count.
int ErrCount()
{
    return error_count;
}

// A function definition for handling the display of error messages.
void ParseError(int line, string msg)
{
    ++error_count;
    cout << line << ": " << msg << endl;

}


// ---**************************************************************************--- Parser Function Headers ---**************************************************************************---
// The value returned is false if the call the existing getNextToken, and includes pushback functionality. | "WRAPPER" |
// All recursive-descent functions take a reference to an input stream, and a line number, and return a Boolean value.

// ___________________________
// *Recursive Decent Parser*
// The parser includes one FUNCTION per rule or NONTERMINAL
// Each function recognizes the right hand side of the rule.
//  -If a function needs to read a token, it can read it using getNextToken()
//  -If the function needs a nonterminal symbol, it calls the function for that nonterminal symbol.
// ___________________________



// Called from prog2.cpp | If the call fails, the program should stop and display a message "Unsuccessful Parsing ", and display the number of errors detected.
// If it succeeds, the program should stop and display the message "Successful Parsing ", and the program stops.
// Grammar Rule | Prog = PROGRAM IDENT {Decl} {Stmt} END PROGRAM IDENT
bool Prog(istream& in, int& line) {
    // Will always need to check after most keywords if the next token is " END ".

    bool prog;
    bool stmtFlag;

    bool decl = true;
    // Variable to make sure the program name at the start is the same as the program name at the end.
    LexItem programName;

    LexItem t = Parser::GetNextToken(in, line);
    // Check if the first keyword is PROGRAM
    if (t == PROGRAM) {
        // Get the PROGRAM name and store it
        t = Parser::GetNextToken(in, line);
        // If the next token is an identifier, then it the name of the program
        if (t == IDENT) {
            // Set the programName Variable to the name of the next token.
            programName = t;
            // Check if the next line is an assignment statement: INTEGER, REAL, CHAR and Decl class IDlist
            t = Parser::GetNextToken(in, line);
            if (  ((t.GetToken() == CHAR || t.GetToken() == REAL || t.GetToken() == INTEGER ) ) ) {
                Parser::PushBackToken(t);
                decl = Decl(in, line);
            } else {
                ParseError(line, "Undeclared Variable");
                ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
                ParseError(line, "Incorrect Statement in program");
                return false;
            }
            // check if there was an error in decl
            if (!decl) {
                t = Parser::GetNextToken(in, line);
                if (t.GetLexeme() == "2"){
                    ParseError(line, "Missing Variable");
                } else {
                    ParseError(line, "Incorrect Declaration in Program");
                    return false;
                }
            }

            varFlag = true;
            // Now call the statements
            stmtFlag = Stmt(in, line);
            if (!stmtFlag) {
                ParseError(line, "Incorrect Statement in program");
                return false;
            }
        } else {
            ParseError(line, "Missing name of program");
            return false;
        }
    } else {
        // No PROGRAM keyword was detected at the start of the program.
        ParseError(line, "Missing PROGRAM keyword");
        return false;
    }


    // We are back in Prog() after passing all the other checks. Now check if the END PROGRAM has the same programname.
    // END PROGRAM programname
    t = Parser::GetNextToken(in, line);
    if (t == END){
        t = Parser::GetNextToken(in, line);
        if (t == PROGRAM) {
            t = Parser::GetNextToken(in, line);
            if (t.GetLexeme() == programName.GetLexeme()) {

            } else if (t == DONE) {
                ParseError(line, "Missing Program Name");
                return false;
            } else {
                // wrong program name
                ParseError(line, "Missing END of Program");
                return false;
            }
        } else {
            //missing PROGRAM
            ParseError(line, "Missing PROGRAM at the End");
            return false;
        }
    }  else {
        // missing end
        ParseError(line, "Missing END of Program");
        return false;
    }

    return true;
}

// Grammar rule | Stmt = PrintStmt | AssignmentStmt | ReadStmt | IfStmt
// The function calls Parser::GetNextToken() to determine which right hand side to expand depending on the first token of each statement.
// PRINT token: to call PrintStmt
// IF token: to call IfStmt
// IDENT: to call AssignStmt
// READ: to call ReadStmt
// Otherwise: Push back token and return
bool Stmt(istream& in, int& line) {
    bool status;
    LexItem t = Parser::GetNextToken(in, line);

    switch(t.GetToken()) {
        case PRINT: // PrintStmt Stmt := PrintStmt
            status = PrintStmt(in, line);
            if(status)
                status = Stmt(in, line);
            break;
            // OTHER CASES TO HANDLE
        case IF: // IfStm
            status = IfStmt(in, line);
            if(status)
                status = Stmt(in, line);
            break;
        case IDENT: // Assignment statement
            Parser::PushBackToken(t);
            status = AssignStmt(in, line);
            if(status)
                status = Stmt(in, line);
            break;
        case READ: // Read Stmt
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

// The function calls Parser::GetNextToken() to determine which token type is applied for the declared list of identifiers.
// Grammar Rule | Decl = (INTEGER | REAL | CHAR) : IdList
// The function is called from Prog function
// A call to IdList() function is done after checking for a colon.
// A recursive call to Decl() is done if the status of the call to IdList function is true.
bool Decl(istream& in, int& line) {
    bool status = false;
    LexItem tok;
    LexItem t = Parser::GetNextToken(in, line);
    if (t == INTEGER || t == REAL || t == CHAR) {
        tok = t;
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == COLON) {
            status = IdList(in, line, t);
            if (!status) {
                return false;
            }

            // TESTV2
            // check if there was a variable redeclaration (checks if any false in the defVar)
            if (!Var(in,line)) {
                return false;
            }
            if (status) {
                // check if
                status = Decl(in, line);
                return status;
            } else {
                ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
                return false;
            }
        }
        else {
            //ParseError(line, "Missing Colon");
            return false;
        }
    }
    Parser::PushBackToken(t);
    return true;
}
// PrintStmt() evaluates the list of expressions [ExprList()], and prints their values in order from left to right | DOESNT ACTUALLY COUT
// Grammar Rule | PrintStmt := PRINT, ExprList     | function calls ExprList()
// Checks the returned value. If it returns false, an error message is printed such as: "Missing expression after print" then returns a false value
// Evaluation: the function prints out the list of expressions' values, and returns successfully.
bool PrintStmt(istream& in, int& line) {
    // Check for coma
    LexItem t = Parser::GetNextToken(in, line);
    if ((t.GetToken()  != COMA)) {
        ParseError(line, "Missing a Comma");
        return false;
    }

    // now check for EXPRLIST = Expr{,Expr}
    bool ex = ExprList(in, line);
    if (!ex) {
        ParseError(line, "Missing expression after print");
        return false;
    }
    // Evaluate: print out the list of expr values
    return ex;
}

// IfStmt() Evaluates a logical expression [LogicExpr()], to a Boolean value. If the expression value is true, then the block of statements are executed, otherwise it is not.
// Grammar Rule IF(LogicExpr)THEN{Stmt}ENDIF
bool IfStmt(istream& in, int& line) {

    //cout << "if\n";
    bool ifstmt;
    // IF was checked for already
    LexItem t = Parser::GetNextToken(in, line);
    // Check for LPAREN
    if (!(t.GetToken() == LPAREN)) {
        // then we leave
        ParseError(line, "Missing LPAREN keyword");
        return false;
    }

    ifstmt = LogicExpr(in, line);
    t = Parser::GetNextToken(in, line);
    if (!(t.GetToken() == RPAREN)) {
        // then we leave
        ParseError(line, "Missing RPAREN keyword");
        return false;
    }

    // now check for then
    t = Parser::GetNextToken(in, line);
    if (!(t.GetToken() == THEN)) {
        // then we leave
        ParseError(line, "Missing THEN keyword");
        return false;
    }

    //t = Parser::GetNextToken(in, line);
    // Now check for RPAREN


    // Check for STMT recursively
    Stmt(in, line);

    // Now check for END
    t = Parser::GetNextToken(in, line);
    if (!(t.GetToken() == END)) {
        // then we leave
        ParseError(line, "Missing END keyword");
        return false;
    }
    // NOw check for IF
    t = Parser::GetNextToken(in, line);
    if (!(t.GetToken() == IF)) {
        // then we leave
        ParseError(line, "Missing IF keyword");
        return false;
    }

    return ifstmt;
}

// ReadStmt() initializes a list of variables with values entered from the standard input (keyboard). Type matching or compatibility of values to variables must be satisfied.
bool ReadStmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    if ((t.GetToken()  != COMA)) {
        ParseError(line, "Missing a Comma");
        return false;
    }
    bool var = VarList(in,line);
    if (!var) {
        ParseError(line, "Missing expression after print");
        return false;
    }

    return var;
}

// IdList takes an extra parameter for a LexItem object of type token for the identifiers list (for implementation of static semantics of variable type)
// Includes the passing of object variable lex item =- to be used to provide attribute for all the types of all the identifies to be identified in the symbol table,  a mapper used to to indicated all seen
bool IdList(istream& in, int& line, LexItem tok) {

    /*
    // tok came as a real, char, integer | this is to fix a bug
    if (((tok.GetToken() == CHAR || tok.GetToken() == REAL || tok.GetToken() == INTEGER ) )) {
        Parser::PushBackToken(tok);
    }
    */

    // Its a INTEGER, REAL, or CHAR and we can find that by doing tok.GetToken();
    Token type = tok.GetToken();
    LexItem idTok;
    // Get the next identifier
    idTok = Parser::GetNextToken(in, line);

    while (  ((idTok.GetToken() != CHAR || idTok.GetToken() != REAL || idTok.GetToken() != INTEGER ) ) ){
        // Check if the token is a coma. If it is, get the next token and check if it an identifier. If it is, let to pass.
        //commaTok = Parser::GetNextToken(in, line);

        // Check if the id is in the defVar map
        if ( defVar.find(idTok.GetLexeme()) == defVar.end() ) {
            if (idTok.GetLexeme() == "3") {
                ParseError(line, "Missing Variable");
                return false;
            }
            // not found; Add to the map | BOTH MAPS
            defVar.insert ( std::pair<string,bool>(idTok.GetLexeme(),true) );
            SymTable.insert( std::pair<string,Token>(idTok.GetLexeme(),type) );
        } else {
            // found, set the key's[idTok.GetLexeme()] value to false;?
            defVar[idTok.GetLexeme()] = false;
            varRedefinition++;
            //ParseError(line, "Variable Redefinition");
            //return false;
        }

        bool chFlag = true;
        // check if the next char is a comma or an \n
        do {
            in.get(ch);
            if ( ch == ',' ) {
                // The get next token.
                idTok = Parser::GetNextToken(in, line);
                break;
                // Skips ' ' and  '\t'
            } else if ( ch == ' ' || ch == '\t') {
                while (ch == ' ' || ch == '\t') {
                    // get the next character
                    in.get(ch);
                }
                in.putback(ch);

                /*
                    do {
                        // THIS IS A HUGE BUG, REFACTOR THIS WITH A BETTER STRATEGY YO..
                        // Check if the char is a variable in defVar;
                        in.get(ch);
                        if (defVar.find(to_string(toupper(ch))) == defVar.end()) {
                            // found
                            in.putback(ch);
                            chFlag = false;
                            break;
                        }
               // } while (!(ch == ' ' || (ch == '\n') || (ch == '\t')));
                 */
            } else if ( ch == '\n' ) {
                // Then it is a line break, we must end.
                // putback \n
                in.putback(ch);
                return true;
            }
            else {
                //error
                ParseError(line, "Undeclared Variable");
                return false;
            }
        } while(true && chFlag);

    } // END OF WHILE LOOP
    // If type is not what it previously was AND

    // Push back the CHAR/INTEGER/REAL/ token
    Parser::PushBackToken(idTok);

    //while(LexItem idTok = Parser::GetNextToken(in, line);)

    //defVar.insert ( std::pair<string,bool>('a',100) );

    return false;
}

// Function for semenatics are difefernt, relying on existing identifiers that are provided with attributes. Already been seens in delcaration statements
bool VarList(istream& in, int& line) {
    bool varlist = true;
    //LexItem t = Parser::GetNextToken(in, line);

    // call Var
    if (!(Var(in, line))) {
        return false;
    }

    LexItem t = Parser::GetNextToken(in, line);

    // First check for IDENT
    if (t.GetToken() == IDENT) {
        // now check for comma, if no comma, return
        t = Parser::GetNextToken(in, line);
        if (t.GetToken() == COMA) {
            //call varlist again
            varlist = VarList(in,line);
        } else {
            Parser::PushBackToken(t);
            return varlist;
        }
    } else {
        // error
        ParseError(line, "NO IDENT AFTER READ STATEMNET");
        return false;
    }

    /*
    // if coma, call var again, else return
    if (t.GetToken() == COMA) {
        // then recursion
        varlist = Var(in, line);
    } else if (t.GetToken() == IDENT) {
        //then theres another thing in the var list

    } else {
        // put back the non coma
        Parser::PushBackToken(t);
        return true;
    }
    */

    return varlist;
}

// Var() - All variables have to be declared in declaration statements | Checks if any values in the map are false
bool Var(istream& in, int& line) {



    if (varFlag) {
        LexItem idTok = Parser::GetNextToken(in,line);
        // Check if the id is in the defVar map
        if ( defVar.find(idTok.GetLexeme()) == defVar.end() ) {
            // not found; ERROR, variable was not declared.
            ParseError(line, "Undeclared Variable");
            return false;
        } else {
            // found, put back the token
            Parser::PushBackToken(idTok);
        }
    }

    // check if variable exisis before its declared dont forget to put it back

    //const bool value = false;
    //std::copy_if(defVar.begin(), defVar.end(), std::inserter(defVarMatching, defVarMatching.end()), [value](const bool& v) {return v.second == value; });
    //std::copy_if(defVar.begin(), defVar.end(), std::inserter(defVarMatching, defVarMatching.end()), [value](const auto& v) {return v.second == value; });
    if (varRedefinition != 0) { // then its 1 or more
        ParseError(line, "Variable Redefinition");
        return false;
    }
    return true;

    /*
    if (t.GetToken() == IDENT) {
        if (defVar.find(t.GetLexeme()) == defVar.end()) {
            // not found
            ParseError(line, "Variable Redefinition");
            return false;
        } else {
            // found
            return true;
        }
    }
     */

}

// AssignStmt() The assignment statement [AssignStmt()] assigns a numeric value to a variable of a numeric type. For example, an integer variable can be assigned
// a real value, and a real variable can be assigned an integer value. In either case, conversion of the value to the type of variable must be applied.
// ERROR - A char variable can be assigned a string literal. It is an error to assign a numeric variable a non-numeric value.
// ERROR - It is an error to use a variable in an expression before it have been assigned.
bool AssignStmt(istream& in, int& line) {

   // cout << "assign\n";

    bool assignstmt;

    // Ident was checked in the prev function call, so check for equal

    // kill the l paren

    assignstmt = Var(in,line);
    if (!assignstmt) {
        // then bad left side
        ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
    }

    LexItem t = Parser::GetNextToken(in, line);
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() == ASSOP) {

    } else {
        ParseError(line, "Missing Equal Sign");
        return false;
    }


    // if left parenth, then we need a right one too. RIGHT?!??!

    assignstmt = Expr(in,line);

    t = Parser::GetNextToken(in, line);
    if (t.GetToken() == MULT || t.GetToken() == DIV) {
        assignstmt = Expr(in,line);
    } else {
        Parser::PushBackToken(t);
    }

    // check for more * or /

    /*

    t = Parser::GetNextToken(in, line);
    if ((t.GetToken() == LPAREN)) {
        assignstmt = Expr(in,line);
        // NOW CHECK FOR RIGHT
        t = Parser::GetNextToken(in, line);
        if ((t.GetToken() == RPAREN)) {
            // do nothing, nice
        } else {
            // ERROR MISSING RPAREN
            ParseError(line, "Missing RPAREN Sign");
            return false;
        }
    } else {
        // NO LEFT PARENTH, JUST CHECK FOR EXPRESSION
        Parser::PushBackToken(t);
        assignstmt = Expr(in,line);
    }

     */
    // check till the end of assignment statement

    return assignstmt;
}

// Function for
bool ExprList(istream& in, int& line) {
    bool status = true;
    // Get the first IDENT
    LexItem t = Parser::GetNextToken(in, line);
    // Its a ICONST, RCONST, SCONST
    if (t.GetToken() == SCONST || t.GetToken() == ICONST || t.GetToken() == RCONST) {
        switch (t.GetToken()) {
            case SCONST:
                Parser::PushBackToken(t);
                status = Expr(in, line);
                break;
            case ICONST:
                Parser::PushBackToken(t);
                status = Expr(in, line);
                break;
            case RCONST:
                Parser::PushBackToken(t);
                status = Expr(in, line);
                break;
        }
    } else if (t.GetToken() == IDENT) {
        if ( defVar.find(t.GetLexeme()) == defVar.end() ) {
            // not found
            ParseError(line, "Variable not declared");
            return false;
        } else {
            // found, putback the token for Expr()
            Parser::PushBackToken(t);
            status = Expr(in, line);
        }
    } else if (t.GetToken() == MINUS || t.GetToken() == PLUS){
        // put it back and check status
        Parser::PushBackToken(t);
        status = Expr(in, line);
    } else {
        // Some parse error, who knows
        ParseError(line, "Some parse error?? In ExprList()");
        return false;
    }

    // check for the comma yo | If therse a comma, check for another statement
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() == COMA) {
        // then recursion
        status = ExprList(in, line);
    } else {
        // put back the non coma
        Parser::PushBackToken(t);
        return status;
    }
    return status;
}

// LogicalExpr() - A Logical Expressions is defined by the two relational operators EQUAL (==), and LTHAN (<). The EQUAL and LTHAN relational operators
// operate upon TWO COMPATIBLE OPERANDS. The evaluation of a logical expression produces either a true or false value that controls whether the statement(s)
// of the selection IfStmt is executed or not.
// Grammar Rule | LogicExpr = Expr (==|<) Expr
bool LogicExpr(istream& in, int& line) {
    bool logicexpr;

    //check expr
    logicexpr = Expr(in , line);

    if (!(logicexpr)) {
        return logicexpr;
    }
    // check == | <
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == EQUAL | t.GetToken() == LTHAN) {
        // good
    } else {
        // missing ERROR
        ParseError(line, "Missing == or <");
        return false;
    }

    //check expr
    logicexpr = Expr(in , line);
    if (!(logicexpr)) {
        return logicexpr;
    }

    return logicexpr;
}

// Grammar Rule Expr = Term {(+|-)Term}
bool Expr(istream& in, int& line) {
    bool expr;
    Token type;
    LexItem t = Parser::GetNextToken(in, line);
    // CHECK FOR LPAREN FIRST

    if (t.GetToken() == LPAREN || t.GetToken() ==  RPAREN) {
        t = Parser::GetNextToken(in, line);
    } else {
        // put it back man
        Parser::PushBackToken(t);
    }

        // Check for Term
        expr = Term(in, line);
        if (!expr) {
            ParseError(line,"Missing Expression");
            return false;
        }

        // check for unrecchar

        t = Parser::GetNextToken(in, line);
        // Check for + or -
        if (t.GetToken() == MINUS || t.GetToken() == PLUS) {
            if (expr) {
                // check if
                expr = Term(in, line);
                return expr;
            }
        } else {
            // not + or -, so no other terms
            //LexItem t = Parser::GetNextToken(in, line);
            Parser::PushBackToken(t);
            return expr;
        }
        return expr;
}

// Grammar Rule | Term = SFactor{(*|/)SFactor}
bool Term(istream& in, int& line){
    bool term;
    //LexItem t = Parser::GetNextToken(in, line);
    // Check for SFactor

    // check for $
    in.get(ch);
    if (ch == '$'){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    } else {
        in.putback(ch);
    }

        term = SFactor(in, line);

        // Check for *|/
        LexItem t = Parser::GetNextToken(in, line);
        if (t.GetToken() == MULT || t.GetToken() == DIV) {
            // Then call SFactor Again
            if (term) {
                // check if
                term = SFactor(in, line);
                return term;
            }
        } else {
            // NOT SURE ABOUT THIS ONE CHIEF Probably an Ident or STMT
            Parser::PushBackToken(t);
            if (term) {
                // check if not a STMT
                if (!(t.GetToken() == MULT || t.GetToken() == DIV)) {
                    // break out
                    return true;
                }

                term = SFactor(in, line);
                // Parser::PushBackToken(t);
                return term;
            }
        }
        return term;

}

// Function for
bool SFactor(istream& in, int& line) {
    bool sfactor;

    // Check for the sign
    LexItem t = Parser::GetNextToken(in, line);

    if (t.GetToken() == MINUS || t.GetToken() == PLUS)  {
        // then the sign operator is good, now get a factor
        switch(t.GetToken()) {
            case MINUS:
                sfactor = Factor(in, line, -1);
                break;
            case PLUS:
                sfactor = Factor(in, line, 1);
                break;
            default:
                sfactor = Factor(in, line, 0);
        }
    } else {
        // Well then, its just a plain old factor (0)
        // Putback the token because its not + or -
        Parser::PushBackToken(t);
        sfactor = Factor(in, line, 0);
    }

    return sfactor;
}

// Factor function takes an extra parameter for the passed sign operator ( +, -, null) AS (1, -1, 0) respectively.
bool Factor(istream& in, int& line, int sign) {
    bool factor = false;
    // Check for IDENT, to see if its in the map.

    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == SCONST || t.GetToken() == ICONST || t.GetToken() == RCONST) {
        switch (t.GetToken()) {
            case SCONST:
                factor = true;
                // Check if the next token as an arithmetic operation on the string. If so, return ERROR BOY dont actually have to check
                return factor;
                break;
            case ICONST:
                factor = true;
                return factor;
                break;
            case RCONST:
                factor = true;
                return factor;
                break;
        }
    } else if (t.GetToken() == IDENT) {
        if ( defVar.find(t.GetLexeme()) == defVar.end() ) {
            // not found
            ParseError(line, "Variable not declared");
            return false;
        } else {
            // found
            factor = true;
        }
    } else {
        // left and right PARENTH
        factor = Expr(in, line);
    }

    // If factor is false, then UHH ?
    if (!factor) {
        // Some parse error, who knows
        ParseError(line, "Some parse error?? In ExprList()");
        return false;
    }

    return factor;
}
