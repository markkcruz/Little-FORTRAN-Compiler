#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "lex.h"


/*
 * CS280 - Spring 2021
 */

#include <cctype>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{


    // --Main Variables for iofstream--=
    ifstream finObj;
    //fstream finObj2; // used for finding , and ! tokens
    string file_name; // Name of file we are working with. Either from argv[1] or cin (Case 3).
    string line; //temp string that store the value of each line


    // Core variables
    int lineNum = 0;
    int tokensNum = 0;
    //int tokenNumPlus = 0;
    //bool touchMe = false; // This means that the getNextToken was never called yo
    //LexItem tok;
    LexItem t;
    // --Mapped Variables--
    vector<int> intVec; // For ints (5)
    vector <string> sConstVec; // For Strings ("Hello")
    vector <string> rConstVec; // For Reals (34.5)
    vector <string> idenVec; // Identifiers ONLY (CIRCLE, A, ETC....)

    //bool errorPrinter = false; // if this is true, then we print the error statement
    vector <string> identKeyWord;



    // idtoks LexItem, (token, lexeme, line) // LexItem(IDENT,"PRINT",3),

    /*
    LexItem idtoks[] = {

    };

    // toks LexItem, (token, lexeme, line) // (END,"END",15),
    LexItem toks[] = {

    };
     */

    // Check if no file name was given (test case 3)

    if (argc == 1) {
        cout << "No Specified Input File Name." << endl;
        return 0;
    }

    // bools for keeping track of flags

    // bool
    // Flag Checker ( -v -iconsts -rconsts -sconsts -ids ) 0
    /*
    vector<string>
    int elem = 42;
    std::vector<string> vectorFlags;
    vectorFlags.push_back("-v");
    vectorFlags.push_back("-iconsts");
    vectorFlags.push_back("-rconsts");
    vectorFlags.push_back("-sconsts");
    vectorFlags.push_back("-ids");
    */

    bool _allFlags = false;
    bool _v = false;
    bool _vALL = false;

    bool _iconsts = false;
    bool _rconsts = false;
    bool _sconsts = false;
    bool _ids = false;
    // Iterate through agrv[]
    for (int i = 1; i < argc; i++) {
        string argTester = argv[i];
        if (argTester == "-v") {
            _v = true;
        } else if (argTester == "-iconsts") {
            _iconsts = true;
        } else if (argTester == "-rconsts") {
            _rconsts = true;
        } else if (argTester == "-sconsts") {
            _sconsts = true;
        } else if (argTester == "-ids") {
            _ids = true;
        } else if (argTester[0] == '-') {
            // Invalid Flag
            cout << "UNRECOGNIZED FLAG -icons" << endl;
            exit(0);
        } //else {
            // Another File Detected
            //cout << "No Specified Input File Name." << endl;
            //return 0;
        //}
    }

    if (_vALL || _iconsts || _rconsts || _sconsts || _ids) {
        // do nothing
        // this is for vorc to run this program....
    }

    // Checks if all 4 flags are true, then -v is true also...

    if (_iconsts && _rconsts && _sconsts && _ids ) {
        _allFlags = true;
    }



    // collecting flags
    //


    // Check if there are only 2 or more arguments
    if (argc >= 2) {
        file_name = argv[1]; //argv[1] "infile4" // Set string to the name of the filename, which is argv[1]
        finObj.open(file_name); // Open the file with the istream object finObj
        // Check if the file is open
        if (finObj.is_open())
            //in = &finObj;
            ;
        else {
            cout << "CANNOT OPEN THE FILE " << file_name << endl;
            exit(1);
        }
        //Do EVERYTHING here.


        /*
        // This is for finding commas    DOESNT WORK IN VORC
        finObj2.open(file_name);

        bool commentChar = false;
        bool commaChar = false;
        char toker;
        while (finObj2 >> noskipws >> toker) {
            if (toker == '!')
                commentChar = true;
            if (toker == ',')
                commaChar = true;
        }

        if (commentChar) {
            tokensNum++;
        }
        if (commaChar) {
            tokensNum++;
        }

         */












        while (  ((t = getNextToken(finObj, lineNum)).GetToken() != DONE && t.GetToken() != ERR ) ){

            tokensNum++;
            //lineNum;

            if (t.GetLexeme() == ",") {
                continue;
            }

            // REAL CONST Vector operations
            if (t.GetToken() == RCONST) {
                rConstVec.push_back(t.GetLexeme());
            }

            // INTEGER CONST Vector operations
            if (t.GetToken() == ICONST) {
                intVec.push_back( stoi(t.GetLexeme())); // get lexeme string, convert to int, then push to vector
            }

            // IDS CONST Vector Operations
            if (t.GetToken() == IDENT) {
                idenVec.push_back(t.GetLexeme());
            }

            // String CONST Vector Operations
            if (t.GetToken() == SCONST) {

                // Before we push onto the stack, we have to remove the " " or ' ' at the end and at the start
                string truncatedLexeme = t.GetLexeme();

                truncatedLexeme = truncatedLexeme.substr(1, truncatedLexeme.size() - 1); // killed first and last
                // now push it onto the vector lol
                sConstVec.push_back(truncatedLexeme);
            }

            // for -v flag
            if (t.GetToken() == IDENT || t.GetToken() == PROGRAM || t.GetToken() == PRINT || t.GetToken() == READ || t.GetToken() == INTEGER || t.GetToken() == END || t.GetToken() == IF || t.GetToken() == THEN || t.GetToken() == REAL || t.GetToken() == CHAR) {
                if (t.GetToken() == IDENT) {
                    // its an ident, so push the string IDENT(t.GetLexeme)
                    string test = "IDENT(" + t.GetLexeme() + ")";
                    identKeyWord.push_back(test);
                } else {
                    // Then its a keyword. so just push it boy
                    identKeyWord.push_back(tokenPrint[t.GetToken()]);
                }
            }



            // KEYWORD Vector Operations



            // do stuff with t;


            // error printer

            //if ()

        }











        // Close the file after it was successfuly read.
        finObj.close();
        //finObj2.close();
    } else {
        cout << "CANNOT OPEN THE FILE " << file_name << endl;
        return 0;
    }





    // CODE FOR MAIN LOOP DRIVER _______________________________________________________________

    /*
    LexItem t;
    while (  ((t = getNextToken(finObj, lineNum)).GetToken() != DONE && t.GetToken() != ERR ) ){
        tokensNum++;
        if (t.GetToken() == ICONST) {
            intVec.push_back(t.GetLexeme());
        }
        // do stuff with t;
    }

     */

















    /*
    LexItem	tok;
    LexItem kwtok;
    LexItem idtoks[] = {
            LexItem(IDENT,"PRINT",3),
            LexItem(IDENT,"circle",3),
            LexItem(IDENT,"square",11),
            LexItem(IDENT,"rectangle",12),
            LexItem(IDENT,"ellipse",14),
            LexItem(IDENT, "PROGRAM", 1),
            LexItem(IDENT, "READ", 8),
            LexItem(IDENT, "INTEGER",2),
            LexItem(IDENT, "REAL",3),
            LexItem(IDENT, "CHAR",4),
            LexItem(IDENT, "IF", 5),
            LexItem(IDENT, "THEN", 5),
            LexItem(IDENT, "END", 0)
    };
    LexItem toks[] = {
            LexItem(END,"END",15),

            LexItem(ICONST,"579",5),
            LexItem(SCONST,"hello NJIT",6),
            LexItem(RCONST,"5.79",7),
            LexItem(PLUS,"+",3),
            LexItem(MINUS,"-",3),
            LexItem(MULT,"*",3),
            LexItem(DIV,"/",3),
            LexItem(ASSOP,"=",3),
            LexItem(LPAREN,"(",3),
            LexItem(RPAREN,")",3),
            LexItem(COLON,":",3),
            LexItem(COMA,",",3),
            LexItem(COMA,",",3),
            LexItem( EQUAL, "EQUAL", 4),
            LexItem( LTHAN, "LTHAN", 4 ),
            LexItem( CONCAT, "CONCAT", 6 ),
            LexItem(ERR, "ERR", 3),
            LexItem(DONE,"DONE",3),
    };
    */


    /*
    bool idsflag = false;
    bool tokflag = false;
    int i;

    if (argc == 1)
    {
        cerr << "No Specified arguments." << endl;
        return 0;
    }
    for( int i=1; i<argc; i++ ) {
        string arg( argv[i] );
        if( arg == "-idsonly" )
            idsflag = true;
        else if( arg == "-othertok" )
            tokflag = true;
        else if( arg[0] == '-' ) {
            cerr << "UNRECOGNIZED FLAG " << arg << endl;
            return 0;
        }
    }
    if(idsflag)
    {

        cout << "Identifiers and Keywords:" << endl;
        for( i = 0; idtoks[i].GetLexeme() != "END"; i++ )
        {
            kwtok = id_or_kw(idtoks[i].GetLexeme(), toks[i].GetLinenum());
            cout << kwtok;
        }
        kwtok = id_or_kw(idtoks[i].GetLexeme(), toks[i].GetLinenum());
        cout << kwtok;
    }
    if(tokflag)
    {
        cout << "Other tokens:" << endl;
        for( i = 0; toks[i] != DONE; i++ )
        {
            cout << toks[i];
        }
        cout << toks[i];
    }

    */




    // Check for errors
    // ERROR CASE for strings
    if (t.GetToken() == ERR && t.GetLinenum() != -1 && isalpha(t.GetLexeme()[0]) ) {

        cout << "Error in line " << t.GetLinenum() + 1 << " (\"" << t.GetLexeme() << ")" << endl;
        exit(0);
    }

    // ERROR case for EVERYTHING ELSE lol
    if (t.GetToken() == ERR && t.GetLinenum() != -1) {
        cout << "Error in line " << t.GetLinenum() + 1 << " (" << t.GetLexeme() << ")" << endl;
        exit(0);
    }

    // Final Output
    // First line of output
    cout << "Lines: " << lineNum << endl;
    if (lineNum != 0) {
        cout << "Tokens: " << tokensNum << endl;
    }

    // Need control flow by checking if the flags exist
    if (_v) {
        // print all of the tokens
        return 0;
    }
    if (_allFlags) {
        cout << "STRINGS:" << endl;
        sort(sConstVec.begin(), sConstVec.end()); // Sort the vector
        sConstVec.erase( unique( sConstVec.begin(), sConstVec.end() ), sConstVec.end() ); // Erase Duplicates
        for(auto & i : sConstVec) // Now print it out
            std::cout << i << endl;


        cout << "INTEGERS:" << endl;
        sort(intVec.begin(), intVec.end()); // Sort the vector
        intVec.erase( unique( intVec.begin(), intVec.end() ), intVec.end() ); // Erase Duplicates
        for(auto & i : intVec) // Now print it out
            std::cout << i << endl;



        cout << "REALS:" << endl;
        sort(rConstVec.begin(), rConstVec.end()); // Sort the vector
        rConstVec.erase( unique( rConstVec.begin(), rConstVec.end() ), rConstVec.end() ); // Erase Duplicates
        for(auto & i : rConstVec) // Now print it out
            std::cout << i << endl;


        cout << "IDENTIFIERS:" << endl;
        sort(idenVec.begin(), idenVec.end()); // Sort the vector
        idenVec.erase( unique( idenVec.begin(), idenVec.end() ), idenVec.end() ); // Erase Duplicates
        int j = 0;
        for(auto & i : idenVec) { // Now print it out
            cout << i;
            j++;
            if (j != (idenVec.size())) {
                cout << ", ";
            }
        }
        cout << endl;

        return 0;
    }

    if (_sconsts) {
        cout << "STRINGS:" << endl;
        sort(sConstVec.begin(), sConstVec.end()); // Sort the vector
        sConstVec.erase( unique( sConstVec.begin(), sConstVec.end() ), sConstVec.end() ); // Erase Duplicates
        for(auto & i : sConstVec) // Now print it out
            std::cout << i << endl;
        return 0;

        return 0;
    }

    if (_rconsts) {
        cout << "REALS:" << endl;
        sort(rConstVec.begin(), rConstVec.end()); // Sort the vector
        rConstVec.erase( unique( rConstVec.begin(), rConstVec.end() ), rConstVec.end() ); // Erase Duplicates
        for(auto & i : rConstVec) // Now print it out
            std::cout << i << endl;
        return 0;
        return 0;
    }

    if (_iconsts) {
        cout << "INTEGERS:" << endl;
        sort(intVec.begin(), intVec.end()); // Sort the vector
        intVec.erase( unique( intVec.begin(), intVec.end() ), intVec.end() ); // Erase Duplicates
        for(auto & i : intVec) // Now print it out
            std::cout << i << endl;
        return 0;
    }

    if (_ids) {
        cout << "IDENTIFIERS:" << endl;
        sort(idenVec.begin(), idenVec.end()); // Sort the vector
        idenVec.erase( unique( idenVec.begin(), idenVec.end() ), idenVec.end() ); // Erase Duplicates
        int j = 0;
        for(auto & i : idenVec) { // Now print it out
            cout << i;
            j++;
            if (j != (idenVec.size())) {
                cout << ", ";
            }
        }
        cout << endl;
        return 0;
    }


    return 0;
}


// Helpers










lex.ppp

//
// Created by Jinrain on 2/27/2021.
//
#include "lex.h"
#include <string>
#include <cctype>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>


/*
 * The first argument to getNextToken is a reference to an istream object that the function should read from. The second argument
 * to getNextToken is a reference to an integer that contains the current line number. getNextToken should update this integer
 * every time it reads a newline from the input stream. getNextToken returns a LexItem object. A LexItem is a class that contains
 * a token, a string for the lexeme, and the line number as data members.
 * A header file, lex.h, is provided for you. It contains a definition of the LexItem class, and a definition of an enumerated
 * type of token symbols, called Token. You MUST use the header file that is provided. You may NOT change it.
 *
 * Note that the getNextToken function performs the following:
 *
 * 1. Any error detected by the lexical analyzer should result in a LexItem object to be returned with the ERR token,
 * and the lexeme value equal to the string recognized when the error was detected.
 * _______
 * 2. Note also that both ERR and DONE are unrecoverable. Once the getNextToken function returns a LexItem object for
 * either of these tokens, you shouldn’t call getNextToken again.
 * _______
 * 3. Tokens may be separated by spaces, but in most cases are not required to be. For example, the input characters “3+7”
 * and the input characters “3 + 7” will both result in the sequence of tokens ICONST PLUS ICONST. Similarly, The input characters
 *
 * “Hello” “World”, and the input characters “Hello””World”
 * will both result in the token sequence SCONST SCONST.
 *
 */


LexItem getNextToken (istream& in, int& linenumber) {
    enum TokStates {START, INID, INSTRING, ININT, INREAL, INCOMMENT, INPOSSIBLEREAL, INSINGLESTRING, INDOUBLESTRING};
    LexItem output;
    TokStates lexstate = START;
    //Token token;
    string lexeme;
    char ch;
       while (in.get(ch)) {
        switch (lexstate) {
            case START:
                if (ch == '\n')
                    linenumber++;
                if (isspace(ch)) {
                    break;
                }
                // Special Chars
                if (ch == '+' || ch == '-' || ch == '*' || ch == '(' || ch == ')' ||ch == '<' || ch == ':' || ch == ',') {
                    if (ch == '+') {
                        return LexItem(PLUS, lexeme, linenumber);
                    }
                    if (ch == '-') {
                        return LexItem(MINUS, lexeme, linenumber);
                    }
                    if (ch == '*') {
                        return LexItem(MULT, lexeme, linenumber);
                    }
                    if (ch == '(') {
                        return LexItem(LPAREN, lexeme, linenumber);
                    }
                    if (ch == ')') {
                        return LexItem(RPAREN, lexeme, linenumber);
                    }
                    if (ch == '<') {
                        return LexItem(LTHAN, lexeme, linenumber);
                    }
                    if (ch == ':') {
                        return LexItem(COLON, lexeme, linenumber);
                    }
                    if (ch == ',') {
                        return LexItem(COMA, lexeme, linenumber);
                    }
                }
                if (ch == '/') {
                    // Get next Char
                    in.get(ch);
                    if (ch == '/') {
                        //concat
                        return LexItem(CONCAT, lexeme, linenumber);
                    } else {
                        in.putback(ch);
                        return LexItem(DIV, lexeme, linenumber);
                    }
                }

                if (ch == '=') {
                    // Get next Char
                    in.get(ch);
                    if (ch == '=') {
                        //concat
                        return LexItem(ASSOP, lexeme, linenumber);
                    } else {
                        in.putback(ch);
                        return LexItem(EQUAL, lexeme, linenumber);
                    }
                }

                // ______________________________InComment (lexstate: INCOMMENT) _______________________________
                if (ch == '!') {
                    lexstate = INCOMMENT;
                    in.get(ch);
                    while (ch != '\n') {
                        in.get(ch);
                    }
                    if (ch == '\n') {
                        lexstate = START;
                       linenumber++;
                        break;
                    } else {
                        lexstate = START;
                        linenumber++;
                        break;
                    }
                }
                // ______________________________InComment (lexstate: INCOMMENT) _______________________________

                // Digits and Reals
                if (isdigit(ch)) {
                    lexstate = ININT;
                    lexeme += string(&ch, 1);
                    continue;
                }

                // CHECK FOR REALS
                if (ch == '.') {
                    lexstate = INREAL;
                    lexeme += string("0");
                    lexeme += string(&ch, 1);
                }
                // Check for alphabet chars [a-z][A-Z]
                if (isalpha(ch)) {
                    lexstate = INID;
                    lexeme += ch;
                    continue;
                }

                // Check for Strings, INSINGLESTRING
                if (ch == '\'' ) {
                    lexstate = INSINGLESTRING;
                    lexeme += string(&ch, 1);
                }

                // Check for Strings, INDOUBLESTRING
                if (ch == '\"' ) {
                    lexstate = INDOUBLESTRING;
                    lexeme += string(&ch, 1);
                }




                break;




            case INID:
                if (isalnum(ch)) {
                    lexeme += ch;
                    // check for comma
                    //ch comma; = cin.peek(comma);
                    break;
                } else if(ch == '\n') {
                    linenumber++;
                    return id_or_kw(lexeme, linenumber);
                } else {
                    if ( kwmap.find(lexeme) == kwmap.end() ) {
                        // If comma, put that back yo.... but lets not output it as a token or anything crazy like that
                        if (ch == ',') {
                            in.putback(',');
                            //linenumber++;
                            return id_or_kw(lexeme, linenumber);
                        }
                        // Not found. So not a keyword
                        return id_or_kw(lexeme, linenumber);
                    } else {
                        // Found, so its a keyword. Deal with it.
                    }
                    // Check for keywords
                    //
                    //
                    //
                    //
                    break;
                }

                break;
            case INSTRING:
                //some code
                break;
            case ININT:
                if (isdigit(ch)) {
                    lexeme += string(&ch, 1);
                } else if ((ch) == '.') {
                    lexstate = INPOSSIBLEREAL;
                    lexeme +=string(&ch, 1);
                    continue;
                } else {
                    // its a space or some other shit,
                    cin.putback(ch);
                    if (ch == '\n')
                        linenumber++;
                    return LexItem(ICONST, lexeme, linenumber);
                }
                break;



            case INPOSSIBLEREAL:
                if (isdigit(ch)) {
                    lexstate = INREAL;
                } else if (ch == ' ') {
                        // cant have whitespace after
                        cin.putback(ch);

                        // need to cut the period from (15.)
                        lexeme = lexeme.substr(0, lexeme.size()-1);

                        return LexItem(ERR, lexeme, linenumber);
                } else {
                    cin.putback(ch);
                    if (ch == '\n')
                        linenumber++;
                    return LexItem(ERR, lexeme, linenumber);
                }


            case INREAL:
                if (isdigit(ch)) {
                    lexeme += string(&ch, 1);
                } else {
                    cin.putback(ch);
                    if (ch == '\n') {
                        linenumber++;
                        return LexItem(RCONST, lexeme, linenumber);
                    }

                    if (ch == ' ') {
                        // its fine yo
                        ;
                    } else { //error, probably lol
                        return LexItem(ERR, lexeme, linenumber);
                    }

                    return LexItem(RCONST, lexeme, linenumber);
                }
                break;
            case INCOMMENT:
                //some code
                break;
            case INSINGLESTRING:
                if (ch == '\n') {
                    // ERROR
                    return LexItem(ERR, lexeme, linenumber);
                } else if (ch == '\'') {
                    return LexItem(SCONST, lexeme, linenumber);
                } else {
                    lexeme += string(&ch, 1);
                }
                break;
            case INDOUBLESTRING:
                if (ch == '\n') {
                    // ERROR
                    return LexItem(ERR, lexeme, linenumber);
                } else if (ch == '\"') {
                    return LexItem(SCONST, lexeme, linenumber);
                } else {
                    lexeme += string(&ch, 1);
                }
                break;
        }
    }




    return output;// LexItem Obj
}

LexItem id_or_kw(const string& lexeme, int linenum){
    //Token token;
    // Check if it is a registered keyword



    string lexemeUpper = lexeme;
    // Change to uppercase please
    std::transform(lexemeUpper.begin(),lexemeUpper.end(),lexemeUpper.begin(),::toupper); // Change string to uppercase
    if ( kwmap.find(lexemeUpper) == kwmap.end() ) {
        // not found SO its a IDEN
        return LexItem(IDENT, lexemeUpper, linenum);
    } else {
        // found, so its a KEYWORD
        return LexItem(kwmap[lexemeUpper], lexemeUpper, linenum);
    }



    /*
    switch(kwmap[lexeme]) {
        case PROGRAM :
            token = kwmap[lexeme];
            break;
        case READ :
            token = kwmap[lexeme];
            break;
        case INTEGER :
            token = kwmap[lexeme];
            break;
        case REAL :
            token = kwmap[lexeme];
            break;
        case CHAR :
            token = kwmap[lexeme];
            break;
        case PRINT :
            token = kwmap[lexeme];
            break;
        case IF :
            token = kwmap[lexeme];
            break;
        case THEN :
            token = kwmap[lexeme];
            break;
        case END :
            token = kwmap[lexeme];
            break;
        default : // Then its an Identifier
            token = IDENT;
    }

    // Its a Keyword
    if (token != IDENT) {
        return {token, lexeme, linenum};
    } else { // Its not a keyword
        return {IDENT, lexeme, linenum};
    }

     */
    return {IDENT, lexeme, linenum};
}

ostream& operator << (ostream& out, const LexItem& tok) {


    //out << tokenPrint[tok.GetToken()] << " (" << tok.GetLexeme() << ") " << "Line #: " << tok.GetLinenum() << std::endl;
    if (tokenPrint[tok.GetToken()] == "IDENT") {
        out << "IDENT " << "("<< tok.GetLexeme() << ") Line #: " << tok.GetLinenum() << std::endl;
    } else if(tokenPrint[tok.GetToken()] == "ERR") {
        out << tokenPrint[tok.GetToken()] << " ("<< tok.GetLexeme() << ") Line #: " << tok.GetLinenum() << std::endl;
    } else if (tokenPrint[tok.GetToken()] == "ICONST" || tokenPrint[tok.GetToken()] == "SCONST" || tokenPrint[tok.GetToken()] == "RCONST" ) {
        out << tokenPrint[tok.GetToken()] << " ("<< tok.GetLexeme() << ") Line #: " << tok.GetLinenum() << std::endl;
    } else {
        out << tokenPrint[tok.GetToken()] << " Line #: " << tok.GetLinenum() << std::endl;
    }
    return out;
}
