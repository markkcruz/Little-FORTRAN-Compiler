#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;
// Use of enem type called ValType. Defined an enum type which includes the symbolic names. The value for int, real, char, bool and error
enum ValType { VINT, VREAL, VCHAR, VBOOL, VERR };

// You are the implementor of the interpreter. Given this class forming the interface to the class.
// This class creates an object that in houses those private data members. It desgintates its type of a valtype of enum type. There are 4 other Data members. Each one of them
// Is of a certain type. So int, float, string bool.
class Value {
    ValType	T;
     bool    Btemp;
	int		Itemp;
	float   Rtemp;
    string	Stemp;

    // Overloaded constructors. Each one of them instantiates an object with a certain value based on the value passed to it/
    // The one without a passed parameter will have Error with intTemp and RealTemp to 0. ETC.
public:
    Value() : T(VERR), Itemp(0), Rtemp(0.0){}
    Value(bool vb) : T(VBOOL), Btemp(vb), Itemp(0), Rtemp(0.0) {}
    Value(int vi) : T(VINT), Itemp(vi) {}
	Value(float vr) : T(VREAL), Itemp(0), Rtemp(vr) {}
    Value(string vs) : T(VCHAR), Itemp(0), Rtemp(0.0), Stemp(vs) {}

    // Other methods include a check whether the current object type (ERR, INT, CHAR...) returns based on the type.
    // GetType returns a getter for the type data member to be returned and checked.
    ValType GetType() const { return T; }
    bool IsErr() const { return T == VERR; }
    bool IsInt() const { return T == VINT; }
    bool IsChar() const { return T == VCHAR; }
    bool IsReal() const {return T == VREAL;}
    bool IsBool() const {return T == VBOOL;}

    // For each getter type, it has to check if the type is actually belonging to that

    // Get INT which returns the value if the integer is an int type. Else, throw an exception.
    int GetInt() const { if( IsInt() ) return Itemp; throw "RUNTIME ERROR: Value not an integer"; }

    // Get CHAR which returns the value if the char is an int type. Else, throw an exception.
    string GetChar() const { if( IsChar() ) return Stemp; throw "RUNTIME ERROR: Value not a string"; }

    // Get REAL which returns the value if the real is an int type. Else, throw an exception.
    float GetReal() const { if( IsReal() ) return Rtemp; throw "RUNTIME ERROR: Value not a real"; }

    // Get BOOL which returns the value if the bool is an int type. Else, throw an exception.
    bool GetBool() const {if(IsBool()) return Btemp; throw "RUNTIME ERROR: Value not a boolean";}


    // The exception will terminate the program due to runtime error. EX. Value is not string, value is not real.

    // Setters: methods allowing an existing value for an object to be changed. This is assuming of the same type.
    // Has to check the type before actually making the assignment.
    void SetInt(int val){ if( IsInt() ) Itemp = val; throw "RUNTIME ERROR: Type not an integer";}
	
	void SetReal(float val){ if( IsReal() ) Rtemp = val; throw "RUNTIME ERROR: Type not a real";}
	
	void SetChar(string val){ if( IsChar() ) Stemp = val; throw "RUNTIME ERROR: Type not a string"; }
	
	void SetBool(bool val){ if(IsBool()) Btemp = val; throw "RUNTIME ERROR: Type not a boolean";}


    // Set of overloaded operators are provided to support the evaluation of epxressions
    // The + - * / are all overloaded and they are acting like you are passing a value of operant and this is like adding the value operator to the value object

    // add op to this
    Value operator+(const Value& op) const;
    
    // subtract op from this
    Value operator-(const Value& op) const;
    
    // multiply this by op
    Value operator*(const Value& op) const;
    
    // divide this by op
    Value operator/(const Value& op) const;

    // Needed for the relational operators. Compare this value of the object with the passed operant
    Value operator==(const Value& op) const;

	Value operator<(const Value& op) const;

    // Friend mothod to overload the operator for insertationl. Gives the ability of this insertation operator to print out the object of the value.
    // Printing out the object of the value is done by checking the type. If it is int, then print out the value of the integer data memmber.
    // If char, string vlaue. If real, print real temp.
    // OTHERWISE, PRINT OUT AN ERROR.
    // Assuming the left is boolean or error type will print out ERROR.
    friend ostream& operator<<(ostream& out, const Value& op) {
        if( op.IsInt() ) out << op.Itemp;
        else if( op.IsChar() ) out << op.Stemp;
        else if( op.IsReal()) out << op.Rtemp;
        else out << "ERROR";
        return out;
    }
};


#endif
