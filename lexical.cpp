#include "lexical.h"



std::string fmt(size_t margin, size_t width, std::string text)
{
    std::string result;
    while (!text.empty())   // while more text to move into result
    {
        result += std::string(margin, ' ');  // add margin for this line

        if (width >= text.size())  // rest of text can fit... nice and easy
            return (result += text) += '\n';

        size_t n = width - 1;  // start by assuming we can fit n characters
        while (n > width / 2 && isalnum(text[n]) && isalnum(text[n - 1]))
            --n; // between characters; reduce n until word breaks or 1/2 width left

        // move n characters from text to result...
        (result += text.substr(0, n)) += '\n';
        text.erase(0, n);
    }
    return result;
}



void initScanner()
{
    keywords ["auto"] = AUTO_T;
    keywords ["break"] = BREAK_T ;
    keywords ["case"] = CASE_T;
    keywords ["char"] = CHAR_T ;
    keywords ["const"] = CONST_T;
    keywords ["continue"] = CONTINUE_T ;
    keywords["default"] = DEFAULE_T ;
    keywords ["do"] = DO_T;
    keywords ["double"] = DOUBLE_T ;
    keywords ["else"] = ELSE_T ;
    keywords ["enum"] = ENUM_T ;
    keywords ["extern"] = EXTERN_T;
    keywords ["float"] = FLOAT_T;
    keywords ["for"] = FOR_T ;
    keywords ["goto"] = GOTO_T ;
    keywords ["if"] = IF_T ;
    keywords ["int"] = INT_T;
    keywords ["long"]= LONG_T ;
    keywords ["register"] = REGISTER_T ;
    keywords ["return"] = RETURN_T;
    keywords ["short"] = SHORT_T;
    keywords ["signed"] = SIGNED_T ;
    keywords ["sizeof"] = SIZEOF_T ;
    keywords ["static"] = STATIC_T ;
    keywords ["struct"] = STRUCT_T ;
    keywords ["switch"] = SWITCH_T ;
    keywords ["typede"] = TYPEDEF_T ;
    keywords ["union"] = UNION_T ;
    keywords ["unsigned"] = UNSIGNED_T ;
    keywords ["void"] = VOID_T ;
    keywords ["volatile"] = VOLATILE_T ;
    keywords ["while"] = WHILE_T ;


    lexemes[ASSIGNEMENT_T] = "=";
    lexemes[PLUSEQUAL_T] = "+=" ;
    lexemes[MINUSEQUAL_T] = "-=" ;
    lexemes[MULTEQUAL_T] = "*=" ;
    lexemes[DIVEQUAL_T] = "/=" ;
    lexemes[MODEQUAL_T] = "%=" ;
    lexemes[SHIFTLEFTEQUAL_T] = "<<=" ;
    lexemes[SHIFTRIGHTEQUAL_T] = ">>=" ;
    lexemes[ANDEQUAL_T] = "&=" ;
    lexemes[XOR_EUQAL_T] = "^=" ;
    lexemes[OR_EQUAL_T] = "|=" ;
    lexemes[INCREMENT_T] = "++" ;
    lexemes[DECREMENT_T] = "--" ;
    lexemes[ADD_T] = "+" ;
    lexemes[SUB_T] = "-" ;
    lexemes[MULT_T] = "*" ;
    lexemes[DIV_T] = "/" ;
    lexemes[MOD_T] = "%" ;
    lexemes[EQUAL_T] = "==" ;
    lexemes[NOTEQUAL_T] = "!=" ;
    lexemes[GT_T] = ">" ;
    lexemes[GTE_T] = ">=" ;
    lexemes[LT_T] = "<" ;
    lexemes[LTE_T] = "<=" ;
    lexemes[LOGICALAND_T] = "&&" ;
    lexemes[LOGICALOR_T] = "||" ;
    lexemes[LOGICALNEGATION_T] = "!" ;
    lexemes[BITWISEAND_T] = "&" ;
    lexemes[BITWISEOR_T] = "|" ;
    lexemes[BITWISEXOR_T] = "^";
    lexemes[BITWISENEGATION_T] = "`" ;
    lexemes[DOT] = "." ;
    lexemes[SEMICOLON_T] = ";" ;
    lexemes[LP] = "(" ;
    lexemes[RP] = ")" ;
    lexemes[LB] = "[" ;
    lexemes[RB] = "]" ;
    lexemes[DOT] = "." ;
    lexemes[LCB] = "{" ;
    lexemes[RCB] = "}" ;
    lexemes[COMMA] = "," ;
    lexemes[COLON] = ":";






}

int getNextToken(fstream& instream , Token& token)
{
    int ch ;

    while  ( (ch = instream.get() ) != EOF )
    {
        //get ride of spaces & new line(done)
        //descard comment(done)
        //recognize identifiyer(done)
        //recognice the numbers.(done)
        //recognize the operators
        // recognize the characters
        //recognize the string
        column++;
        while( isspace(ch) )
        {
            ch=instream.get() ;
            column++;
        }
        if (ch == '\n')
        {
            line++;
            column =0;
        }
        // comments recognition
        else if ( ch == '/')
        {
            ch = instream.get() ;
            column++;
            switch (ch)
            {
                case '/' :
                        //ignore until new line
                        while ( (ch = instream.get() ) != EOF && ch != '\n' );
                            if (ch == '\n')
                            {
                                line++;
                                column = 0;

                            }
                            else  {
                                fillToken(token , EOF_T , column , line ) ;
                            return EOF_T;
                            }
                    break ;
                case '*' :
                    {
                        bool done = false ;
                        while ( !done)
                        {
                            while ( (ch = instream.get() ) != EOF  && ch != '*' )
                            {
                                column++;
                            }
                            if ( ch == '*')
                            {
                                column++;
                                ch = instream.get() ;
                                if (ch == '/' )
                                {
                                    column++;
                                    done = true ;
                                }
                                else if ( ch == EOF )
                                {
                                    fillToken(token , EOF_T , column , line ) ;
                                    return token.type;
                                }

                            }
                            //EOF TOKEN
                            else
                            {
                                 fillToken(token , EOF_T , column , line ) ;
                                 return EOF_T;

                            }
                        }
                    break ;
                    }
                case  '=': // Token /=
                         fillToken(token , DIVEQUAL_T , column , line ) ;
                        return  token.type ; //EOF
                    break ;
                default : // token /
                        instream.unget();
                        fillToken(token , DIV_T , column , line ) ; // DIV_T
                        return token.type;
                    break ;

            }//swtich

        }//if ch == '/'
            //IDENTIFER recognition
        else if ( isalpha(ch) || ch == '_' )
        {

            int i = 0 ;
            token.val.stringValue[i++] = ch;
            while ( ( ch = instream.get() ) && (isdigit(ch) || isalpha(ch) || ch == '_' ) )
            {
                column++;
                token.val.stringValue[i++] = ch;
            }

                    instream.unget();

                    token.val.stringValue[i] = '\0' ;
                    map<string,int>::iterator it;
                    string id = token.val.stringValue ;
                    it = keywords.find(id);
                    if (it!=keywords.end() )//the identifer is a keywrod
                    {

                        fillToken(token , it->second ,strlen(token.val.stringValue)  , line ) ;
                        return token.type ;

                    }
                    else
                    {
                        fillToken(token , IDENTIFER_T , strlen(token.val.stringValue) , line ) ;
                        return  token.type  ;

                    }

        }//recognition IDENTIFERS


    //recognition NUMBERS (Integer & double )
        else if ( '.' == ch || '+' == ch || '-' == ch || isdigit(ch)  )
        {
            string input;
            //lets check the next stream of chars
            if ( isdigit(ch) ) //{1}
            {
              input.push_back( ch) ;
              fetch_dot_e_E_digit_other(instream , input , token , ch );
              token.columnNum = column - input.size() ;
              return token.type;

            }// the bottom road if digit fetched from {1}
            //the middle road if +|- is fetched from {1}
            else if ( '+' == ch || '-' == ch ) //{1}->{5}
            {
                input.push_back(ch) ;
                ch = instream.get () ;
                column++;
                if ( '.' == ch ) //{5}->{2}
                {
                   ifDot(instream , input , token , ch ) ;
                   if (token.type != UNKNOW_T )
                   {
                   token.columnNum = column - input.size() ;
                    return token.type ;
                    }

                }//if '.'
                else if (EOF != ch && isdigit(ch ) )//{5}->{7}
                {
                   input.push_back( ch ) ;
                   fetch_dot_e_E_digit_other(instream , input , token , ch ) ;
                    token.columnNum = column - input.size() ;
                   return token.type ;

                }
                // if next char after +|- is not . or digit (i.e it's an operator)
                //just back two step to the begining of +|- and continue processing the text .
                else
                {

//                  instream.unget();
//                  instream.unget();
                    input.clear() ;
                    instream.seekg( -2 ,ios::cur );
                    column -=2 ;
                    token.type = UNKNOW_T ;

                }


            }
             //the top road if '.' is fetched
            else if ( '.' == (ch ) )//(1)->{2}
            {
                ifDot(instream ,input , token , ch);
                if (token.type != UNKNOW_T)
                {
                 token.columnNum = column - input.size() ;
                 return token.type ;
                }

            }

//            double decimal = 10;
//            column++;
//             token.val.doubleValue = 0.0;
//
      //     while (  isdigit( (ch = instream.get() ) )  )
//            {
//                token.val.doubleValue += (ch - '0' )/decimal ;
//                decimal *=10;
//                column++ ;
//            }
//            fillToken(token , REAL_T , column , line );
//            return token.type ;
        }//Recognition Numbers (integers&double)
//

            //if fail recognise Sienctifc tokens like +.x |-.x|.x
           if ( token.type == UNKNOW_T )
           {
                ch = instream.get() ;
                column++;
           }
           // separators , operator without /= , / , charachters , strings
           switch (ch )
           {
            //Separators .|(|)|[|]|{|}|;|,|:
            case '.' :

                fillToken(token , DOT , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case '(' :
                fillToken(token , LP , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case ')' :
                fillToken(token , RP , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case '[' :
                fillToken(token , LB , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case ']' :
                fillToken(token , RB , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case '{' :
                fillToken(token , LCB , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case '}' :
                fillToken(token , RCB , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case ';' :
                fillToken(token , SEMICOLON_T , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case ',' :
                fillToken(token , COMMA , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            case ':' :
                fillToken(token , COLON , column , line ) ;
                token.columnNum = column - 1;
                return token.type ;
                break ;
            }
            //operators

 switch (ch){

        /* + , += , ++ ,*/
    case '+':

                ch = instream.get() ;
                column++ ;
 //(-------------tested-------------)
            if ( ch == '=' ){
                // ASSIGNEMNT Token +=
                fillToken( token ,PLUSEQUAL_T ,column -2,line );

                return token.type;
            }
            //(-------------tested-------------)
            else if ( ch == '+' ){
                //IncrementDecrement token ++
                fillToken (token ,INCREMENT_T,column -2, line  ) ;

                return token.type ;
            }
             //(-------------tested-------------)
            else {
                //ARITHMETHIC Token +
                instream.unget() ;
                column--;
                fillToken( token ,ADD_T , column -1, line );
                return token.type ;
            }
        break ;

    case '-' :
            ch = instream.get() ;
            column++ ;
 //(-------------tested-------------)
            if ( ch == '=' ){
                // ASSIGNEMNT Token -=
                fillToken( token ,MINUSEQUAL_T , column -2, line  );
                return token.type ;
            }
            //(-------------tested-------------)
            else if ( ch == '-' ){
                //IncrementDecrement token --
                fillToken (token ,DECREMENT_T,column -2, line   ) ;
                return token.type ;
            }
             //(-------------tested-------------)
            else {
                //ARITHMETHIC Token -
                instream.unget();
                column--;
                fillToken( token ,SUB_T , column -1, line );
                return token.type ;
            }
        break ;

    case '*' :
                ch = instream.get();
                column++;
                //(-------------tested-------------)
                // ASSIGNEMENT Token *=
                if ( ch == '=' ){
                    fillToken(token , MULTEQUAL_T , column-2 , line  ) ;
                    return token.type ;

                }
                //(-------------tested-------------)
                // //ARITHMETHIC Token *
                else {

                instream.unget();
                column--;
                fillToken( token ,MULT_T , column -1, line );
                return token.type ;

                }

            break ;

    case '%' :
                ch = instream.get();
                column++;
                //(-------------tested-------------)
                // ASSIGNEMENT Token %=
                if ( ch == '=' ){
                    fillToken(token , MODEQUAL_T , column -2, line ) ;
                    return token.type ;

                }
                //(-------------tested-------------)
                // //ARITHMETHIC Token %
                else {

                    instream.unget();
                    column--;
                    fillToken( token ,MOD_T , column -1, line );
                    return token.type ;
                }

            break ;

    case '&':
                ch = instream.get() ;
                column++ ;
        //(-------------tested-------------)
            if ( ch == '=' ){
                // ASSIGNEMNT Token &=
                fillToken( token ,ANDEQUAL_T , column -2, line );
               return token.type ;
            }
            //(-------------tested-------------)
            else if ( ch == '&' ){
                //LOGICAL  token &&
                fillToken (token ,LOGICALAND_T,column -2, line   ) ;
                return token.type;
            }
             //(-------------tested-------------)
            else {
                //BITWISE Token &
                instream.unget() ;
                column-- ;
                fillToken( token ,BITWISEAND_T , column -1, line );
                return token.type ;
            }
        break ;

    case '|' :
                ch = instream.get() ;
                column++ ;
        //(-------------tested-------------)
            if ( ch == '=' ){
                // ASSIGNEMNT Token |=
                fillToken( token , OR_EQUAL_T, column -2, line  );
                return token.type ;
            }
            //(-------------tested-------------)
            else if ( ch == '|' ){
                //LOGICAL  token &&
                fillToken (token ,LOGICALOR_T,column -2, line   ) ;
                return token.type ;
            }
             //(-------------tested-------------)
            else {
                //BITWISE Token |
                instream.unget() ;
                column--;
                fillToken( token ,BITWISEOR_T , column-1, line );
                return token.type ;
            }

            break ;

    case '!' :
                ch  = instream.get() ;
                column++;
                //(-------------tested-------------)
                //COMPARISON operator TOKEN !=
                if (ch == '=' ){
                    fillToken(token ,NOTEQUAL_T, column-2 , line )  ;
                    return token.type ;
                }
                //(-------------tested-------------)
                //LOGICAL operator TOKEN !
                else {
                    fillToken(token ,LOGICALNEGATION_T, column -1, line )  ;
                    return token.type ;
                }

                break ;
    case '=' :
                ch = instream.get() ;
                column++;
                 //(-------------tested-------------)
                //COMPARISON operator TOKEN ==
                if (ch  == '=' ){
                    fillToken(token ,EQUAL_T, column -2, line  )  ;
                    return token.type ;
                }
                 //(-------------tested-------------)
                //ASSIGNEMNT OPERATOR TOKEN =
                else {
                    instream.unget() ;
                    column--;
                    fillToken(token ,ASSIGNEMENT_T, column -1, line )  ;
                    return token.type ;
                }

                break ;
    case '^' :
                ch  = instream.get() ;
                column++;
                 //(-------------tested-------------)
                //ASSIGNEMNT OPERATOR TOKEN  ^=
                if (ch == '=' ){
                    fillToken(token ,XOR_EUQAL_T, column-2 , line)  ;
                    return token.type ;
                }
                //(-------------tested-------------)
                 //BITWISE OPERATOR TOKEN ^
                else {
                    instream.unget() ;
                    column-- ;
                    fillToken(token ,BITWISEXOR_T, column  -1, line ) ;
                   return token.type ;
                }

                break ;
    case '`' :
                //(-------------tested-------------)
                 //BITWISE OPERATOR TOKEN `
                 fillToken(token ,BITWISENEGATION_T, column -1, line )  ;
                 return token.type ;
                 break ;

    case '<' :

                 ch = instream.get();
                 column++ ;
        //(-------------tested-------------)
            if ( ch == '<' ){
                // ASSIGNEMNT operator Token <<=
                if ( (ch = instream.get() ) == '=' ){
                    column++;
                    fillToken( token ,SHIFTLEFTEQUAL_T , column -3, line  );
                    return token.type ;
                }
                else{ // if <<* this segment code will handle
                    instream.seekg(-2, ios::cur) ;
                    column--;
                    fillToken(token , LT_T , column -1 ,line ) ;
                    return token.type ;

                }
            }
            //(-------------tested-------------)
            else if ( ch == '=' ){
                //COMPARISON operator token <=
                fillToken (token ,LTE_T,column -2 , line   ) ;
                return token.type ;
            }
             //(-------------tested-------------)
            else {
                 //COMPARISON operator token <
                 instream.unget() ;
                 column--;
                fillToken( token ,LT_T , column -1, line );
                return token.type;
            }
        break ;

    case '>' :
                ch = instream.get();
                column++ ;
        //(-------------tested-------------)
            if ( ch == '>' ){
                // ASSIGNEMNT operator Token >>=
                if ( (ch = instream.get() ) == '=' ){
                    column++;
                    fillToken( token ,SHIFTRIGHTEQUAL_T , column-3 , line  );
                    return token.type ;
                }
                else{ // if >>* this segment code will handle
                    instream.seekg(-2, ios::cur) ;
                    column--;
                    fillToken(token , GT_T , column  -1,line ) ;
                    return token.type ;

                }
            }
            //(-------------tested-------------)
            else if ( ch == '=' ){
                //COMPARISON operator token >=
                fillToken (token ,GTE_T,column  -2, line   ) ;
                return token.type ;
            }
             //(-------------tested-------------)
            else {
                 //COMPARISON operator token >
                 instream.unget() ;
                 column--;
                fillToken( token ,GT_T , column -1, line );
                return token.type;
            }
        break ;

 }
    //Recognize Characters
    if ( '\'' == ch ){
        string input ;
        input.push_back(ch);
        ch = instream.get() ;
        column++;
        input.push_back(ch) ;
        if ( '\'' != ch ){
            while (  ( ch = instream.get()  ) != EOF && '\'' != ch   ){
                column++;
                input.push_back(ch);

            }
            column++;

            if ( ch == '\''  ){
                input.push_back(ch);
                if ( instream.get() == '\'' ){
                    input.push_back('\'') ;
                    column++;
                }else {
                    instream.unget();
                }
                fillToken(token , CHARACHTER_T , column - input.size(), line ) ;
                size_t length = input.copy(token.val.stringValue,128);
                token.val.stringValue [length] = '\0';
                input.clear();
                return token.type  ;
            }else{
            //  EOF fetched Error missing '
                fillToken(token , UNKNOW_T , column -input.size(), line ) ;
                //fillToken(token , CHARACHTER_T , column , line ) ;
                size_t length = input.copy(token.val.stringValue,128);
                token.val.stringValue [length] = '\0';
                input.clear();
                return token.type ;
            }
        }else {
            cerr << "Error : Empty chararacter " <<endl ;
                fillToken(token , UNKNOW_T , column - input.size() , line ) ;
                size_t length = input.copy(token.val.stringValue,128);
                token.val.stringValue [length] = '\0';
                input.clear();
                return token.type ;
        }
    }else if ( '\"' == ch ){//Recognistion String
        int idx = 0;
        bool done = false ;
        token.val.stringValue[idx++] = ch;
        while (!done ){

            while (  ( (ch = instream.get()  ) != EOF ) && '\"' != ch    ){

            token.val.stringValue[idx++] = ch;
            column++ ;
        }
        if (ch == EOF ){ // in case no end of the string and EOF featched like "jasd jjj
            token.val.stringValue[idx] = '\0';
            fillToken(token , UNKNOW_T , column - strlen(token.val.stringValue), line ) ;
            return token.type;
        }
        column++;
        if ( token.val.stringValue[idx -1 ] != '\\' && ch == '\"' ){
            token.val.stringValue[idx++] = ch ;
            token.val.stringValue[idx] = '\0' ;
            done = true ;
        }
        if (!done ){
            token.val.stringValue[idx++] = ch ;
        }

    }

    fillToken(token, STRING_T , column - strlen(token.val.stringValue), line ) ;
    return token.type ;

    }



}//big loop


    return  EOF_T;

}


void fillToken (Token & token , int type , int col , int& line )
{
    token.type = type ;
    token.columnNum = col;
    token.lineNum = line ;
}


int handleIntegers (string& input ,  int lenth)
{
    //write the handler's and test each one
    int result = 0 ;
    if ( !input.empty())
    {
        int i = 0;
        int exp = 1;

        if ( '+' == input.at(0) || '-' == input.at(0) )
        {
            i = 1 ;
	    exp = 2;
        }


        for (  ; i < lenth; i++, exp++ )
        {
    	  result +=( (int) ( input.at(i) -'0') ) * pow(10, ( lenth - exp ) );

        }

    }
    if ( input.at(0) == '-' )
      result *=-1;

    return result ;
}


double handleDoubles ( string& input )
{
  //11.1E1"
  double result = 0.0;
  if ( !input.empty() )
    {
      bool isneg = false;
      size_t  i ;
      int exp = -1 ;
      size_t decimal_pos = input.find(".");

      if (  decimal_pos != string::npos )
        {
          if ( decimal_pos != 0 )
            {
              result += handleIntegers(input , decimal_pos) ;
              if ( result < 0 )
                {
                   isneg = true;
                    result *= -1 ;
                }
            }
	  char ch ;

      for (  i = decimal_pos + 1 ; i < input.length() ; i++ )
        {

          ch = input.at(i);
          if (isdigit( ch ) )
            {
              result  += (double) ( input.at(i) -'0')  * pow(10,  exp ) ;
              exp += -1 ;
            }

          else if ( 'e' == ch || 'E' == ch )
            {
              string rhs ;
              int exponent = 0;
              for ( size_t j = i+1 ; j < input.length() ; j++ )
                {
                    rhs.push_back( input[j] );
                }
              exponent = handleIntegers( rhs , rhs.length()  ) ;
              result *= pow(10 , exponent ) ;
              //end the outter loop
              i = input.length() ;
            }


        }//for i=decimal_pos ...
	}//if decima_pos!= 0 ....


      // convert the string until E|e to integer then continue processing the
      //exponent part .
      else if ( decimal_pos == string::npos )
    {
	  size_t e_pos = input.find("e");

	  if (e_pos != string::npos)
	    {
	      result += handleIntegers(input , e_pos ) ;
	      if ( result < 0 )
            {
              isneg = true;
              result *= -1 ;
            }
	    }
	  else
	    {
	      e_pos = input.find("E")  ;
	      result += handleIntegers(input , e_pos ) ;
	      if ( result < 0 )
            {
              isneg = true;
              result *= -1 ;

            }

	    }
	  // process from  the E|e  to end of input
	  string rhs ;
	  for ( size_t j = e_pos + 1 ; j < input.length() ; j++ )
	    {
	      rhs.push_back(input [j] ) ;
	    }
	  int exponent = handleIntegers(rhs , rhs.length()  ) ;
	  result *= pow(10 , exponent ) ;

	}


      if ( isneg)
        result *= -1 ;
    }


  return result ;
}
void eE(fstream & instream , string& input , Token& token ,int& ch )
{
    input.push_back(ch ) ;
    ch = instream.get() ;
    column++;
    if ( '+' == ch || '-' == ch )//{8}->{9}
    {
        input.push_back( ch ) ; // push the sign +|-
        if ( ( (ch = instream.get()  ) != EOF  ) && isdigit(ch )  )//{9}->{10}
        {
            input.push_back( ch) ;
            column++;
            while ( ( (ch = instream.get()  ) != EOF  ) && isdigit(ch ) ) //{10}->{10}
            {
                input.push_back( ch) ;
                column++ ;
            }
            // EOF or non digit featch , reached a (Sientific )double .
            //{10}->(12)
            instream.unget() ;
            token.val.doubleValue = handleDoubles(input ) ;
            fillToken( token , REAL_T , column , line ) ;
            return  ;
        }
        // error missing digit after E|e
        else //{9}->{6}
        {
            instream.unget();
            cerr << " missing digit after exponet " << endl ;
            //token.val.stringValue = input ;
            size_t len = input.copy (token.val.stringValue , 128 );
            token.val.stringValue[len] = '\0' ;
            fillToken( token , UNKNOW_T , column , line ) ;
            return  ;
        }

    }

    //recognize Sienctifc double
    else if (isdigit( ch ) ) //{8}->{10}
    {
        input.push_back(ch ) ;
        while ( ( (ch = instream.get() ) != EOF ) && isdigit( ch )   )//{10}->{10}
        {
            input.push_back( ch ) ;
            column++;
        }
        //Recognise the Sientific double
        instream.unget() ;
        token.val.doubleValue = handleDoubles ( input ) ;
        fillToken ( token , REAL_T , column , line ) ;
        return  ;

    }
    // error missing digit after E|e
    else //{8}->{6}
    {
        instream.unget();
        column-- ;
        cerr << " missing digit after exponet " << endl ;
        size_t len = input.copy (token.val.stringValue , 128 );
        token.val.stringValue[len] = '\0' ;
        fillToken( token , UNKNOW_T , column , line ) ;
        return ;
    }
}

void ifDot(fstream & instream , string& input , Token& token , int& ch )
{
    input.push_back(ch) ;

    if ( ( EOF != ( ch = instream.get() )   ) && isdigit( ch )  )//{2}->{3}
    {

        input.push_back( ch ) ;
        column++;

        while ( ( EOF != ( ch = instream.get() )   ) && isdigit( ch )  )//{3}->{3}
        {
            input.push_back( ch ) ;
            column++;
        }
        column++;
        if ( 'e' == ch || 'E' == ch )//{15}
        {
            eE(instream , input , token , ch ) ;
            return  ;
        }
        //recognize double
        else //{3}->(4)
        {
            instream.unget();
            column-- ;
            token.val.doubleValue = handleDoubles(input) ;
            fillToken( token , REAL_T , column , line ) ;
            return ;
        }

    }
    //Unkown token for now i should back . like +|-'.'  // back 2 position to check againe for operators & separators.
    else
    {
        if ( input.size() == 1)
        {
            instream.seekg( -2 ,ios::cur );

            column-=1;
            //cout << "Seek 2 pos back ." << endl ;


        }
        else if (input.size() == 2)
        {
            instream.seekg( -3 , ios::cur) ;
            column -=2 ;


        }

        fillToken( token , UNKNOW_T , column , line ) ;

        return  ;
    }
}


void fetch_dot_e_E_digit_other(fstream& instream , string& input , Token& token ,int& ch )
{

    //while the next char isdigit & not EOF keep storing numbers;
        while ( ( (ch = instream.get() ) != EOF  ) && isdigit( ch )  )//{7}
            {
                column++;
                input.push_back(ch);

            }
            // EOF or not digit featch.
            column++;
            if ( '.' != ch && 'e' != ch && 'E' != ch  )//(11)
            {
            // this mean i found integer
                int output = 0;
                instream.unget() ;
                column-- ;
                output = handleIntegers(input ,input.length() ) ;
                token.val.intValue = output ;
                fillToken(token , INTEGER_T , column , line ) ;
                return ;

            }
            else if ( '.' == ch  )//{7}->{3}
            {
                //now next stream of chars may be double or sientific double

                input.push_back(ch) ;
                while ( ( ( ch = instream.get() ) != EOF ) && isdigit( ch )  ) //{3}->{3}
                {
                    input.push_back( ch ) ;
                    column++;
                }
                //if ch == e|E then we go to Sienctifc interpretaion else i got a double .
                column++;
                // for Sientifc Num.
                if ( 'e' == ch || 'E' == ch )//{3}->{8}
                {
                    eE( instream , input ,  token ,ch );
                    return  ;

                }//if e|E
                // it's a double
                else //{3}->{4}
                {
                    instream.unget() ;
                    column-- ;
                    double output = 0.0;
                    output = handleDoubles( input ) ;
                    token.val.doubleValue = output ;
                    fillToken( token , REAL_T , column , line ) ;
                    return  ;
                }

            }//fetch '.' in 7
                else if ('E' == ch || 'e' == ch )//{7}->{8}
                {
                    eE( instream , input ,  token ,ch );
                    return  ;

                }

}

