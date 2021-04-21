/* Programming Assignment 4
 * 
 * main.cpp
 *
 * CS280 - Fall 2020
 * parser and interpreter testing program
 */

#include <iostream>
#include <fstream>

#include "lex.h"
#include "val.h"
#include "parserInt.h"


using namespace std;
//extern int error_count;

int main(int argc, char *argv[])
{
	int lineNumber = 1;

	istream *in = NULL;
	ifstream file;
		
	for( int i=1; i<argc; i++ )
    {
		string arg = argv[i];
		
		if( in != NULL ) 
        {
			cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
			return 0;
		}
		else 
        {
			file.open(arg.c_str());
			if( file.is_open() == false ) 
            {
				cerr << "CANNOT OPEN " << arg << endl;
				return 0;
			}

			in = &file;
		}
	}
    // If prog fails, the program should stop and display a message as unsucessful interpretation and display the number of errors detected.
    // If it succeeds, the prog stops and displays Successful Execution
    bool status = Prog(*in, lineNumber);
    
    if( !status ){
    	cout << "\nUnsuccessful Interpretation " << endl << "Number of Errors " << ErrCount()  << endl;
	}
	else{
		cout << "\nSuccessful Execution" << endl;
	}
}
