#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "lexical.h"

int parse(const string&);
int program ()  ;
int compundStmt();
int lists () ;
int stmt();
int assignmentStmt() ;
int doStmt();
int whileStmt();
int ifStmt();
int forStmt();
int switchStmt();
int condition();
int simple();
int structure();
int relationOperator();
int exp();
int exp_prime();
int term();
int term_prime();
int factor();


#endif // PARSER_H_INCLUDED
