
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

#include "val.h"




// add this with op 
    Value Value::operator+(const Value& op) const {
        if( GetType() == op.GetType() )
        {
        	if( IsInt() ) return Value( Itemp + op.GetInt() );
        	if( IsReal() ) return Value( Rtemp + op.GetReal() );
		}
		else if(IsInt() && op.IsReal())
		{
			
			return Value( (float) GetInt() + op.GetReal());
		}
		else if(IsReal() && op.IsInt())
		{
			return Value(GetReal() + (float) op.GetInt());
		}
		
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
		
		return Value();
		
    }
    
    Value Value::operator==(const Value& op) const {
        if( GetType() == op.GetType() )
        {
        	if( IsInt() ) return Value( (bool)(Itemp == op.GetInt() ));
        	if( IsReal() ) return Value( (bool) (Rtemp == op.GetReal() ));
        	if( IsChar()) return Value( (bool) (Stemp < op.GetChar()));
		}
		else if(IsInt() && op.IsReal())
		{
			
			return Value( (bool) (((float) GetInt())== op.GetReal()));
		}
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

bool PrintStmt(istream& in,int& line){
/*create an empty queue of Value objects.*/
    ValQue = new queue<Value>;
    bool ex = ExprList(in,line);
    if(!ex){
        ParseError(line,"Missing expression after print");
        //Empty the queue and delete.
        while(!(*ValQue).empty()){
            ValQue->pop();
        }
        delete ValQue;
        return false;
    }
    //Evaluate:print out the list of expressions' values
    LexItem t = Parser::GetNextToken(in,line);
    if(t.GetToken()==COMA){
        //Execute the statement after making sure the comma is seen.
        while(!(*ValQue).empty()){
            Value nextVal = (*ValQue).front();
            cout<<nextVal;
            ValQue->pop();
        }
        cout<<endl;
    }
    Parser::PushBackToken(t);
    return ex;
}