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
