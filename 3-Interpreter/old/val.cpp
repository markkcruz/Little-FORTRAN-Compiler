
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

/*
 * Description of the Language
 *
 *
 */


#include "val.h"



// There is a need to
// add this with op 
    Value Value::operator+(const Value& op) const {
        // If the current type of this object is matching exactly the type of the operant
        if( GetType() == op.GetType() )
        {
            // If both integers, add both int temp with the value maintained in the operator object.
        	if( IsInt() ) return Value( Itemp + op.GetInt() );
        	// If real, do the same
        	if( IsReal() ) return Value( Rtemp  + op.GetReal() );
		}
        // Checks if the object value is an integer and that operand is a real
		else if(IsInt() && op.IsReal())
		{
			// Perform the integer by casting the integer into float and returns the objet Value
			return Value( (float) GetInt() + op.GetReal());
		}
		// Check if its real and the value of operand is integer, then cast converstion int to float and return the value.
		else if(IsReal() && op.IsInt())
		{
			return Value(GetReal() + (float) op.GetInt());
		}
		// Any other case output will return the value of an ERROR.
		return Value();
		
    }
    
    // subtract op from this
    Value Value::operator-(const Value& op) const {
        if( GetType() == op.GetType() )
        {
        	if( IsInt() ) return Value( Itemp - op.GetInt() );
        	if( IsReal() ) return Value( Rtemp - op.GetReal() );
		}
		else if(IsInt() && op.IsReal())
		{
			
			return Value( (float) GetInt() - op.GetReal());
		}
		else if(IsReal() && op.IsInt())
		{
			return Value(GetReal() - (float) op.GetInt());
		}
		// ERROR
		return Value();
		
    }
    
    // multiply this with op
    Value Value::operator*(const Value& op) const {
        if( GetType() == op.GetType() )
        {
        	if( IsInt() ) return Value( Itemp * op.GetInt() );
        	if( IsReal() ) return Value( Rtemp * op.GetReal() );
		}
		else if(IsInt() && op.IsReal())
		{
			
			return Value( (float) GetInt() * op.GetReal());
		}
		else if(IsReal() && op.IsInt())
		{
			return Value(GetReal() * (float) op.GetInt());
		}
		// ERROR
		return Value();
		
    }
    
    // divide this by op
    Value Value::operator/(const Value& op) const {
        if( GetType() == op.GetType() )
        {
        	if( IsInt() ) return Value( Itemp / op.GetInt() );
        	if( IsReal() ) return Value( Rtemp / op.GetReal() );
		}
		else if(IsInt() && op.IsReal())
		{
			
			return Value( (float) GetInt() / op.GetReal());
		}
		else if(IsReal() && op.IsInt())
		{
			return Value(GetReal() / ((float) op.GetInt()));
		}
		// ERROR
		return Value();
		
    }


    // Comparison. If the get type of the current object compared to the operand passed to it are equal.
    // With the relational operators, stirng comparisons are included | if stirng or char, they are both variables.
    Value Value::operator==(const Value& op) const {
        if( GetType() == op.GetType() )
        {
            // INT, returns the integer value. Casts into a bool just to make sure you are not using the interpretation of c-like
        	if( IsInt() ) return Value( (bool)(Itemp == op.GetInt() ));
        	if( IsReal() ) return Value( (bool) (Rtemp == op.GetReal() ));
        	if( IsChar()) return Value( (bool) (Stemp < op.GetChar()));
		}
        // If int of object is an int and the operand is a real, then we make a conversion of int to real in order to make a comparison
		else if(IsInt() && op.IsReal())
		{
			
			return Value( (bool) (((float) GetInt())== op.GetReal()));
		}
		// Vice versa of above
		else if(IsReal() && op.IsInt())
		{
			return Value( (bool) (GetReal() == ((float) op.GetInt())));
		}
		
		return Value();
		
    }
    
    Value Value::operator<(const Value& op) const {
        if( GetType() == op.GetType() )
        {
        	if( IsInt() ) return Value( Itemp < op.GetInt() );
        	if( IsReal() ) return Value( Rtemp < op.GetReal() );
        	if( IsChar()) return Value( Stemp < op.GetChar());
		}
		else if(IsInt() && op.IsReal())
		{
			
			return Value( ((float) GetInt()) < op.GetReal());
		}
		else if(IsReal() && op.IsInt())
		{
			return Value(GetReal() < ((float) op.GetInt()));
		}
		
		return Value();
		
    }




    // PrintStmt := print ExprList (funciton calls ExprList()
    // Checks the returned value, if it returns false an error message is printed such as "Missing expression after print" Then the PrintStmt function returns false value
    // Evaluation: the funciton prints out the list of expression's values an returns successfully
    // Proviedes the checking of what the expression lists.
    bool PrintStmt(istream& in, int& line) {
        /*create an empty queue of Value objects.*/
        // Each time you need a print statemnet, a queue is created.
        ValQue = new queue<Value>;

        bool ex = ExprList(in, line);
        if (!ex) {
            ParseError(line, "Missing expression after print");
            // Empty the queue and delete.
            while(!(*ValQue).empty()) {
                ValQue -> pop();
            }
            delete ValQue;
            return false;
        }

        // Evaluate: print out the list of expressions' values
        LexItem t = Parser:: GetNextToken(in, line);


    }
