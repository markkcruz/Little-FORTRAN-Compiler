# Little FORTRAN Compiler
 A FORTRAN "like" compiler.

A compiler is a computer program (or set of programs) that transforms source code written in a programming language into another computer language.

**An analysis divides program into components and creates the intermediate representation. This part consists of three phases:**

1. Lexical analysis (lexing,scanning) breaks the source code text into small pieces called tokens. Each token is a single atomic unit of the language,for instance a keyword,identifier or symbol name. The token syntax is typically a regular language,so a finite state automaton constructed from a regular expression can be used to recognize it. This phase is also called lexing or scanning,and the software doing lexical analysis is called a lexical analyzer or scanner.

2. Syntactic analysis (parsing) is the process of analyzing a text,made of a sequence of tokens,to determine its grammatical structure with respect to a given formal grammar.

3. Semantic analysis is the phase in which the compiler adds semantic information to the parse tree and builds the symbol table. This phase performs semantic checks such as type checking (checking for type errors),or object binding (associating variable and function references with their definitions),or definite assignment (requiring all local variables to be initialized before use),rejecting incorrect programs or issuing warnings.


Source for description: https://brasil.cel.agh.edu.pl/~11sustrojny/en/compiler/index.html
