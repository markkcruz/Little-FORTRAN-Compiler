/*
 * parse.h
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <iostream>
#include "lex.h"

using namespace std;
                                                            // Grammar Rules
extern bool Prog(istream& in, int& line);                   // Prog = PROGRAM IDENT {Decl} {Stmt} END PROGRAM IDENT   --- #DONE
extern bool Decl(istream& in, int& line);                   // Decl = (INTEGER|REAL|CHAR):IdList                      --- #DONE
extern bool IdList(istream& in, int& line, LexItem tok);    // IdList = IDENT{,IDENT}                                 --- #DONE
extern bool Stmt(istream& in, int& line);                   // Stmt = AssigStmt|IfStmt|PrintStmt|ReadStmt             --- #???
extern bool PrintStmt(istream& in, int& line);              // PrintStmt=PRINT,ExprList                               --- #DONE
extern bool IfStmt(istream& in, int& line);                 // IF(LogicExpr)THEN{Stmt}ENDIF                           --- #DONE?
extern bool AssignStmt(istream& in, int& line);             // AssignStmt = Var = Expr                                --- #DONE?
extern bool ReadStmt(istream& in, int& line);               // ReadStmt = READ, VarList                               --- #DONE?
extern bool ExprList(istream& in, int& line);               // ExprList=Expr{,Expr}                                   --- #DONE?
extern bool Expr(istream& in, int& line);                   // Expr = Term {(+|-)Term}                                --- #???
extern bool Term(istream& in, int& line);                   // Term = SFactor{(*|/)SFactor}                           --- #???
extern bool SFactor(istream& in, int& line);                // SFactor = Sign Factor|Factor                           --- #???
extern bool Factor(istream& in, int& line, int sign);       // Factor = IDENT|ICONST|RCONST|SCONST| (Expr)            --- #Proably Done
extern bool LogicExpr(istream& in, int& line);              // LogicExpr = Expr (==|<) Expr                           --- #???
extern bool VarList(istream& in, int& line);                // Checks for variables if they are in the map            --- #???
extern bool Var(istream& in, int& line);                    // IDENT                                                  --- #???
                                                            // Sign= +|-                                              --- #DONE
extern int ErrCount();

#endif /* PARSE_H_ */
