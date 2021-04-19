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
                //Check for that invalid char yo $$$
                if (ch == '$') {
                    lexeme += string(&ch, 1);
                    return LexItem(ERR, lexeme, linenumber);
                }
                if (ch == '\n')
                    linenumber++;
                if (isspace(ch) || ch == '\t') {
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
                    // Check next char. If its a digit, we good. If not. Dude, its an error yo
                    if (isdigit(in.peek())) { // this is good for bitcoin
                        lexstate = INREAL;
                        lexeme += string("0");
                        lexeme += string(&ch, 1);
                    } else {
                        lexeme += ch;
                        in.get(ch);
                        if (!(isdigit(ch))) {
                            lexeme += string(&ch, 1);
                            return LexItem(ERR, lexeme, linenumber);
                        }
                    }

                    /* old code jic i fuck it up
                                          lexeme += ch;
                    in.get(ch);
                    if (!(isdigit(ch))) {
                        lexeme += string(&ch, 1);
                        return LexItem(ERR, lexeme, linenumber);
                    }
                    lexstate = INREAL;
                    lexeme += string("0");
                    lexeme += string(&ch, 1);
                     */

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
                } else if (ch == '+' || ch == '-' || ch == '*' || ch == '(' || ch == ')' ||ch == '<' || ch == ':' || ch == ',' || ch == '.') {

                    in.putback(ch);
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
                        return id_or_kw(lexeme, linenumber);
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
                } else if (isalpha(ch) || ch == ')') {
                  // then x2 bs
                  in.putback(ch);
                  return LexItem(ICONST, lexeme, linenumber);
                } else if ((ch) == '.') {
                    lexstate = INPOSSIBLEREAL;
                    lexeme +=string(&ch, 1);
                    continue;
                } else {
                    // its a space or some other shit,

                    if (ch == '\n')
                        linenumber++;
                    return LexItem(ICONST, lexeme, linenumber);
                    in.putback(ch);
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
                    if (ch == '\n') {
                        linenumber++;
                        return LexItem(RCONST, lexeme, linenumber);
                    }

                    if (ch == ' ') {
                        // its fine yo
                        ;
                    } else if (ch == ')') {
                        // its fine yo, put end it and putback the ) dude...
                        in.putback(ch);
                        return LexItem(RCONST, lexeme, linenumber);
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
