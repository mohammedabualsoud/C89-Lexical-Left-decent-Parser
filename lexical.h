#ifndef LEXICAL_H_INCLUDED
#define LEXICAL_H_INCLUDED



#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <assert.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iomanip>


using namespace std ;

#define AUTO_T 300
#define BREAK_T 301
#define CASE_T 302
#define CHAR_T 303
#define CONST_T 304
#define CONTINUE_T 305
#define DEFAULE_T 306
#define DO_T 307
#define DOUBLE_T 308
#define ELSE_T 309
#define ENUM_T 310
#define EXTERN_T 311
#define FLOAT_T 312
#define FOR_T 313
#define GOTO_T 314
#define IF_T 315
#define INT_T 316
#define LONG_T 317
#define REGISTER_T 318
#define RETURN_T 319
#define SHORT_T 320
#define SIGNED_T 321
#define SIZEOF_T 322
#define STATIC_T 323
#define STRUCT_T 324
#define SWITCH_T 325
#define TYPEDEF_T 326
#define UNION_T 327
#define UNSIGNED_T 328
#define VOID_T 329
#define VOLATILE_T 330
#define WHILE_T 331







#define IDENTIFER_T 400
#define INTEGER_T 401
#define REAL_T 402
//#define SCIENTIFIC_T 403
#define CHARACHTER_T 403
#define STRING_T 404

//separaotrs
#define LP 405
#define RP 406
#define LB 407
#define RB 408
#define LCB 409
#define RCB 410
#define SEMICOLON_T 411
#define COMMA 412
#define DOT 413
#define COLON 414

//operators
//Assignemt

#define PLUSEQUAL_T 500
#define MINUSEQUAL_T 501
#define MULTEQUAL_T 502
#define DIVEQUAL_T 503
#define MODEQUAL_T 504
#define SHIFTLEFTEQUAL_T 505
#define SHIFTRIGHTEQUAL_T 506
#define ANDEQUAL_T 507
#define XOR_EUQAL_T 508
#define OR_EQUAL_T 509
#define ASSIGNEMENT_T 510
//Increment & Decrement
#define INCREMENT_T 511
#define DECREMENT_T 512

//Arithmetic
#define ADD_T 513
#define SUB_T 514
#define MULT_T 515
#define DIV_T 516
#define MOD_T 517

//Comparison
#define EQUAL_T 518
#define NOTEQUAL_T 519
#define GT_T 520
#define GTE_T 521
#define LT_T 522
#define LTE_T 523
//Logical
#define LOGICALAND_T 524
#define LOGICALOR_T 525
#define LOGICALNEGATION_T 526
//Bitwise
#define BITWISEAND_T 527
#define BITWISEOR_T 528
#define BITWISEXOR_T 529
#define BITWISENEGATION_T 530

#define EOF_T 600
#define UNKNOW_T 601
#define BUFFER_SIZE 8192




struct Token {
    int type ;
    int lineNum ;
    int columnNum ;
    union {
    char stringValue [128];
    int intValue;
    double doubleValue;
    }val ;

    void clears()
    {

        if (type == REAL_T)
            val.doubleValue = 0.0 ;
        else if ( type == INTEGER_T)
            val.intValue = 0 ;
        else {
            std::fill_n(val.stringValue , 128 ,'0' );
        }
        type = lineNum = columnNum = 0 ;
    }
};




map <string , int > keywords;
map <int , string> lexemes;
int column = 0 ;
int line =1 ;





void initScanner();
int getNextToken(fstream& , Token& );
int handleIntegers (string& input ,int) ;
double handleDoubles( string& input ) ;
void fetch_dot_e_E_digit_other(fstream& instream ,string& input ,Token& token ,int& ch );
void ifDot(fstream & instream , string& input , Token& token , int& ch );
void eE(fstream & instream , string& input , Token& token ,int& ch );
void fillToken (Token & token , int type , int col , int& line );
std::string fmt(size_t margin, size_t width, std::string text);




#endif // LEXICAL_H_INCLUDED
