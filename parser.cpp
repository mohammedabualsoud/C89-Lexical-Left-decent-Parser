
#include "parser.h"
Token lookahead ;
fstream fs ;
int parse(const string& sourcefile ){
	 fs.open (sourcefile.c_str() ) ;
	if ( !fs.is_open() ){
		cerr << "Cannot open file " << sourcefile << "For parsing " << endl ;
		return -2 ;
	}

	getNextToken(fs , lookahead );
	if ( 0 == program(token) )
		return 0;//every thing correct
	return -2;//syntax error
}

int program () {
	int status = 0 ;//no errors
	if (lookahead.type == IDENTIFER_T  && (strcmp(token.val.stringValue,"main") == 0 ) ) {
		getNextToken(fs ,lookahead);
		if (lookahead.type == LP ){
			getNextToken(fs ,lookahead);
			if (lookahead.type == RP){
				status = compundStmt( );
			}else status = -2; // missing )
		}else status = -2;//missing (
	}else  status = -2;//missing main in the project (program source)

	return status ;
};
int compundStmt(){
	int status = 0 ;
	if (lookahead.type == LCB ){
		getNextToken(fs , lookahead );
		status = lists();
		getNextToken(fs , lookahead) ;
		if (lookahead.type == RCB  ){
			getNextToken(fs , lookahead);
		}else status = -2 ; //missing } after {compundStmt
	}else status = -2 ;// error missing {
	return status ;
}

int lists () {
	int status = 0 ;


	if (lookahead.type == IF_T ){
		status = ifStmt();
	}else if (lookahead.type == IDENTIFER_T ){
		status = assignmentStmt();
	}else if (lookahead.type == FOR_T){
		status = forStmt();
	}else if (lookahead.type == DO_T ){
		status = doStmt() ;
	}else if (lookahead.type == WHILE_T ){
		status = whileStmt( ) ;
	}else if (lookahead.type == SWITCH_T ){
		status = switchStmt() ;
	}else if (lookahead.type == BREAK_T ){
		getNextToken(fs ,lookahead);
		if (lookahead.type == SEMICOLON_T ){
			getNextToken(fs ,lookahead ) ;
		}else status = -2; //missing ; after break
	}
	return status ;
}
int stmt(){
	int status = 0 ;
    switch(lookahead.type){
        case IF_T:

        case IDENTIFER_T:

        case FOR_T :

        case DO_T :

        case WHILE_T :

        case SWITCH_T :

        case BREAK_T :
                        status = lists() ;
                        break ;
        case LCB :
                    status = compundStmt() ;
                    break ;

    }

    return status ;

}



int assignmentStmt(){
	int status = 0 ;
	if (lookahead.type == IDENTIFER_T ) {
		getNextToken(fs , lookahead);
		if ( EQUAL_T == lookahead.type  ){
            getNextToken(fs , lookahead ) ;
            status = exp() ;
            getNextToken(fs , lookahead) ; //to check for ;
            if ( SEMICOLON_T == lookahead.type ){
                getNextToken(fs , lookahead ) ;
            }else status = -2 ; // missing ; after identifer = exp


		}else status = - 2 ;//missing = after Identifer

		}else status = -2 ; // missing Identifer id
    return status ;
}


int doStmt(){
    int status = 0 ;
    if (DO_T == lookahead.type ){
        getNextToken(fs , lookahead) ;
        status = stmt();
        getNextToken(fs , lookahead ) ;
        if ( WHILE_T == lookahead.type ) {
            getNextToken(fs , lookahead);
            if ( LP == lookahead.type ){
                status = condition( ) ;
               // getNextToken(fs , lookahead) ;
                if (RP == lookahead.type ){
                    getNextToken(fs , lookahead):
                    if ( SEMICOLON_T == lookahead.type ){
                        getNextToken(fs , lookahead ) ;
                    }else status = -2; //missing ; after while(condition);
                }else status = -2; // missing ) after (condition
            }else status = -2 ; //missing ( after while

        }else status = -2 ; //missing while token
    }else status = -2 ; // missing DO token/keyword
    return status ;
}
int whileStmt(){
    int status = 0 ;
    if ( WHILE_T == lookahead.type ){
        getNextToken(fs , lookahead ) ;
        if ( LP == lookahead.type ){
            status = condition() ;
            getNextToken(fs , lookahead) ;
            if (RP == lookahead.type ){
                status = stmt();
            }else status = -2 ; // missing ) after while(condition

        }else status = -2 ; // missing LB after while
    }else status = -2 ; // missing while keyword
    return status ;
}

int ifStmt(){
    int status = 0 ;
    if (IF_T == lookahead.type ){
        getNextToken(fs , lookahead ) ;
        if ( LP == lookahead.type ){
            status = condition()  ;
            getNextToken(fs , lookahead ) ;
            if (RP == lookahead.type ){
                status = stmt();
                getNextToken(fs ,lookahead);
                if(ELSE_T == lookahead.type ){
                    status = stmt() ;

                }//else do nothing
            }else status = -2 ;// missing ) after if (condition
        }else status = -2; //missing ( after if


    }else status = -2 ; //missing if
    return status ;
}
int forStmt(){
// TO DO  for ( {<expression>}? ; {<expression>}? ; {<expression>}? ) <statement>

    int status = 0 ;
    return status;
}
int switchStmt(){
    int status = 0 ;
    if ( SWITCH_T == lookahead.type ){
        getNextToken(fs , lookahead ) ;
        if (LP == lookahead.type ){
            getNextToken(fs , lookahead ) ;
            if (IDENTIER_T == lookahead.type ){
                getNextToken(fs , lookahead ) ;
                if (RP == lookahead.type ){
                    getNextToken(fs , lookahead );
                    if ( LCP == lookahead.type ){
                        getNextToken(fs , lookahead) ;
                        if ( CASE_T == lookahead.type ){
                            getNextToken(fs , lookahead );
                            if ( INTEGER_T == lookahead.type ) {
                                getNextToken(fs , lookahead ) ;
                                if (COLON_T == lookahead.type ){
                                    getNextToken(fs , lookahead ) ;
                                    lists() ;
                                    if (SEMICOLON_T == lookahead.type ){
                                        getNextToken(fs , lookahead ) ;
                                       // status = switchStmt();
                                    }else status = -2 ; //missing ; after switch(id){case v1:lists
                                }else status = -2 ; // missing :
                            }else status = -2 ; // missing integer (vi)

                        }else if (DEFAULT_T == lookahead.type ){
                            getNextToken(fs , lookahead );
                            if ( INTEGER_T == lookahead.type ) {
                                getNextToken(fs , lookahead ) ;
                                if (COLON_T == lookahead.type ){
                                    getNextToken(fs , lookahead ) ;
                                    lists() ;
                                    if (SEMICOLON_T == lookahead.type ){
                                        getNextToken(fs , lookahead ) ;
                                        if ( RCP == lookahead.type ){
                                            getNextToken(fs , lookahead );
                                        }else status = -2 ; // missing } after switch block

                        }else stats = -2 ; // mising ; after swtich (id)... lists
                    }else status = -2 ; // missing : after switch (id) ...
                }else status = -2 ; // missing integer (vi) after switch (id)...
            }
        }else status = -2 ; // missing { (after switch(id)
    }else status = -2 ; // missing ) after switch (id

            }else status = -2 ; // missing IDETIFER after switch(
        }else status = -2 ; // missing ( after switch
    }else status = -2 ; // missing switch in the begining of swithc block
    return status ;
}
int condition(){
    int status = 0 ;
    if ( IDETIFER_T == lookahead.type || INTEGER_T == lookahead.type ){
        status = simple() ;

    }else status = structure() ;
    return status ;
}


int simple(){
    int status = 0 ;
    if ( IDENTIFIER_T == lookahead.type || INTEGER_T == lookahead.type ){
        getNextToken(fs , lookahead ) ;

    }else status = -2 ; // missing integer or identifier
    return status ;
}
int structure(){
    int status = 0;
     status = simple();
     status = relationOperator();
     status = simple() ;
     return status ;
}
int relationOperator(){
    int status = 0 ;
    switch ( lookahead.type  ) {
        case LT_T : case GT_T: case LTE_T : case GTE_T : case  NEQ_T :
            getNextToken(fs , lookahead ) ;
          default : status = -2 ; //missing < |>|<=|>=|!=
    }
    return status ;
}
int exp(){
    int status = 0 ;
    status = term();
    status = exp_prime();
    return status ;
}

int exp_primes(){
    int status = 0 ;
    if (ADD_T == lookahead.type || SUBTRACT_T == lookahead.type ){
        status = term() ;
        status = exp_prime();
    }//else do nthing
    return status ;
}
int term(){
    int status = 0 ;
    status = factor();
    status = term_prime() ;
    return status ;
}
int term_prime(){
    int status = 0 ;
    if (MULT_T == lookahead.type || DIV_T == lookahead.type ){
        status = factor();
        status = term_prime() ;
    }//else do nthing
    return status ;
}

int factor(){
    int status = 0;
    if (INTEGER_T || IDENTIFIER_T ){
        getNextToken(fs , lookahead);
    }else if ( LP == lookahead.type  ){
        getNextToken(fs , lookahead ) ;
        status = exp();
        if (RP == lookahead.type ){
            getNextToken(fs , lookahead) ;
        }else status = -2 ; //missing ) after (exp
    }else status = -2 ; //missing (

    return status ;
}
